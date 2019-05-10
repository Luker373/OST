/*
 README BEFORE EDITING THIS PROJECT
 * 
 * LOOK AT VARS.(H/C)
 * Going to make a variable like those? Put it in there instead of here.
 * 
 * The compiles paths for this project are RELATIVE, NOT ABSOLUTE.
 * 
 * This means you only should need to change the project location under
 * properties -> general (and have the same file structure) for the project
 * to work. 
 * 
 * KEEP ^^THIS^^ HOW IT IS, IF YOU ADD MORE FILES:
 * - make sure a copy of the file physically exists in THIS project's file
 * - do not change the path type to absolute
 * 
 * yes, this means there many copies of things like BOARD.h on your computer,
 * but we can also send the project around to each other much easier
 * 
 * 
 */

#include "vars.h" // all the random variables needed

#include "serialcomm.h"
#include "gpsLib.h"
#include <GenericTypeDefs.h>
#include <string.h>
#include <plib.h>
#include <peripheral/i2c.h>
#include <AD.h>
#include <stdio.h>
#include <math.h>
#include <INPUT_CAPTURE.h>
#include "data_processing.h"
#include "timers.h"
#include "LSM9DS1_func.h"
#include <MatrixMath.h>
#include "BOARD.h"
#include <I2C.h>

#pragma config FPLLODIV = DIV_1, FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FWDTEN = OFF, FCKSM = CSECME, FPBDIV = DIV_1
#pragma config OSCIOFNC = ON, POSCMOD = XT, FSOSCEN = ON, FNOSC = PRIPLL
#pragma config CP = OFF, BWP = OFF, PWP = OFF

#define SENS_SCALE 70 //for LSM9DS1  -- 2000 mdps/LSB
//#define SENS_SCALE 8.75 //for LSM9DS1  -- 8.75 mdps/LSB
//#define biasX
#define Kp_a 0.7
#define Ki_a 0.05
#define ACCEL_X_NULL 0	// no accel null shifts?
#define ACCEL_Y_NULL 0
#define ACCEL_Z_NULL 0
#define ACCEL_SENS_SCALE 0.732    //+/- 16g
//#define ACCEL_SENS_SCALE 0.061      //+/- 2g
#define DELTA_T 0.05

int main(void) {
    char status[100];
    int i, j, k;
    
//    BOARD_Init();
//    TIMERS_Init();
//    AD_Init();
    SERIAL_Init();
    
    while(1){
        PutChar(2, '!');
    }
}
//    
//    err:
//    if (!LSM9DS1_Init()) {
//        sprintf(status, "ERROR\n");
//        for(i = 0; i < strlen(status); ++i)
//            PutChar(2, status[i]);
//        goto err;
//    }
//    
//    char str[100] = "startup";
//    while (1) {
//
//        if (TIMERS_GetMilliSeconds() >= attEstDelay) {
//            loopStep++;
//            //printf("%d;%d;%d\r\n", LSM9DS1_ReadGyroX(), LSM9DS1_ReadGyroY(), LSM9DS1_ReadGyroZ());
//
//            gyroX = (float) LSM9DS1_ReadGyroX();
//            gyroY = (float) LSM9DS1_ReadGyroY();
//            gyroZ = -(float) LSM9DS1_ReadGyroZ();
//            //printf("%f, %f, %f\n", gyroX, gyroY, gyroZ);
//
//            gyroX = (gyroX - biasX) * SENS_SCALE * 3.14 / 180 / 1000; //1000 necessary to convert from mdps to dps
//            gyroY = (gyroY - biasY) * SENS_SCALE * 3.14 / 180 / 1000;
//            gyroZ = (gyroZ - biasZ) * SENS_SCALE * 3.14 / 180 / 1000;
//            gyroInput[0][0] = gyroX;
//            gyroInput[1][0] = gyroY;
//            gyroInput[2][0] = gyroZ;
//            //printf("%f, %f, %f\n", gyroInput[0][0], gyroInput[1][0], gyroInput[2][0]);
//
//            accelX = (float) LSM9DS1_ReadAccelX();
//            accelY = (float) LSM9DS1_ReadAccelY();
//            accelZ = (float) LSM9DS1_ReadAccelZ();
//            
//            //printf("%f, %f, %f\r\n", accelX, accelY, accelZ);
//            accelX = (accelX - ACCEL_X_NULL) * ACCEL_SENS_SCALE / 1000;
//            accelY = (accelY - ACCEL_Y_NULL) * ACCEL_SENS_SCALE / 1000;
//            accelZ = (accelZ - ACCEL_Z_NULL) * ACCEL_SENS_SCALE / 1000;
//            accelReading[0][0] = accelX;
//            accelReading[1][0] = accelY;
//            accelReading[2][0] = accelZ;
//            //
//            //
//            //            gyroInput[0][0] = ((float) LSM9DS1_ReadGyroX() - biasX) / SENS_SCALE * 3.14 / 180;
//            //            gyroInput[1][0] = ((float) LSM9DS1_ReadGyroY() - biasY) / SENS_SCALE * 3.14 / 180;
//            //            gyroInput[2][0] = ((float) LSM9DS1_ReadGyroZ() - biasZ) / SENS_SCALE * 3.14 / 180;
//            //            accelReading[0][0] = ((float) LSM9DS1_ReadAccelX() - ACCEL_X_NULL);
//            //            accelReading[1][0] = ((float) LSM9DS1_ReadAccelY() - ACCEL_Y_NULL);
//            //            accelReading[2][0] = ((float) LSM9DS1_ReadAccelZ() - ACCEL_Z_NULL);
//
//
//            /*
//             * Closed Loop Integration using Matrix Exponential
//             */
//            //accels = accels/norm(accels);
//            normAccel = VectorNorm(accelReading);
//            VectorScalarMultiply(1 / normAccel, accelReading, accel); //set accel to unit vector
//            //printf("%f, %f, %f\r\n", accel[0][0], accel[1][0], accel[2][0]);
//
//            //accelInertial = accelInertial/norm(accelInertial);
//            normAccelInertial = VectorNorm(accelInertialReading);
//            VectorScalarMultiply(1 / normAccelInertial, accelInertialReading, accelInertial); //set accel inertial reference vectors to unit vectors
//            //printf("%f, %f, %f\r\n", accelInertial[0][0], accelInertial[1][0], accelInertial[2][0]);
//
//            //gyroInputWithBias = gyros - Bminus;
//            VectorScalarMultiply(-1.0, biasEstimate, Bminus);
//            VectorAdd(gyroInput, Bminus, gyroInWithBiasEst);
//            //printf("biasEstimate = %f\r\n", biasEstimate);
//            //printf("%f, %f, %f\r\n", gyroInWithBiasEst[0][0], gyroInWithBiasEst[1][0], gyroInWithBiasEst[2][0]);
//
//            //wmeas_a = rcross(accels)*(Rminus' * accelInertial); % accelerometer correction in the body frame            
//            rcross(accel, accelSkew);
//            MatrixTranspose(R, Rminus);
//            MatrixMultiplyVector(Rminus, accelInertial, RminusXaccelInterial);
//            MatrixMultiplyVector(accelSkew, RminusXaccelInterial, wmeas_a);
//
//            VectorScalarMultiply(Kp_a, wmeas_a, KpXwmeas_a);
//            VectorAdd(gyroInWithBiasEst, KpXwmeas_a, gyroInputWithFeedback);
//
//            VectorScalarMultiply(-Ki_a, wmeas_a, bdot);
//
//            VectorScalarMultiply(DELTA_T, gyroInputWithFeedback, gyrosDeltaT);
//            wnorm = sqrt((gyrosDeltaT[0][0] * gyrosDeltaT[0][0]) + (gyrosDeltaT[1][0] * gyrosDeltaT[1][0]) + (gyrosDeltaT[2][0] * gyrosDeltaT[2][0]));
//            //printf("wnorm = %0.3f\r\n", wnorm);
//            rcross(gyrosDeltaT, skewSymGyrosDeltaT);
//            if (wnorm <= 0.01) {
//                s = 1 - pow(wnorm / 2, 2) / 6 + pow(wnorm / 2, 4) / 120 - pow(wnorm / 2, 6) / 5040 + pow(wnorm / 2, 8) / 362880 - pow(wnorm / 2, 10) / 39916800;
//            } else {
//                s = sin(wnorm / 2) / (wnorm / 2);
//            }
//            c = cos(wnorm / 2);
//            MatrixScalarMultiply(s*c, skewSymGyrosDeltaT, termOne);
//            MatrixScalarMultiply(s * s / 2, skewSymGyrosDeltaT, termTwo);
//            MatrixMultiply(termTwo, skewSymGyrosDeltaT, rxrx);
//            MatrixAdd(termOne, rxrx, rodrig);
//            MatrixAdd(eye, rodrig, Rexp);
//            /*********************************************/
//            MatrixMultiply(R, Rexp, Rplus);
//            /*********************************************/
//            VectorAdd(Bminus, bdot, Bplus);
//            MatrixTranspose(Rplus, RplusTrans);
//            MatrixMultiply(Rplus, RplusTrans, eyeTest);
//
//
//            pitch = asin(-Rplus[0][2]);
//            //roll = asin(Rplus[1][2] / cos(pitch));
//            //yaw = asin(Rplus[0][1] / cos(pitch));            
//            roll = atan2(Rplus[1][2], R[2][2]);
//            yaw = atan2(Rplus[0][1], R[0][0]);
//            //
//            //            setRoll(roll);
//            //            setPitch(pitch);
//            //            setYaw(yaw);
//
//            sprintf(str, "r%.2f p%.2f y%.2f\n", roll * 180 / 3.14, pitch * 180 / 3.14, yaw * 180 / 3.14);
//            for(i = 0; i < strlen(str); ++i)
//                PutChar(2, str[i]);
//
//            // copy R to be Rplus for next iteration
//            for (i = 0; i < 3; i++) {
//                for (j = 0; j < 3; j++) {
//                    R[i][j] = Rplus[i][j];
//                }
//            }
//
//            // copy B for next round
//            for (i = 0; i < 3; i++) {
//                biasEstimate[i][0] = Bplus[i][0];
//            }
//
//            attEstDelay += DELTA_T * 1000;
//        }
//
//    }
//
//}