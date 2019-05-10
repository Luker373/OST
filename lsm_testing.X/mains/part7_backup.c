/*
 * File:   part5.c
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
#define GYRO_BIAS_X 275.124451
#define GYRO_BIAS_Y 154.4904832
#define GYRO_BIAS_Z -107.0673499
#define Kp_a .5
#define Ki_a 0.02
#define ACCEL_X_NULL 468.5036331
#define ACCEL_Y_NULL 230.9540918
#define ACCEL_Z_NULL 580.4147557
#define Kp_m 0.1
#define Ki_m 0.05
#define MAG_X_NULL 108.258167
#define MAG_Y_NULL 115.9547344
#define MAG_Z_NULL -186.0074596

int main(void) {
    BOARD_Init();
    TIMERS_Init();
    OledInit();
    AD_Init();
    MPU9250_Init();

    int delay = 500;
    int i, j, k, loopStep = 0;

    float deltaT = 0.05;
    float roll, pitch, yaw, c2;
    float gyroX, gyroY, gyroZ;
    float accelX, accelY, accelZ;
    float magX, magY, magZ;
    float wnorm, s, c;

    float bias[3] = {270.7, 150.2, -107.0};
    float biasX = 275.124451, biasY = 154.4904832, biasZ = -107.0673499;

    char str[100] = "startup";

    float eye[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    float eyeTest[3][3] = {};

    float gyroInput[3][1] = {};

    float R[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    float Rplus[3][3] = {};
    float Rtrans[3][3] = {};
    float RplusTrans[3][3] = {};

    float skewSymGyrosDeltaT[3][3] = {};
    float RSkew[3][3] = {};

    float RSkewDelta[3][3] = {};
    float rx[3][3] = {};
    float gyrosDeltaT[3][1] = {};
    float termOne[3][3] = {};
    float termTwo[3][3] = {};
    float rxrx[3][3] = {};
    float rodrig[3][3] = {};
    float Rexp[3][3] = {};

    ////////////////////////////////////////////
    float accelReading[3][1] = {};
    //NED
    float accelInertialReading[3][1] = {
        {0},
        {0},
        {1} // -1? accel actually reads pos
    };
    //    float accelInertialReading[3][1] = {
    //        {-434.6574818},
    //        {-111.9481693},
    //        {16718.59185}
    //    };
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
    float BminusNeg[3][1] = {
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
    ////////////////////////////////////////////
    //    float Rmis[3][3] = {
    //        {0.9104, 0.3322, 0.2466},
    //        {0.3934, -0.5108, -0.7644},
    //        {-0.1279, 0.7929, -0.5957}
    //    };

    //    float Rmis[3][3] = {
    //        {0.7347, 0.6277, 0.2574},
    //        {0.5981, -0.4202, -0.6824},
    //        {-0.3202, 0.6553, -0.6841}
    //    };

    //    float Rmis[3][3] = {
    //        {0.6257, -0.7642, 0.156},
    //        {0.3023, 0.4227, 0.8544},
    //        {-0.7191, -0.4872, 0.4955}
    //    };

    //    float Rmis[3][3] = {
    //        {0.9104, 0.3322, 0.2466},
    //        {0.3934, -0.5108, -0.7644},
    //        {-0.1279, 0.7929, -0.5957}
    //    };

    //    float Rmis[3][3] = {
    //        {-0.9932, -0.0054, -0.1166},
    //        {0.1057, -0.4655, -0.8787},
    //        {-0.0495, -0.8850, 0.4629}
    //    };

    //        float Rmis[3][3] = {
    //            {0.1667, - 0.0619, 0.9841},
    //            {0.9231, 0.3605, - 0.1336},
    //            {-0.3465, 0.9307, 0.1173}
    //        };

    //    float Rmis[3][3] = {
    //        {0.0619, -0.1667, -0.9841},
    //        {-0.3605, -0.9231, 0.1336},
    //        {-0.9307, 0.3464, -0.1173}
    //    };
    //    float Rmis[3][3] = {
    //        {0.0, 1.0, 0.0},
    //        {1.0, 0.0, 0.0},
    //        {0.0, 0.0, -1.0}
    //    };

    float Rmis[3][3] = {
        {0.0559, 0.9846, 0.1655},
        {0.9715, -0.0919, 0.2187},
        {0.2305, 0.1485, -0.9617}
    };

    float RmisT[3][3] = {};
    float magReading[3][1] = {};
    float magReadingAligned[3][1] = {};
    //NOAA NED comps
    float magInertialReading[3][1] = {
        {22819.3},
        {5363.1},
        {41558.8}
    };
    //    float magInertialReading[3][1] = {
    //        {5363.1},
    //        {22819.3},
    //        {-41558.8}
    //    };
    //            float magInertialReading[3][1] = {
    //                {132.41},
    //                {42.878},
    //                {230.071}
    //            };
    //        float magInertialReading[3][1] = {
    //            {1},
    //            {0},
    //            {0}
    //        };
    float magInertialReadingAligned[3][1] = {};

    float normMag;
    float normMagInertial;
    float mag[3][1] = {};
    float magInertial[3][1] = {};
    //

    //
    float magSkew[3][3] = {};
    float RminusXmagInterial[3][1] = {};
    float wmeas_m[3][1] = {};
    //
    float KpXwmeas_m[3][1] = {};
    float gyroInputWithAccelFeedback[3][1] = {};
    //
    float KiXwmeas_m[3][1] = {};
    //

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
            accelReading[0][0] = accelX;
            accelReading[1][0] = accelY;
            accelReading[2][0] = accelZ;
            //printf("%f, %f, %f\n", accelReading[0][0], accelReading[1][0], accelReading[2][0]);


            magX = (float) MPU9250_ReadMagX();
            magY = (float) MPU9250_ReadMagY();
            magZ = (float) MPU9250_ReadMagZ();
            magX = (magX - MAG_X_NULL);
            magY = (magY - MAG_Y_NULL);
            magZ = (magZ - MAG_Z_NULL);
            magReading[0][0] = magX;
            magReading[1][0] = magY;
            magReading[2][0] = magZ;
            //printf("%f, %f, %f\n", magReading[0][0], magReading[1][0], magReading[2][0]);

            //            gyroInput[0][0] = ((float) MPU9250_ReadGyroX() - biasX) / SENS_SCALE * 3.14 / 180;
            //            gyroInput[1][0] = ((float) MPU9250_ReadGyroY() - biasY) / SENS_SCALE * 3.14 / 180;
            //            gyroInput[2][0] = ((float) MPU9250_ReadGyroZ() - biasZ) / SENS_SCALE * 3.14 / 180;
            //            accelReading[0][0] = ((float) MPU9250_ReadAccelX() - ACCEL_X_NULL);
            //            accelReading[1][0] = ((float) MPU9250_ReadAccelY() - ACCEL_Y_NULL);
            //            accelReading[2][0] = ((float) MPU9250_ReadAccelZ() - ACCEL_Z_NULL);


            /*
             * Closed Loop Integration using Matrix Exponential
             */

            // Align magnetometer to accelerometer coordinate frame
            MatrixTranspose(Rmis, RmisT);
            MatrixMultiplyVector(RmisT, magReading, magReadingAligned);
            MatrixMultiplyVector(RmisT, magInertialReading, magInertialReadingAligned);


            //accels = accels/norm(accels);
            normAccel = VectorNorm(accelReading);
            VectorScalarMultiply(1 / normAccel, accelReading, accel); //set accel to unit vector
            //printf("%f, %f, %f\r\n", accel[0][0], accel[1][0], accel[2][0]);
            //mags = mags/norm(mags);
            normMag = VectorNorm(magReadingAligned);
            VectorScalarMultiply(1 / normMag, magReadingAligned, mag); //set mag to unit vector
            //printf("%f, %f, %f\r\n", mag[0][0], mag[1][0], mag[2][0]);

            /* Set inertial reference vectors to unit vectors */
            //accelInertial = accelInertial/norm(accelInertial);
            normAccelInertial = VectorNorm(accelInertialReading);
            VectorScalarMultiply(1 / normAccelInertial, accelInertialReading, accelInertial);
            //printf("%f, %f, %f\r\n", accelInertial[0][0], accelInertial[1][0], accelInertial[2][0]);            
            // what is the mag inertial vector?
            //magInertial = magInertial/norm(magInertial);
            normMagInertial = VectorNorm(magInertialReading);
            //VectorScalarMultiply(1.0 / normMagInertial, magInertialReading, magInertial); //set mag inertial reference vectors to unit vectors
            VectorScalarMultiply(1 / normMagInertial, magInertialReadingAligned, magInertial); //does inertial reading need to be aligned too?

            //gyroInputWithBias = gyros - Bminus;
            VectorScalarMultiply(-1.0, biasEstimate, BminusNeg);
            VectorAdd(gyroInput, BminusNeg, gyroInWithBiasEst);
            //printf("%f, %f, %f\r\n", gyroInWithBiasEst[0][0], gyroInWithBiasEst[1][0], gyroInWithBiasEst[2][0]);

            //wmeas_a = rcross(accels)*(Rminus' * accelInertial); % accelerometer correction in the body frame            
            rcross(accel, accelSkew);
            MatrixTranspose(R, Rminus);
            MatrixMultiplyVector(Rminus, accelInertial, RminusXaccelInterial);
            MatrixMultiplyVector(accelSkew, RminusXaccelInterial, wmeas_a);

            //wmeas_m = rcross(mags)*(Rminus' * magInertial); % magnetometer correction in the body frame            
            rcross(mag, magSkew);
            //            MatrixTranspose(R, Rminus);
            MatrixMultiplyVector(Rminus, magInertial, RminusXmagInterial);
            MatrixMultiplyVector(magSkew, RminusXmagInterial, wmeas_m);

            //gyroInputWithFeedback = gyroInputWithBias + Kp_a*wmeas_a + Kp_m*wmeas_m;
            VectorScalarMultiply(Kp_a, wmeas_a, KpXwmeas_a);
            VectorScalarMultiply(Kp_m, wmeas_m, KpXwmeas_m);
            VectorAdd(gyroInWithBiasEst, KpXwmeas_a, gyroInputWithAccelFeedback);
            VectorAdd(KpXwmeas_m, gyroInputWithAccelFeedback, gyroInputWithFeedback);

            //bdot=-Ki_a*wmeas_a - Ki_m*wmeas_m;
            VectorScalarMultiply(-Ki_a, wmeas_a, KiXwmeas_a);
            VectorScalarMultiply(-Ki_m, wmeas_m, KiXwmeas_m);
            VectorAdd(KiXwmeas_a, KiXwmeas_m, bdot);

            /* Matrix Exponential
             * Rplus = Rminus * Rexp(gyroInputWithFeedback)
             */
            VectorScalarMultiply(deltaT, gyroInputWithFeedback, gyrosDeltaT);
            wnorm = VectorNorm(gyrosDeltaT);
            //wnorm = sqrt((gyrosDeltaT[0][0] * gyrosDeltaT[0][0]) + (gyrosDeltaT[1][0] * gyrosDeltaT[1][0]) + (gyrosDeltaT[2][0] * gyrosDeltaT[2][0]));
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
            MatrixMultiply(R, Rexp, Rplus);
            /*********************************************/
            //Bplus = Bminus + bdot;
            VectorAdd(Bminus, bdot, Bplus);
            /*************************************************************************************************/
            /* Testing of DCM */
            //            MatrixTranspose(Rplus, RplusTrans);
            //            MatrixMultiply(Rplus, RplusTrans, eyeTest);
            //            printf("Rplus on iteration %d", loopStep);
            //            MatrixPrint2(Rplus);
            //            printf("Orthonormal I test");
            //            MatrixPrint2(eyeTest);

            /* Euler Angles from DCM */
            pitch = asin(-Rplus[0][2]);
            //          roll = asin(Rplus[1][2] / cos(pitch));
            //            yaw = asin(Rplus[0][1] / cos(pitch));
            //c2 = sqrt(R[0][0] * R[0][0] + R[0][1] * R[0][1]);
            c2 = sqrt(Rplus[1][2] * R[1][2] + R[2][2] * R[2][2]);

            roll = atan2(Rplus[1][2], R[2][2]);
            //pitch = atan2(-R[0][2], c2);
            yaw = atan2(Rplus[0][1], R[0][0]);

            //printf("%.2f;%.2f;%.2f\n", roll * 180 / 3.14, pitch * 180 / 3.14, yaw * 180 / 3.14);
            sprintf(str, "Part7: Closed A&M\r\nrol = %.2f\npit = %.2f\r\nyaw = %.2f\n", roll * 180 / 3.14, pitch * 180 / 3.14, yaw * 180 / 3.14);
            printf("%.2f %.2f %.2f;\r\n", roll * 180 / 3.14, pitch * 180 / 3.14, yaw * 180 / 3.14);

            //printf("roll = %.2f pitch = %.2f yaw = %.2f\r\n", roll * 180 / 3.14, pitch * 180 / 3.14, yaw * 180 / 3.14);
            OledClear(OLED_COLOR_BLACK);
            OledDrawString(str);
            OledUpdate();

            // copy Rplus to R for next iteration
            for (i = 0; i < 3; i++) {
                for (j = 0; j < 3; j++) {
                    R[i][j] = Rplus[i][j];
                }
            }
            // copy Bplus to biasEstimate for next round
            for (i = 0; i < 3; i++) {
                biasEstimate[i][0] = Bplus[i][0];
            }

            delay += 50;
        }
    }

    return 0;

}

/*
 * Matlab code - ClosedLoopIntegrationFunc
 * 
 * for i=1:numSteps,              
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