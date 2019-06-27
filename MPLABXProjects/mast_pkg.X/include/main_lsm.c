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
#include "vars_1.h" // all the random variables needed
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

#define SENS_SCALE 70 //for LSM9DS1  -- 2000 mdps/LSB
//#define SENS_SCALE 8.75 //for LSM9DS1  -- 8.75 mdps/LSB
//#define biasX
#define Kp_a 0.7
#define Ki_a 0.05
//#define ACCEL_X_NULL 0	// no accel null shifts?
//#define ACCEL_Y_NULL 0
//#define ACCEL_Z_NULL 0
#define ACCEL_SENS_SCALE 0.732    //+/- 16g
//#define ACCEL_SENS_SCALE 0.061      //+/- 2g
#define DELTA_T 0.05

int main(void){
    int i,j,k;
    char status[100];
    
    BOARD_Init();
    AD_Init();
    //LSM9DS1_Init();
    AD_AddPins(AD_A2);
    INCAP_Init();
    TIMERS_Init();
    
//    if (!LSM9DS1_Init()) {
//        sprintf(status, "ERROR\n");
//        for(i = 0; i < strlen(status); ++i)
//            PutChar(2, status[i]);
//    }
    
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
        
        if(UpdateDataBuffer(1, 100)){
        //if (j == 100000){
            j=0;
            GetDataBuffer(1, gpsPacket);
            processSentence(gpsPacket);
            createGNOST(gnost);
//            createGNTST(gntst);
            for(i = 0; i < strlen(gnost); i++){
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
            freq += INCAP_getFreq()/1000.000;
            numSamples++;
            
        }else{
            delay += 50;        
            degree = ((degVal - 1034.486486)/-2.942303732);
            freq = freq/numSamples;
            windSpeed = (freq + .00185)/0.524;

            setWindSpeed(windSpeed);
            
            degree = -(degree - 360);
            degree = fmod(degree+180, 360);
//            degree = (degree + 180) % (float)360;
            setWindDegree(degree);
            
            numSamples = 0;
            degVal = 0;
            freq = 0;
        }

//        if (TIMERS_GetMilliSeconds() - prev_end >= DELTA_T*1000) {
//            
//            accelX = -(float) LSM9DS1_ReadAccelX() * ACCEL_SENS_SCALE;
//            accelY = -(float) LSM9DS1_ReadAccelY() * ACCEL_SENS_SCALE;
//            accelZ = (float) LSM9DS1_ReadAccelZ() * ACCEL_SENS_SCALE;
//            accelX = (accelX - ACCEL_X_NULL);
//            accelY = (accelY - ACCEL_Y_NULL);
//            accelZ = (accelZ - ACCEL_Z_NULL);
//            //            accel[0][0] = accelX;
//            //            accel[1][0] = accelY; // minus for Y to be E?
//            //            accel[2][0] = accelZ; // minus for Z to be D?
//
//            /*******************************************************/
//            //Moving Average Calculations
//            /*******************************************************/
//         
//
//            roll = atan2(accelY, (sqrt(accelX * accelX + accelZ * accelZ)))*radToDeg;
//            pitch = atan2(-accelX, accelZ)*radToDeg;
//
//            /*******************************************************/
//
//            sprintf(str, "r%.2f\t p%.2f\r\n", roll, pitch);
//            for(i = 0; i < strlen(str); ++i)
//                PutChar(2, str[i]);
//
//            //            printf("roll = %.2f pitch = %.2f yaw = %.2f\r\n", roll * 180 / 3.14, pitch * 180 / 3.14, yaw * 180 / 3.14);
//            prev_end = TIMERS_GetMilliSeconds();
//        }

    }

}