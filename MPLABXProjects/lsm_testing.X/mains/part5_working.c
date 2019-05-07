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
//#define biasX
#define Kp_a 0.7
#define Ki_a 0.05
#define ACCEL_X_NULL 468.5036331
#define ACCEL_Y_NULL 230.9540918
#define ACCEL_Z_NULL 580.4147557

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
    float accelX, accelY, accelZ;


    float eye[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };

    float gyroInput[3][1] = {};

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
    ////////////////////////////////////////////
    float accelReading[3][1] = {};
    float accelInertialReading[3][1] = {
        {0},
        {0},
        {-1}
    };
    float normAccel;
    float normAccelInertial;
    float accel[3][1] = {};
    float accelInertial[3][1] = {};
    //
    float biasEstimate[3][1] = {
        {0},
        {0},
        {0}
    };
    float Bminus[3][1] = {
        {0},
        {0},
        {0}
    };
    float gyroInWithBiasEst[3][1] = {};
    //
    float accelSkew[3][3] = {};
    float Rminus[3][3] = {};
    float RminusXaccelInterial[3][1] = {};
    float wmeas_a[3][1] = {};
    //
    float KpXwmeas_a[3][1] = {};
    float gyroInputWithFeedback[3][1] = {};
    //
    float KiXwmeas_a[3][1] = {};
    float bdot[3][1] = {};
    //
    float Bplus[3][1] = {};

    while (1) {

        if (TIMERS_GetMilliSeconds() == delay) {
            loopStep++;
            //printf("%d;%d;%d\r\n", MPU9250_ReadGyroX(), MPU9250_ReadGyroY(), MPU9250_ReadGyroZ());

            gyroX = (float) MPU9250_ReadGyroX();
            gyroY = (float) MPU9250_ReadGyroY();
            gyroZ = (float) MPU9250_ReadGyroZ();
            gyroX = (gyroX - biasX) / SENS_SCALE * 3.14 / 180;
            gyroY = (gyroY - biasY) / SENS_SCALE * 3.14 / 180;
            gyroZ = (gyroZ - biasZ) / SENS_SCALE * 3.14 / 180;
            gyroInput[0][0] = gyroX;
            gyroInput[1][0] = gyroY;
            gyroInput[2][0] = gyroZ;
            //printf("%f, %f, %f\n", gyroInput[0][0], gyroInput[1][0], gyroInput[2][0]);

            accelX = (float) MPU9250_ReadAccelX();
            accelY = (float) MPU9250_ReadAccelY();
            accelZ = (float) MPU9250_ReadAccelZ();
            accelX = (accelX - ACCEL_X_NULL);
            accelY = (accelY - ACCEL_Y_NULL);
            accelZ = (accelZ - ACCEL_Z_NULL);
            accelReading[0][0] = -accelX;
            accelReading[1][0] = -accelY;
            accelReading[2][0] = -accelZ;
//
//
//            gyroInput[0][0] = ((float) MPU9250_ReadGyroX() - biasX) / SENS_SCALE * 3.14 / 180;
//            gyroInput[1][0] = ((float) MPU9250_ReadGyroY() - biasY) / SENS_SCALE * 3.14 / 180;
//            gyroInput[2][0] = ((float) MPU9250_ReadGyroZ() - biasZ) / SENS_SCALE * 3.14 / 180;
//            accelReading[0][0] = ((float) MPU9250_ReadAccelX() - ACCEL_X_NULL);
//            accelReading[1][0] = ((float) MPU9250_ReadAccelY() - ACCEL_Y_NULL);
//            accelReading[2][0] = ((float) MPU9250_ReadAccelZ() - ACCEL_Z_NULL);


            /*
             * Closed Loop Integration using Matrix Exponential
             */
            //accels = accels/norm(accels);
            normAccel = VectorNorm(accelReading);
            VectorScalarMultiply(1 / normAccel, accelReading, accel); //set accel to unit vector
            //printf("%f, %f, %f\r\n", accel[0][0], accel[1][0], accel[2][0]);

            //accelInertial = accelInertial/norm(accelInertial);
            normAccelInertial = VectorNorm(accelInertialReading);
            VectorScalarMultiply(1 / normAccelInertial, accelInertialReading, accelInertial); //set accel inertial reference vectors to unit vectors
            //printf("%f, %f, %f\r\n", accelInertial[0][0], accelInertial[1][0], accelInertial[2][0]);

            //gyroInputWithBias = gyros - Bminus;
            VectorScalarMultiply(-1.0, biasEstimate, Bminus);
            VectorAdd(gyroInput, Bminus, gyroInWithBiasEst);
            //printf("biasEstimate = %f\r\n", biasEstimate);
            printf("%f, %f, %f\r\n", gyroInWithBiasEst[0][0], gyroInWithBiasEst[1][0], gyroInWithBiasEst[2][0]);

            //wmeas_a = rcross(accels)*(Rminus' * accelInertial); % accelerometer correction in the body frame            
            rcross(accel, accelSkew);
            MatrixTranspose(R, Rminus);
            MatrixMultiplyVector(Rminus, accelInertial, RminusXaccelInterial);
            MatrixMultiplyVector(accelSkew, RminusXaccelInterial, wmeas_a);

            //gyroInputWithFeedback = gyroInputWithBias + Kp_a*wmeas_a + Kp_m*wmeas_m;
            VectorScalarMultiply(Kp_a, wmeas_a, KpXwmeas_a);
            VectorAdd(gyroInWithBiasEst, KpXwmeas_a, gyroInputWithFeedback);

            //bdot=-Ki_a*wmeas_a - Ki_m*wmeas_m;
            VectorScalarMultiply(-Ki_a, wmeas_a, bdot);

            //Rplus = Rminus * Rexp(gyroInputWithFeedback)
            /////////////////////////////////////////////////////////////////////////
            VectorScalarMultiply(deltaT, gyroInputWithFeedback, gyrosDeltaT);
            wnorm = sqrt((gyrosDeltaT[0][0] * gyrosDeltaT[0][0]) + (gyrosDeltaT[1][0] * gyrosDeltaT[1][0]) + (gyrosDeltaT[2][0] * gyrosDeltaT[2][0]));
            //printf("wnorm = %0.3f\r\n", wnorm);
            rcross(gyrosDeltaT, skewSymGyrosDeltaT);
            if (wnorm <= 0.01) {
                s = 1 - pow(wnorm / 2, 2) / 6 + pow(wnorm / 2, 4) / 120 - pow(wnorm / 2, 6) / 5040 + pow(wnorm / 2, 8) / 362880 - pow(wnorm / 2, 10) / 39916800;
            } else {
                s = sin(wnorm / 2) / (wnorm / 2);
            }
            c = cos(wnorm / 2);

            MatrixScalarMultiply(s*c, skewSymGyrosDeltaT, termOne);

            MatrixScalarMultiply(s * s / 2, skewSymGyrosDeltaT, termTwo);
            MatrixMultiply(termTwo, skewSymGyrosDeltaT, rxrx);
            MatrixAdd(termOne, rxrx, rodrig);
            //            MatrixMultiply(skewSymGyrosDeltaT, skewSymGyrosDeltaT, rxrx);
            //            MatrixScalarMultiply(s * s / 2, rxrx, termTwo);
            //            MatrixAdd(termOne, termTwo, rodrig);

            MatrixAdd(eye, rodrig, Rexp);
            /*********************************************/
            MatrixMultiply(R, Rexp, Rplus);
            /*********************************************/
            //Bplus = Bminus + bdot;
            VectorAdd(Bminus, bdot, Bplus);
            //
            MatrixTranspose(Rplus, RplusTrans);
            MatrixMultiply(Rplus, RplusTrans, eyeTest);

            /*Matlab Code*/
            //Rplus = Rminus * Rexp(gyros*deltaT);
            //R_exp = [1 0 0;0 1 0;0 0 1] + s*c*rx + s*s/2*rx*rx;

            pitch = asin(-Rplus[0][2]);
            roll = asin(Rplus[1][2] / cos(pitch));
            yaw = asin(Rplus[0][1] / cos(pitch));

            sprintf(str, "roll = %.2f\npitch = %.2f\r\nyaw =%.2f\n", roll * 180 / 3.14, pitch * 180 / 3.14, yaw * 180 / 3.14);
            printf("roll = %.2f pitch = %.2f yaw =%.2f\r\n", roll * 180 / 3.14, pitch * 180 / 3.14, yaw * 180 / 3.14);
            OledClear(OLED_COLOR_BLACK);
            OledDrawString(str);
            OledUpdate();

            printf("Rplus on iteration %d", loopStep);
            MatrixPrint2(Rplus);
            printf("Orthonormal I test");
            MatrixPrint2(eyeTest);


            // copy R to be Rplus for next iteration
            for (i = 0; i < 3; i++) {
                for (j = 0; j < 3; j++) {
                    R[i][j] = Rplus[i][j];
                }
            }

            // copy B for next round
            for (i = 0; i < 3; i++) {
                biasEstimate[i][0] = Bplus[i][0];
            }

            delay += 50;
        }
    }

    return 0;

}

/*for i=1:numSteps,              
    gyroInputWithBias=gyroInput+biasTerms;
    [R,biasEstimate] = IntegrateClosedLoop(R,biasEstimate,gyroInputWithBias,magReading,accelReading,magInertial,accelInertial,.1)    
 pause;
end
 
 function [Rplus, Bplus] = IntegrateOpenLoop(Rminus, Bminus, gyros, mags, accels, magInertial, accelInertial, deltaT)
% function [Rplus, Bplus] = IntegrateOpenLoop(Rminus, Bminus, gyros, mags, accels, magInertial, accelInertial, deltaT)
%
% Function to implement the full complementary estimate and integration of
% gyros for full attitude estimation using an accelerometer and
% magnetometer feedback.
%
% Inputs: Previous attitute DCM (Rminus)
%         Previous bias estimate (Bminus)
%         Body Fixed Rotation rates ([p;q;r]) in rad/s (gyros)
%         Magnetometer Readings in body coordinates (mags)
%         Accelerometer Readings in body coordinates (accels)
%         Inertial reference magnetic field (magInertial)
%         Inertial reference gravity field (accelInertial)
%         Time between samples (deltaT) in seconds
%
% Outputs: New DCM (Rplus)
%
% Note: This code implements a full complementary filter on the DCM using
% the matrix exponential integration of the gyros. Units of the mags and
% accels should match their respective reference inertial vectors. The
% gains are constant and set internally, modify as needed.


Kp_a=.2;
Ki_a=Kp_a/10;

Kp_m=.2;
Ki_m=Kp_m/10;

accels = accels/norm(accels);                       % set mags and accels to unit vectors
mags = mags/norm(mags);

magInertial = magInertial/norm(magInertial);        % set inertial reference vectors to unit vectors
accelInertial = accelInertial/norm(accelInertial);

gyroInputWithBias = gyros - Bminus;
wmeas_a = rcross(accels)*(Rminus' * accelInertial); % accelerometer correction in the body frame
wmeas_m = rcross(mags) * (Rminus' * magInertial);   % magnetometer correction in the body frame
 *          3x3         x (3x3 x 3x1) => 3x1
 * 
 * 
    
gyroInputWithFeedback = gyroInputWithBias + Kp_a*wmeas_a + Kp_m*wmeas_m;
bdot=-Ki_a*wmeas_a - Ki_m*wmeas_m;
    
Rplus = Rminus * Rexp(gyroInputWithFeedback)
Bplus = Bminus + bdot;

 */