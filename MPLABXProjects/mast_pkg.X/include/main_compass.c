/*
 * File:   mpu_tilt_compass.c
 * Author: Joe
 *
 * Created on May 11, 2019, 1:32 AM
 * 
 * Uses previous accel att est to tilt compensate compass calculation.
 * Magnetometer data must be normalized and aligned with accelerometer.
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
#include "MPU9250.h"

#pragma config FPLLODIV = DIV_1, FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FWDTEN = OFF, FCKSM = CSECME, FPBDIV = DIV_1
#pragma config OSCIOFNC = ON, POSCMOD = XT, FSOSCEN = ON, FNOSC = PRIPLL
#pragma config CP = OFF, BWP = OFF, PWP = OFF

//MPU9250 SETTINGS
//OLD NAIVE
//#define ACCEL_SENS_SCALE 16384
//#define ACCEL_X_NULL 468.5036331
//#define ACCEL_Y_NULL 230.9540918
//#define ACCEL_Z_NULL 580.4147557

//OLD ELLIPSOID
//#define ACCEL_X_NULL -0.0293391789930355
//#define ACCEL_Y_NULL -0.0129116378750163
//#define ACCEL_Z_NULL -0.0347796690241969

//NEW
#define ACCEL_X_NULL -0.0265
#define ACCEL_Y_NULL -0.0138
#define ACCEL_Z_NULL -0.0374

//OLD NAIIVE
//#define MAG_X_NULL 108.258167
//#define MAG_Y_NULL 115.9547344
//#define MAG_Z_NULL -186.0074596

//OLD ELLIPSOID
//#define MAG_X_NULL -0.629648290470760
//#define MAG_Y_NULL -0.682535317554976
//#define MAG_Z_NULL 1.08468200204145

//NEW
#define MAG_X_NULL -0.8223
#define MAG_Y_NULL -0.9022
#define MAG_Z_NULL 1.3509

#define DELTA_T 10
#define MOVING 20

/*****************************************************************************/
/************************* Luke's Circular Moving Average ********************/
#define WINDOW_SIZE 10
#define WINDOW_SUM (WINDOW_SIZE)*(WINDOW_SIZE+1)/2

int compassSupdated = 0, compassDupdated = 0, compassSidx = 0, compassDidx = 0, compassSsum = 0, compassDsum = 0, c_startup = 1, j;
int compassSarr[WINDOW_SIZE];
int compassDraw[WINDOW_SIZE];
int compassDarr[WINDOW_SIZE];
float compassDegree;

void setcompassDegree(float f) {
    compassDupdated = 1;
    f += 360;
    f = (int)f;
    int compassDold = (compassDidx - 1) % WINDOW_SIZE;
    compassDidx = compassDidx % WINDOW_SIZE;
    compassDraw[compassDidx] = f;
    if (c_startup != 1) {
        if (f < 410 && compassDraw[compassDold] > 660)
            f = compassDarr[compassDold] / 10 + (360 - compassDraw[compassDold]) + f;
        else if (f > 660 && compassDraw[compassDold] < 410)
            f = compassDarr[compassDold] / 10 - (360 - f + compassDraw[compassDold]);
        else
            f = compassDarr[compassDold] / 10 - (compassDraw[compassDold] - f);
    } else {
        c_startup = 0;
    }
    compassDsum += f * 10 * WINDOW_SIZE;
    for (j = 0; j < WINDOW_SIZE; ++j) {
        compassDsum -= compassDarr[j];
    }
    compassDarr[compassDidx] = (int) (f * 10);
    ++compassDidx;
    //compassDegree = f;
}

float getcompassDegree(void) {
    if (compassDupdated == 0)
        return compassDegree;
    compassDupdated = 0;
    compassDegree = compassDsum / (10 * WINDOW_SUM);
    compassDegree = fmod(compassDegree, 360);
    return compassDegree;
}
/*****************************************************************************/

/*****************************************************************************/

int main(void) {
    BOARD_Init();
    TIMERS_Init();
    //OledInit();
    AD_Init();
    MPU9250_Init();

    char str[100] = "startup";
    int delay = 500;
    uint32_t i = 0;

    float deltaT = DELTA_T / 1000;
    float prev = 0;
    float radToDeg = 180 / 3.1415;
    float rollAvg, pitchAvg, compassAvg, rollSum = 0, pitchSum = 0, compassSum = 0, magHeading, rawCompassHeading, alignedCompassHeading;
    float accelX, accelY, accelZ;
    float magX, magY, magZ, magXCorr, magYCorr, magZCorr;

    float accel[3][1] = {};
    float roll[MOVING] = {};
    float pitch[MOVING] = {};
    float compass[MOVING] = {};


    float accelNullVec[3][1] = {
        {ACCEL_X_NULL},
        {ACCEL_Y_NULL},
        {ACCEL_Z_NULL}
    };

    // OLD NORMALIZING SPHERICAL SCALING FACTOR
    //    float accelScale[3][3] = {
    //        {6.05689436147414e-05, -7.01875406863991e-07, -5.09637778490521e-08},
    //        {5.15299782820684e-07, 6.04512834485393e-05, 2.35752210469650e-07},
    //        {1.81773373852542e-07, -2.97123434340270e-07, 6.00480565218782e-05}
    //    };

    //NEW
    float accelScale[3][3] = {
        {0.6064e-04, 0.0023e-04, 0.0007e-04},
        {0.0016e-04, 0.6062e-04, -0.0010e-04},
        {0.0006e-04, -0.0062e-04, 0.5977e-04}
    };

    float accelReading[3][1] = {};
    float accelVec[3][1] = {};
    float accelVecScaled[3][1] = {};
    float accelVecShifted[3][1] = {};

    float magNullVec[3][1] = {
        {MAG_X_NULL},
        {MAG_Y_NULL},
        {MAG_Z_NULL}
    };

    //OLD
    //    float magScale[3][3] = {
    //        {0.00612670493408451, -0.000223849273296355, -4.68643007321321e-05},
    //        {0.000114922610714144, 0.00605271757439585, 3.50945764595120e-05},
    //        {-1.79479995660422e-05, 2.43864656457224e-05, 0.00577277581299775}
    //    };

    //NEW
    float magScale[3][3] = {
        {0.0083, 0.0000, 0.0001},
        {-0.0000, 0.0085, 0.0002},
        {0.0001, 0.0002, 0.0076}
    };

    float magReading[3][1] = {};
    float magReadingAligned[3][1] = {};
    float magVec[3][1] = {};
    float magVecScaled[3][1] = {};
    float magVecShifted[3][1] = {};

    //BASIC is BETTER
        float Rmis[3][3] = {
            {0, 1, 0},
            {1, 0, 0},
            {0, 0, -1}
        };
    float RmisT[3][3] = {};

    while (1) {

        if (TIMERS_GetMilliSeconds() - prev >= DELTA_T) {
            delay = TIMERS_GetMilliSeconds() - prev;
            // clock over array index at modulo moving points
            if ((i % MOVING) == 0)
                i = 0;

            accelX = (float) MPU9250_ReadAccelX();
            accelY = (float) MPU9250_ReadAccelY();
            accelZ = (float) MPU9250_ReadAccelZ();
            accelVec[0][0] = accelX;
            accelVec[1][0] = accelY;
            accelVec[2][0] = accelZ;

            //Correct accelerometer ellipsoid data
            MatrixMultiplyVector(accelScale, accelVec, accelVecScaled);
            VectorAdd(accelVecScaled, accelNullVec, accelVecShifted);
            accelReading[0][0] = accelVecShifted[0][0];
            accelReading[1][0] = accelVecShifted[1][0];
            accelReading[2][0] = accelVecShifted[2][0];

            // OLD Naive Calibration
            //            accelX = (float) MPU9250_ReadAccelX();
            //            accelY = (float) MPU9250_ReadAccelY();
            //            accelZ = (float) MPU9250_ReadAccelZ();
            //            accelX = (accelX - ACCEL_X_NULL);
            //            accelY = (accelY - ACCEL_Y_NULL);
            //            accelZ = (accelZ - ACCEL_Z_NULL);
            //            //            accel[0][0] = accelX;
            //            //            accel[1][0] = accelY;
            //            //            accel[2][0] = accelZ;


            magX = (float) MPU9250_ReadMagX();
            magY = (float) MPU9250_ReadMagY();
            magZ = (float) MPU9250_ReadMagZ();
            // OLD Naive callibration 
            //            magX = (magX - MAG_X_NULL);
            //            magY = (magY - MAG_Y_NULL);
            //            magZ = (magZ - MAG_Z_NULL);

            magVec[0][0] = magX;
            magVec[1][0] = magY;
            magVec[2][0] = magZ;

            // CorrectEllipsoid.m
            MatrixMultiplyVector(magScale, magVec, magVecScaled);
            VectorAdd(magVecScaled, magNullVec, magVecShifted);
            magReading[0][0] = magVecShifted[0][0];
            magReading[1][0] = magVecShifted[1][0];
            magReading[2][0] = magVecShifted[2][0];

            //printf("%f, %f, %f\n", magReading[0][0], magReading[1][0], magReading[2][0]);
            //            sprintf(str, "%f, %f, %f\n", magReading[0][0], magReading[1][0], magReading[2][0]);


            // Align magnetometer to accelerometer coordinate frame
            MatrixTranspose(Rmis, RmisT);
            //            MatrixMultiplyVector(Rmis, magReading, magReadingAligned);
            MatrixMultiplyVector(RmisT, magVecShifted, magReadingAligned);

            /*******************************************************/
            //Moving Average and Calculations (rol, pit, magHeading, tilt correction)
            /*******************************************************/

            // simple moving average
            // (1) remove oldest element from data array           
            pitchSum = (pitchSum - pitch[i]);
            rollSum = (rollSum - roll[i]);
            compassSum = (compassSum - compass[i]);

            // calculate roll and pitch
            //            roll[i] = atan2(accelY, (sqrt(accelX * accelX + accelZ * accelZ)));
            //            pitch[i] = atan2(-accelX, accelZ);
            // (2) insert newest data point
            roll[i] = atan2(accelReading[1][0], (sqrt(accelReading[0][0] * accelReading[0][0] + accelReading[2][0] * accelReading[2][0])));
            pitch[i] = atan2(-accelReading[0][0], accelReading[2][0]);

            // tilt correction to magReadings (must be normalized for these methods)
            magXCorr = magReadingAligned[0][0] * cos(pitch[i]) + magReadingAligned[2][0] * sin(pitch[i]);
            magYCorr = magReadingAligned[0][0] * sin(roll[i]) * sin(pitch[i]) + magReadingAligned[1][0] * cos(roll[i]) - magReadingAligned[2][0] * sin(roll[i]) * cos(pitch[i]);

            // calculate compass heading & convert to cardinal coord
            // 3 options: raw, aligned to accel(rot90), aligned & tilt corrected  
            rawCompassHeading = atan2(-magReading[1][0], magReading[0][0]) * radToDeg;
            alignedCompassHeading = atan2(magReadingAligned[1][0], magReadingAligned[0][0]) * radToDeg;
            magHeading = atan2(magYCorr, magXCorr) * radToDeg;

            // correct range of atan2 [-180, 180] to cardinal
            if (alignedCompassHeading < 0)
                alignedCompassHeading += 360;
            if (magHeading < 0)
                magHeading += 360;

            // (2) insert newest data point
            //            compass[i] = rawCompassHeading;
            //            compass[i] = alignedCompassHeading;
            compass[i] = magHeading;

            // OR use Luke's alternative circular moving average
            //            setcompassDegree(alignedCompassHeading);
            if (magHeading < 360 && magHeading > 0)
                setcompassDegree(magHeading);

            // (3) resum w newest element
            pitchSum = pitchSum + pitch[i];
            rollSum = rollSum + roll[i];
            compassSum = compassSum + compass[i];

            // (4) calculate moving average
            pitchAvg = pitchSum / MOVING;
            rollAvg = rollSum / MOVING;
            compassAvg = compassSum / MOVING;

            i++;
            /*******************************************************/
            /**************** PRINT OPTIONS ************************/

            //            sprintf(str, "%f\n", compassAvg);
            //            printf("%f, %f, %f\n", accelReading[0][0], accelReading[1][0], accelReading[2][0]);
            //            printf("%d, %d, %d, %d, %d, %d\n", MPU9250_ReadAccelX(), MPU9250_ReadAccelY(), MPU9250_ReadAccelZ(), MPU9250_ReadMagX(), MPU9250_ReadMagY(), MPU9250_ReadMagZ());
            //            sprintf(str, "r  = %.1f p = %.1f\n %.1f\n %.1f\n %.1f\n", rollAvg*radToDeg, pitchAvg*radToDeg, rawCompassHeading, alignedCompassHeading, compassAvg);
            //sprintf(str, "r  = %.1f p = %.1f\r\n %.1f\r\n %.1f     %.1f\r\n %.1f\r\n", rollAvg*radToDeg, pitchAvg*radToDeg, rawCompassHeading, alignedCompassHeading, magHeading, getcompassDegree());
            //            sprintf(str, "r  = %.1f p = %.1f\n %.1f\n %.1f\n %.1f\n", rollAvg*radToDeg, pitchAvg*radToDeg, rawCompassHeading, alignedCompassHeading, magHeading);
            //            sprintf(str, "rol = %.2f\npit = %.2f\r\n", roll[i], pitch[i]);
            //            printf("roll = %.2f pitch = %.2f yaw = %.2f\r\n", roll * 180 / 3.14, pitch * 180 / 3.14, yaw * 180 / 3.14);
            
            sprintf(str, "raw: %.2f \t avg: %.2f \r\n", magHeading, getcompassDegree());
            for(i = 0; i < strlen(str); ++i)
                PutChar(1, str[i]);
            
            for (i = 0; i < 1000000; ++i);
//            OledClear(OLED_COLOR_BLACK);
//            OledDrawString(str);
//            OledUpdate();
            prev = TIMERS_GetMilliSeconds();
        }

    }
}
