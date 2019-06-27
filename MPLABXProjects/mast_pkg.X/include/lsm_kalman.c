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
#define DELTA_T 0.04

float kalmanX(float accAngle, float gyrRate);
float kalmanY(float accAngle, float gyrRate);

// PUT IN VARS.h
float XP_00 = 0, XP_01 = 0, XP_10 = 0, XP_11 = 0;
float YP_00 = 0, YP_01 = 0, YP_10 = 0, YP_11 = 0;
float ZP_00 = 0, ZP_01 = 0, ZP_10 = 0, ZP_11 = 0;
float KFangleX = 0.0;
float KFangleY = 0.0;
float KFangleZ = 0.0;
float cX = 0, cY = 0;

float Q_angle  =  0.01;
float Q_gyro   =  0.0003;
float R_angle  =  0.01;
float x_bias = 0;
float y_bias = 0;
float z_bias = 0;

int main(void){
    int i,j,k;
    char status[100];
    
    BOARD_Init();
    AD_Init();
    //LSM9DS1_Init();
    AD_AddPins(AD_A2);
    INCAP_Init();
    TIMERS_Init();
    
    if (!LSM9DS1_Init()) {
        sprintf(status, "ERROR\n");
        for(i = 0; i < strlen(status); ++i)
            PutChar(2, status[i]);
    }
    
    // put in vars.h later
    float gyro_rate_x, gyro_rate_y, gyro_rate_z;
    float gyro_raw_x, gyro_raw_y, gyro_raw_z;
    
    float acc_raw_x, acc_raw_y, acc_raw_z;
    float acc_x, acc_y, acc_z;
    
    char str[100] = "startup";
    while (1) {

        if (TIMERS_GetMilliSeconds() >= attEstDelay) {
            loopStep++;
            //printf("%d;%d;%d\r\n", LSM9DS1_ReadGyroX(), LSM9DS1_ReadGyroY(), LSM9DS1_ReadGyroZ());

            // Read raw gyro and accel vals
            gyro_raw_x = (float) LSM9DS1_ReadGyroX();
            gyro_raw_y = (float) LSM9DS1_ReadGyroY();
            gyro_raw_z = -(float) LSM9DS1_ReadGyroZ();
            acc_raw_x = (float) LSM9DS1_ReadAccelX();
            acc_raw_y = (float) LSM9DS1_ReadAccelY();
            acc_raw_z = (float) LSM9DS1_ReadAccelZ();

            // Convert gyro raw to dps
            gyro_rate_x = (gyroX - biasX) * SENS_SCALE / 1000; //1000 necessary to convert from mdps to dps
            gyro_rate_y = (gyroY - biasY) * SENS_SCALE / 1000;
            gyro_rate_z = (gyroZ - biasZ) * SENS_SCALE / 1000;
            
            // Convert gyro dps to angle
            gyroX = gyroX + gyro_rate_x * DELTA_T;
            gyroY = gyroY + gyro_rate_y * DELTA_T;
            gyroZ = gyroZ + gyro_rate_z * DELTA_T;

            // Convert accel raw to degrees
//            accelX = (accelX - ACCEL_X_NULL) * ACCEL_SENS_SCALE / 1000;
//            accelY = (accelY - ACCEL_Y_NULL) * ACCEL_SENS_SCALE / 1000;
//            accelZ = (accelZ - ACCEL_Z_NULL) * ACCEL_SENS_SCALE / 1000;
            acc_x = (atan2(acc_raw_y, acc_raw_z)+M_PI)*180/M_PI;
            acc_y = (atan2(acc_raw_z, acc_raw_x)+M_PI)*180/M_PI;
            acc_z = (atan2(acc_raw_y, -acc_raw_x)+M_PI)*180/M_PI; //??
            
            acc_x -= 180;
            if(acc_y > 90)
                acc_y -= 270;
            else
                acc_y += 90;
            
            // Kalman
            float kX = kalmanX(acc_x, gyro_rate_x);
            float kY = kalmanX(acc_y, gyro_rate_y);
            sprintf(str, "X: %.2f  Y: %.2f\r\n", kX, kY);
            for(i = 0; i < strlen(str); ++i)
                PutChar(2, str[i]);
            
            // Complementary
//            cX = 0.97*(cX+gyro_rate_x*DELTA_T)+(1-0.97)*acc_x;
//            cY = 0.97*(cY+gyro_rate_y*DELTA_T)+(1-0.97)*acc_y;          
//            sprintf(str, "%.2f  %.2f\r\n", cX, cY);
//            for(i = 0; i < strlen(str); ++i)
//                PutChar(2, str[i]);

            attEstDelay += DELTA_T * 1000;
        }

    }

}

float kalmanX(float accAngle, float gyrRate){
    float  y, S;
	float K_0, K_1;

	KFangleX += DELTA_T * (gyrRate - x_bias);

	XP_00 +=  -DELTA_T * (XP_10 + XP_01) + Q_angle * DELTA_T;
	XP_01 +=  -DELTA_T * XP_11;
	XP_10 +=  -DELTA_T * XP_11;
	XP_11 +=  Q_gyro * DELTA_T;

	y = accAngle - KFangleX;
	S = XP_00 + R_angle;
	K_0 = XP_00 / S;
	K_1 = XP_10 / S;

	KFangleX +=  K_0 * y;
	x_bias  +=  K_1 * y;
	XP_00 -= K_0 * XP_00;
	XP_01 -= K_0 * XP_01;
	XP_10 -= K_1 * XP_00;
	XP_11 -= K_1 * XP_01;

	return KFangleX;
}

float kalmanY(float accAngle, float gyrRate){
    float  y, S;
	float K_0, K_1;

	KFangleY += DELTA_T * (gyrRate - y_bias);

	YP_00 +=  -DELTA_T * (YP_10 + YP_01) + Q_angle * DELTA_T;
	YP_01 +=  -DELTA_T * YP_11;
	YP_10 +=  -DELTA_T * YP_11;
	YP_11 +=  Q_gyro * DELTA_T;

	y = accAngle - KFangleY;
	S = YP_00 + R_angle;
	K_0 = YP_00 / S;
	K_1 = YP_10 / S;

	KFangleY +=  K_0 * y;
	y_bias  +=  K_1 * y;
	YP_00 -= K_0 * YP_00;
	YP_01 -= K_0 * YP_01;
	YP_10 -= K_1 * YP_00;
	YP_11 -= K_1 * YP_01;

	return KFangleY;
}