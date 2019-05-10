/*
 * File:   part2.c
 * Author: Joe
 *
 * Created on March 3, 2019, 7:54 PM
 */


#include "xc.h"
#include <BOARD.h>
#include <I2C.h>
#include <AD.h>
#include <timers.h>
#include <stdio.h>
#include <MPU9250.h>
#include <stdlib.h>
#include <Oled.h>
#include <OledDriver.h>
#include <MatrixMath.h>
#include <math.h>

#define SENS_SCALE 131


int main(void) {
    BOARD_Init();
    TIMERS_Init();
    OledInit();
    AD_Init();
    MPU9250_Init();

    int delay = 500;
    float deltaT = 0.05;
    float roll, pitch, yaw;
    int i, j, k, loopStep = 0;
    float bias[3] = {270.7, 150.2, -107.0};
    float biasX = 275.124451, biasY = 154.4904832, biasZ = -107.0673499;
    float wnorm, s, c;
    char str[100] = "startup";
    float gyroX, gyroY, gyroZ;

    float eye[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };

    float gyroInput[3][1] = {};
    
    float nvector[3][1] = {
        {1},
        {0},
        {0}
    };
    float evector[3][1] = {
        {0},
        {-1},
        {0}
    };
    float dvector[3][1] = {
        {0},
        {0},
        {-1}
    };
    float newNVector[3][1] = {
        {0},
        {0},
        {0}
    };
    float newEVector[3][1] = {
        {0},
        {0},
        {0}
    };
    float newDVector[3][1] = {
        {0},
        {0},
        {0}
    };
    float Ro[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    float R[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    float Rplus[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    float Rtrans[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    float RplusTrans[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    float eyeTest[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };        
    
    float skewSymGyrosDeltaT[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    float RSkew[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    float RSkewDelta[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    float rx[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    float gyrosDeltaT[3][1] = {
        {0},
        {0},
        {0}
    };
    float termOne[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    float termTwo[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    float rxrx[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    float rodrig[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    float Rexp[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };

    while (1) {

       if (TIMERS_GetMilliSeconds() == delay) {
           loopStep++;
            //printf("%d;%d;%d\r\n", MPU9250_ReadGyroX(), MPU9250_ReadGyroY(), MPU9250_ReadGyroZ());

            gyroX = (float) MPU9250_ReadGyroX();
            gyroY = (float) MPU9250_ReadGyroY();
            gyroZ = (float) MPU9250_ReadGyroZ();

            gyroX = (gyroX - biasX)/SENS_SCALE*3.14/180;
            gyroY = (gyroY - biasY)/SENS_SCALE*3.14/180;
            gyroZ = (gyroZ - biasZ)/SENS_SCALE*3.14/180;

            //printf("%f, %f, %f\n", gyroX, gyroY, gyroZ);


            gyroInput[0][0] = gyroX;
            gyroInput[1][0] = gyroY;
            gyroInput[2][0] = gyroZ;
            
            //printf("%f, %f, %f\n", gyroInput[0][0], gyroInput[1][0], gyroInput[2][0]);
            //open loop integrate using matrix exponential

            VectorScalarMultiply(deltaT, gyroInput, gyrosDeltaT);
            wnorm = sqrt((gyrosDeltaT[0][0] * gyrosDeltaT[0][0]) + (gyrosDeltaT[1][0] * gyrosDeltaT[1][0]) + (gyrosDeltaT[2][0] * gyrosDeltaT[2][0]));
            printf("wnorm = %0.4f\r\n", wnorm);
            rcross(gyrosDeltaT, skewSymGyrosDeltaT);
            if (wnorm <= 0.01) {
                s = 1 - pow(wnorm/2, 2) / 6 + pow(wnorm/2, 4) / 120 - pow(wnorm/2, 6) / 5040 + pow(wnorm/2, 8) / 362880 - pow(wnorm/2, 10) / 39916800;
            } else {
                s = sin(wnorm / 2) / (wnorm / 2);
            }
            c = cos(wnorm / 2);

            MatrixScalarMultiply(s*c, skewSymGyrosDeltaT, termOne);

            MatrixScalarMultiply(s*s/2, skewSymGyrosDeltaT, termTwo);
            MatrixMultiply(termTwo, skewSymGyrosDeltaT, rxrx);
            MatrixAdd(termOne, rxrx, rodrig);
//            MatrixMultiply(skewSymGyrosDeltaT, skewSymGyrosDeltaT, rxrx);
//            MatrixScalarMultiply(s * s / 2, rxrx, termTwo);
//            MatrixAdd(termOne, termTwo, rodrig);

            MatrixAdd(eye, rodrig, Rexp);
            MatrixMultiply(R, Rexp, Rplus);
                        
            MatrixTranspose(Rplus, RplusTrans);
            MatrixMultiply(Rplus, RplusTrans, eyeTest);

            /*Matlab Code*/
            //Rplus = Rminus * Rexp(gyros*deltaT);
            //R_exp = [1 0 0;0 1 0;0 0 1] + s*c*rx + s*s/2*rx*rx;
            
            //asin returns -90 to +90
            pitch = asin(-Rplus[0][2]);
            roll = asin(Rplus[1][2] / cos(pitch));
            yaw = asin(Rplus[0][1] / cos(pitch));

           
            sprintf(str, "Part4: Open Loop\r\nrol = %.2f\npit = %.2f\r\nyaw = %.2f\n", roll * 180 / 3.14, pitch * 180 / 3.14, yaw * 180 / 3.14);
            printf("rol = %.2f pit = %.2f yaw = %.2f\r\n", roll * 180 / 3.14, pitch * 180 / 3.14, yaw * 180 / 3.14);
            OledClear(OLED_COLOR_BLACK);
            OledDrawString(str);
            OledUpdate();
            
            printf("Rplus on iteration %d", loopStep);
            MatrixPrint2(Rplus);
            printf("Orthonormal I test");
            MatrixPrint2(eyeTest);
            /*
            MatrixTranspose(Rplus, Rtrans);
            MatrixMultiplyVector(Rtrans, nvector, newNVector);
            MatrixMultiplyVector(Rtrans, evector, newEVector);
            MatrixMultiplyVector(Rtrans, dvector, newDVector);
             */

            // copy R to be Rplus for next iteration
            for (i = 0; i < 3; i++) {
                for (j = 0; j < 3; j++) {
                    R[i][j] = Rplus[i][j];
                }
                       }

            delay += 50;
        }
    }

    return 0;

}