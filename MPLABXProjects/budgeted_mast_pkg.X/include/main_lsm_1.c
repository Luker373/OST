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
//#include "data_processing.h"
#include "timers.h"
#include "LSM9DS1_func.h"
#include <MatrixMath.h>
#include "BOARD.h"
#include <I2C.h>

#pragma config FPLLODIV = DIV_1, FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FWDTEN = OFF, FCKSM = CSECME, FPBDIV = DIV_1
#pragma config OSCIOFNC = ON, POSCMOD = XT, FSOSCEN = ON, FNOSC = PRIPLL
#pragma config CP = OFF, BWP = OFF, PWP = OFF


#define DELTA_T 0.05

int main(void) {
    int i, j, k;
    char status[100];

    BOARD_Init();
    AD_Init();
    AD_AddPins(AD_A2);
    INCAP_Init();
    TIMERS_Init();
    MPU9250_Init();

    float actual_t = 0;
    float prev_end = 0;

    char gnost[100];
    char gntst[100];
    char gpsPacket[100];

    int delay = 100;
    float freq = 0, degree = 0, windSpeed = 0;
    unsigned int degVal = 0, numSamples = 0;


    char str[100] = "startup";
    while (1) {

        if (UpdateDataBuffer(1, 100)) {
            //if (j == 100000){
            j = 0;
            GetDataBuffer(1, gpsPacket);
            processSentence(gpsPacket);
            createGNOST(gnost);
            //            createGNTST(gntst);
            for (i = 0; i < strlen(gnost); i++) {
                PutChar(2, gnost[i]);
            }
            //            for(i = 0; i < strlen(gntst); i++){
            //                PutChar(2, gntst[i]);
            //            }
            //for(i =0; i < 1000; ++i);
        }

        // accumulate average over delay period
        if (delay >= TIMERS_GetMilliSeconds()) {
            degVal = AD_ReadADPin(AD_A2);
            freq += INCAP_getFreq() / 1000.000;
            numSamples++;

        } else {
            delay += 50;
            degree = ((degVal - 1034.486486) / -2.942303732);
            freq = freq / numSamples;
            windSpeed = (freq + .00185) / 0.524;

            setWindSpeed(windSpeed);

            degree = -(degree - 360);
            degree = fmod(degree + 180, 360);
            //            degree = (degree + 180) % (float)360;
            setWindDegree(degree);

            numSamples = 0;
            degVal = 0;
            freq = 0;
        }

        if (TIMERS_GetMilliSeconds() - prev_end >= DELTA_T * 1000) {
            if ((i % MOVING) == 0)
                i = 0;

            accelVec[0][0] = (float) MPU9250_ReadAccelX();
            accelVec[1][0] = (float) MPU9250_ReadAccelY();
            accelVec[2][0] = (float) MPU9250_ReadAccelZ();

            //Correct accelerometer ellipsoid data
            MatrixMultiplyVector(accelScale, accelVec, accelVecScaled);
            VectorAdd(accelVecScaled, accelNullVec, accelVecShifted);
            accelReading[0][0] = accelVecShifted[0][0];
            accelReading[1][0] = accelVecShifted[1][0];
            accelReading[2][0] = accelVecShifted[2][0];
            ?
            magVec[0][0] = (float) MPU9250_ReadMagX();
            magVec[1][0] = (float) MPU9250_ReadMagY();
            magVec[2][0] = (float) MPU9250_ReadMagZ();

            // CorrectEllipsoid.m
            MatrixMultiplyVector(magScale, magVec, magVecScaled);
            VectorAdd(magVecScaled, magNullVec, magVecShifted);
            magReading[0][0] = magVecShifted[0][0];
            magReading[1][0] = magVecShifted[1][0];
            magReading[2][0] = magVecShifted[2][0];

            // Align magnetometer to accelerometer coordinate frame
            MatrixTranspose(Rmis, RmisT);
            MatrixMultiplyVector(RmisT, magVecShifted, magReadingAligned);

            /*******************************************************/
            //Moving Average and Calculations (rol, pit, magHeading, tilt correction)
            /*******************************************************/

            // simple moving average
            // (1) remove oldest element from data array      
            pitchSum = (pitchSum - pitch[i]);
            rollSum = (rollSum - roll[i]);
            //compassSum = (compassSum - compass[i]);

            // calculate roll and pitch
            //      roll[i] = atan2(accelY, (sqrt(accelX * accelX + accelZ * accelZ)));
            //      pitch[i] = atan2(-accelX, accelZ);
            // (2) insert newest data point
            roll[i] = atan2(accelReading[1][0], (sqrt(accelReading[0][0] * accelReading[0][0] + accelReading[2][0] * accelReading[2][0])));
            pitch[i] = atan2(-accelReading[0][0], accelReading[2][0]);

            // tilt correction to magReadings (must be normalized for these methods)
            magXCorr = magReadingAligned[0][0] * cos(pitch[i]) + magReadingAligned[2][0] * sin(pitch[i]);
            magYCorr = magReadingAligned[0][0] * sin(roll[i]) * sin(pitch[i]) + magReadingAligned[1][0] * cos(roll[i]) - magReadingAligned[2][0] * sin(roll[i]) * cos(pitch[i]);

            // calculate compass heading & convert to cardinal coord
            // 3 options: raw, aligned to accel(rot90), aligned & tilt corrected 
            //            rawCompassHeading = atan2(-magReading[1][0], magReading[0][0]) * radToDeg;
            //            alignedCompassHeading = atan2(magReadingAligned[1][0], magReadingAligned[0][0]) * radToDeg;
            magHeading = atan2(magYCorr, magXCorr) * radToDeg;

            // correct range of atan2 [-180, 180] to cardinal
            if (alignedCompassHeading < 0)
                alignedCompassHeading += 360;
            if (magHeading < 0)
                magHeading += 360;

            // (2) insert newest data point
            //      compass[i] = rawCompassHeading;
            //      compass[i] = alignedCompassHeading;
            //      compass[i] = magHeading;

            // OR use Luke's alternative circular moving average
            //      setcompassDegree(alignedCompassHeading);      
            setCompassDegree(magHeading);

            // (3) resum w newest element
            pitchSum = pitchSum + pitch[i];
            rollSum = rollSum + roll[i];
            //            compassSum = compassSum + compass[i];

            // (4) calculate moving average
            pitchAvg = pitchSum / MOVING;
            rollAvg = rollSum / MOVING;
            //            compassAvg = compassSum / MOVING;

            i++;
            /*******************************************************/
            /**************** PRINT OPTIONS ************************/
            
            // ==> sprintf(str, "r = %.1f p = %.1f\n %.1f\n %.1f   %.1f\n %.1f\n", rollAvg*radToDeg, pitchAvg*radToDeg, rawCompassHeading, alignedCompassHeading, magHeading, getcompassDegree());


            prev_end = TIMERS_GetMilliSeconds();
        }

    }

}