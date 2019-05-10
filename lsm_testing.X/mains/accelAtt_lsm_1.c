/*
 * File:   accelAtt_1.c
 * Author: Joe
 *
 * Created on May 9, 2019, 2:14 AM
 */

#include "xc.h"
#include <BOARD.h>
#include <I2C.h>
#include <AD.h>
#include <timers.h>
#include <stdio.h>
#include <LSM9DS1.h>
#include "LSM9DS1_func.h"
#include <stdlib.h>
#include <Oled.h>
#include <OledDriver.h>
#include <MatrixMath.h>
#include <math.h>

//LSM SETTINGS
#define ACCEL_X_NULL 0	// no accel null shifts?
#define ACCEL_Y_NULL 0
#define ACCEL_Z_NULL 0
#define ACCEL_SENS_SCALE 0.732    //+/- 16g
//#define ACCEL_SENS_SCALE 0.061      //+/- 2g

//MPU SETTINGS
//#define SENS_SCALE 16384
//#define ACCEL_X_NULL 468.5036331
//#define ACCEL_Y_NULL 230.9540918
//#define ACCEL_Z_NULL 580.4147557

#define DELTA_T 10
#define INT_POWA 100000
#define MOVING 16

int main(void) {
    BOARD_Init();
    TIMERS_Init();
    OledInit();
    AD_Init();
    LSM9DS1_Init();

    int delay = 500;
    uint32_t i, j, k, loopStep = 0;

    float deltaT = DELTA_T / 1000;
    float rollAvg, pitchAvg, rollSum = 0, pitchSum = 0, accelX, accelY, accelZ;
    float convToDeg = 90 * INT_POWA / SENS_SCALE;

    char str[100] = "startup";

    float accel[3][1] = {};
    float roll[MOVING] = {};
    float pitch[MOVING] = {};

    // fill up moving avg array once in beginning
    for (i = 0; i < MOVING; i++) {
        accelX = (float) LSM9DS1_ReadAccelX();
        accelY = (float) LSM9DS1_ReadAccelY();
        accelZ = (float) LSM9DS1_ReadAccelZ();
        accelX = (accelX - ACCEL_X_NULL);
        accelY = (accelY - ACCEL_Y_NULL);
        accelZ = (accelZ - ACCEL_Z_NULL);
        pitch[i] = -convToDeg * accelX / INT_POWA;
        pitchSum += pitch[i];
        roll[i] = convToDeg * accelY / INT_POWA;
        rollSum += roll[i];
        //        printf("%0.2f, %0.2f\n", roll[i], pitch[i]);
    }
    //    printf("RS%0.2f, PS%0.2f\n", rollSum, pitchSum);
    //    rollAvg = (rollSum * INT_POWA) / MOVING / INT_POWA;
    //    pitchAvg = (pitchSum * INT_POWA) / MOVING / INT_POWA;
    rollAvg = (rollSum) / MOVING;
    pitchAvg = (pitchSum) / MOVING;
    //    printf("RAVG%0.2f, PAVG%0.2f\n", rollAvg, pitchAvg);


    i = 0;
    while (1) {

        if (TIMERS_GetMilliSeconds() >= delay) {
            // clock over array index at modulo moving points
            if ((i % MOVING) == 0)
                i = 0;
            accelX = (float) LSM9DS1_ReadAccelX();
            accelY = (float) LSM9DS1_ReadAccelY();
            accelZ = (float) LSM9DS1_ReadAccelZ();
            accelX = (accelX - ACCEL_X_NULL);
            accelY = (accelY - ACCEL_Y_NULL);
            accelZ = (accelZ - ACCEL_Z_NULL);
            //            accel[0][0] = accelX;
            //            accel[1][0] = accelY; // minus for Y to be E?
            //            accel[2][0] = accelZ; // minus for Z to be D?
            
            // remove oldest element           
            pitchSum = (pitchSum - pitch[i]);
            rollSum = (rollSum - roll[i]);
            
            // calculate newest element
            pitch[i] = -convToDeg * accelX / INT_POWA;
            roll[i] = convToDeg * accelY / INT_POWA;
            
            // resum w newest element
            pitchSum = pitchSum + pitch[i];
            rollSum = rollSum + roll[i];
            
            // calc moving avg
            pitchAvg = pitchSum / MOVING;
            rollAvg = rollSum / MOVING;
            i++;
            
            // not averaged data
            //            pitchAvg= -convToDeg * accelX / INT_POWA;
            //            rollAvg= convToDeg * accelY / INT_POWA;

            printf("%0.2f, %0.2f\n", rollAvg, pitchAvg);
            //printf("%f, %f, %f\n", accel[0][0], accel[1][0], accel[2][0]);
            sprintf(str, "rol = %.2f\npit = %.2f\r\n", rollAvg, pitchAvg);

            //            printf("roll = %.2f pitch = %.2f yaw = %.2f\r\n", roll * 180 / 3.14, pitch * 180 / 3.14, yaw * 180 / 3.14);
            OledClear(OLED_COLOR_BLACK);
            OledDrawString(str);
            OledUpdate();
            delay += 10;
        }
    }

    return 0;

}
