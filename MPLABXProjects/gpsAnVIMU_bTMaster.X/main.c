#include "serialcomm.h"
#include "gpsLib.h"
#include <GenericTypeDefs.h>
#include <string.h>
#include <plib.h>
#include <peripheral/i2c.h>
#include <AD.h>
#include "xc.h"
#include "BOARD.h"
#include <stdio.h>
#include "stdlib.h"
#include "Oled.h"
#include "OledDriver.h"
#include <math.h>
#include <INPUT_CAPTURE.h>
#include "I2C.h"
#include "LSM9DS1_func.h"
#include "DCM.h"
#include "MatrixFunctions.h"
#include "OpenLoopIntegration.h"
#include "ClosedLoopIntegration.h"
#include "serial.h"


#pragma config FPLLODIV = DIV_1, FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FWDTEN = OFF, FCKSM = CSECME, FPBDIV = DIV_1
#pragma config OSCIOFNC = ON, POSCMOD = XT, FSOSCEN = ON, FNOSC = PRIPLL
#pragma config CP = OFF, BWP = OFF, PWP = OFF

/*#define GyroScale245 8.75
#define GyroXShift245 -37.83632735
#define GyroYShift245 -154.6309381
#define GyroZShift245 -171.2355289
#define AccelScale 0*/
#define SENS_SCALE 8.75 //for LSM9DS1  -- 8.75 mdps/LSB
#define timer_delay 50

int main(void){
    
    BOARD_Init();
    AD_Init();
    
    OledInit();
    LSM9DS1_Init();
    AD_AddPins(AD_A2);
    INCAP_Init();
    TIMERS_Init();
    
    float freq = 0, degree = 0, windSpeed = 0;
    unsigned int degVal = 0, numSamples = 0;
    int g = 0, m = 0, n = 0, p = 0, x = 0, count = 0, delay2 = 50;
    int e = 0, f = 0, a = 0, b = 0, c = 0, d = 0, l = 0, j = 0, k = 0, i = 0;
    int delay = 100;
    
    // necessary matrices
    float ID[3][3] = {{1,0,0},{0,1,0},{0,0,1}}, Rexp[3][3] = {{1,0,0},{0,1,0},{0,0,1}}; 
    float RCopy[3][3], RPlus[3][3] = {{1,0,0},{0,1,0},{0,0,1}}; // RPlus is RMinus
    float orthoR[3][3] = {{1,0,0},{0,1,0},{0,0,1}}, rotXY[3][3] = {{1,0,0},{0,1,0},{0,0,1}}; 
    float Ro[3][3] = {{1,0,0},{0,1,0},{0,0,1}}, magVec[3][1] = {0,0,0}; 
    float realGyro[3][1] = {0,0,0}, realGyroCopy[3][1] = {0,0,0}, eR[3][1] = {0,0,0};
    
    // Angle holding variables
    double decpitch = 0.0, decyaw = 0.0, decroll = 0.0; 
    double prevpitch = 0.0, prevyaw = 0.0, prevroll = 0.0;
    double finalpitch = 0.0, finalyaw = 0.0, finalroll = 0.0;
    double rollbuffer[10] = {0,0,0,0,0,0,0,0,0,0};
    double pitchbuffer[10] = {0,0,0,0,0,0,0,0,0,0};
    double yawbuffer[10] = {0,0,0,0,0,0,0,0,0,0};
    double Angle[3] = {0,0,0};
    
    // scaling factors and null shifts
    float GyroScale245 = 8.75, GyroXShift245 = -37.83632735, GyroYShift245 = -154.6309381, GyroZShift245 = -171.2355289;
    float GyroScale500 = 17.50, GyroXShift500 = 32.05788423, GyroYShift500 = -105.6007984, GyroZShift500 = -46.93213573;
    float AccelScale2G = 0.061;
    float GyroDriftRateVal = 0.1;
    
    // tuning factors: determine how much mag and accel data affect the gyro
    //float kp_a = 1.5, kp_m = 0.3;
    //float kp_a = 1.5, kp_m = 0;
    //float kp_a = 1.75, kp_m = 2.25;
    //float kp_a = 0.5, kp_m = 0.05;
    float kp_a = 0, kp_m = 0;
    float ki_a = kp_a/10, ki_m = kp_m/10;
    
    // matrices from calibration matlab code
    float RMisTumbleID[3][3] = {{0.9910, -0.1120, 0.0732},
                                {0.1108, 0.9936, 0.0196},
                                {-0.0749, -0.0113, 0.9971}};
    float RMisTumbleT[3][3], magCorr[3][1], accCorr[3][1], aAC[3][1], mAC[3][1], magInCorr[3][1];
    
    float AAtil[3][3] = {{0.000732285369703595, -0.000000702045626005923, -0.00000215685361893536},
    {-0.000000756863377998983, 0.00073368834997813, 0.0000009774345812771},
    {-0.00000283590738104761, 0.00000118233111829483, 0.000733824372524157}};
    float ABtil[3][1] = {{0.0238}, {-0.0188}, {-0.0292}}; 
    float MAtil[3][3] = {{0.000619460440592813, 0.000039945059541213, -0.0000038989641442371},
    {0.0000557313444001783, 0.000754921822811573, 0.000010010991967113},
    {-0.000010575514982454, 0.0000114848181943713, 0.000772307195373597}};
    float MBtil[3][1] = {{0.0126},{0.1213},{-0.9658}};
    
    float Mi[3][1] = {{0},{0},{1}};
    float Si[3][1] = {{-22793},{5340.6},{-41578}};
    float magInertial[3][1] = {{0}, {0}, {1}};
    float accelInertial[3][1] = {{0}, {0}, {1}};
    float accelData[3][1] = {{0}, {0}, {1}};
    
    // data holding variables
    float GXData = 0, GYData = 0, GZData = 0;
    float AXData = 0, AYData = 0, AZData = 0;
    float MXData = 0, MYData = 0, MZData = 0;
    float gyroX, gyroY, gyroZ;
    float biasX = 17, biasY = 30, biasZ = -45; // gyro biases
    
    float biasEst[3][1] = {{0},{0},{0}};
    float bias[3][1] = {{(0)}, {(0)}, {(0)}};
    
    char heading[100];
    
    char str1[200];
    UINT32 rx1_size=0;
    UINT8 str2[1024];
    UINT32 rx2_size;
    
    char  test[] = {
        "0123456789\r\n"
    };
    char gnost[100];
    char gntst[100];
    char gpsPacket[100];
    memset(str2, '\0', sizeof(str2));
    strcpy(str2, test);
    rx1_size = 0;
    //int i=0, j=0;
    while(1){    
       // j++;
        if(UpdateDataBuffer(1, 100)){
        //if (j == 100000){
            j=0;
            GetDataBuffer(1, gpsPacket);
            processSentence(gpsPacket);
           // createGNOST(gnost);
            createGNTST(gntst);
//            for(i = 0; i < strlen(gnost); i++){
//                PutChar(2, gnost[i]);
//            }
            //while(!IsTransmitEmpty(2));
            for(i = 0; i < strlen(gntst); i++){
                PutChar(2, gntst[i]);
            }
        }
        
        // accumulate average over delay period
        if (delay >= TIMERS_GetMilliSeconds()) {
            degVal += AD_ReadADPin(AD_A2);
            freq += INCAP_getFreq()/1000.000;
            numSamples++;
            
        }else{
            delay += 50;        
            degree = (((float)((float)degVal/numSamples)) - 1034.486486)/-2.942303732;
            freq = freq/numSamples;
            windSpeed = (freq + .00185)/0.524;

            setWindSpeed(windSpeed);
            setWindDegree(degree);
            
            numSamples = 0;
            degVal = 0;
            freq = 0;
        }
        
        if(TIMERS_GetMilliSeconds() >= delay2){
            
            // this is for gyro sensitivity of 245 mdps
            GXData = (float)(((LSM9DS1_ReadGyroX()-(GyroXShift245))*(GyroScale245/1000))*(3.14159/180));
            GYData = (float)(((LSM9DS1_ReadGyroY()-(GyroYShift245))*(GyroScale245/1000))*(3.14159/180));
            GZData = (float)(((LSM9DS1_ReadGyroZ()-(GyroZShift245))*(GyroScale245/1000))*(3.14159/180));
            
            // this is for gyro sensitivity of 500 mdps
            /*GXData = (float)(((LSM9DS1_ReadGyroX()-(GyroXShift500))*(GyroScale500/1000))*(3.14159/180));
            GYData = (float)(((LSM9DS1_ReadGyroY()-(GyroYShift500))*(GyroScale500/1000))*(3.14159/180));
            GZData = (float)(((LSM9DS1_ReadGyroZ()-(GyroZShift500))*(GyroScale500/1000))*(3.14159/180));
            */
            
            // for accel scaled to +/- 2G sensitivity
            /*AXData = (float)((LSM9DS1_ReadAccelX())*(AccelScale2G/1000));
            AYData = (float)((LSM9DS1_ReadAccelY())*(AccelScale2G/1000));
            AZData = (float)((LSM9DS1_ReadAccelZ())*(AccelScale2G/1000));
            */
            
            AXData = (float)((LSM9DS1_ReadAccelX()));
            AYData = (float)((LSM9DS1_ReadAccelY()));
            AZData = (float)((LSM9DS1_ReadAccelZ()));
            
            MXData = (float)((LSM9DS1_ReadMagX()));
            MYData = (float)((LSM9DS1_ReadMagY()));
            MZData = (float)((LSM9DS1_ReadMagZ()));
            
            float GyroIn[3][1] = {{GXData},{GYData},{-1*(GZData)}}; // use this for actual
            //float vec1[3][1] = {{0},{0},{0}}; // use this to check orthonormal
            float vec2[3][1] = {{AXData},{AYData},{(-1*AZData)}};
            //float vec2[3][1] = {{0},{0},{-1}};
            float vec3[3][1] = {{(-1*MXData)},{MYData},{(-1*MZData)}};
           
            
            MatVecMultiply(AAtil, vec2, aAC, 3, 3, 3);
            MatVecMultiply(MAtil, vec3, mAC, 3, 3, 3);
            for(i = 0; i < 3; i++){
                magCorr[i][0] = mAC[i][0] + MBtil[i][0];
                accCorr[i][0] = aAC[i][0] + ABtil[i][0];
            }
            
            MatrixTranspose(RMisTumbleID, RMisTumbleT);
            MatVecMultiply(RMisTumbleT, magCorr, magVec, 3, 3, 3);
            MatVecMultiply(RMisTumbleT, magInertial, magInCorr, 3, 3, 3);
            
            
            //IntegrateOpenLoop(RPlus, realGyroCopy, RPlus, 0.05, 1); // working version
          
            IntegrateClosedLoop(RPlus, biasEst, GyroIn, vec3, vec2, 
            magInertial, accelInertial, 0.05, kp_a, kp_m, ki_a, ki_m, 
            RPlus, biasEst);
            
            //printf("\r\n");
            /*char out1[200], out2[200], out3[200];
            sprintf(out1, "Line 1: %.1f, %.1f, %.1f\r\n", BetterR[0][0], BetterR[0][1], BetterR[0][2]);
            for(i = 0; i < strlen(out1); ++i){
                PutChar(2, out1[i]);
            }
            sprintf(out2, "Line 2: %.1f, %.1f, %.1f\r\n", BetterR[1][0], BetterR[1][1], BetterR[1][2]);
            for(j = 0; j < strlen(out2); ++j){
                PutChar(2, out2[j]);
            }
            sprintf(out3, "Line 3: %.1f, %.1f, %.1f\r\n", BetterR[2][0], BetterR[2][1], BetterR[2][2]);
            //sprintf(out, "%.1f, %.1f, %.1f\r\n", decroll, decpitch, decyaw);
            for(k = 0; k < strlen(out3); ++k){
                PutChar(2, out3[k]);
            }*/
            
            // use identity matrix for initial dcm
            ExtractEulerFromDCM(RPlus, Angle);
            //decroll = Angle[0]-22.5, decpitch = Angle[1]-18.5, decyaw = Angle[2]-50.5;
            decroll = Angle[0], decpitch = Angle[1], decyaw = Angle[2];
            
            // account for gyro drift on all axes
            if((decroll-prevroll) < 0){
                finalroll = decroll+GyroDriftRateVal;
                prevroll = decroll;
            } else if((decroll-prevroll) == 0){
                finalroll = decroll;
                prevroll = decroll;
            } else {
                finalroll = decroll-GyroDriftRateVal;
                prevroll = decroll;
            }
            
            if((decpitch-prevpitch) < 0){
                finalpitch = decpitch+GyroDriftRateVal;
                prevpitch = decpitch;
            } else if((decpitch-prevpitch) == 0){
                finalpitch = decpitch;
                prevpitch = decpitch;
            } else {
                finalpitch = decpitch-GyroDriftRateVal;
                prevpitch = decpitch;
            }
            
            if((decyaw-prevyaw) < 0){
                finalyaw = decyaw+GyroDriftRateVal;
                prevyaw = decyaw;
            } else if((decyaw-prevyaw) == 0){
                finalyaw = decyaw;
                prevyaw = decyaw;
            } else {
                finalyaw = decyaw-GyroDriftRateVal;
                prevyaw = decyaw;
            }
            
            if(g < 10){
                rollbuffer[g] = finalroll;
                pitchbuffer[g] = finalpitch;
                yawbuffer[g] = finalyaw;
                g++;
            } else {
                rollbuffer[g] = finalroll;
                pitchbuffer[g] = finalpitch;
                yawbuffer[g] = finalyaw;
                g = 0;
            }
            
            double trueroll = (rollbuffer[0]+rollbuffer[1]+rollbuffer[2]
            +rollbuffer[3]+rollbuffer[4]+rollbuffer[5]+rollbuffer[6]
            +rollbuffer[7]+rollbuffer[8]+rollbuffer[9])/10;
            
            double truepitch = (pitchbuffer[0]+pitchbuffer[1]+pitchbuffer[2]
            +pitchbuffer[3]+pitchbuffer[4]+pitchbuffer[5]+pitchbuffer[6]
            +pitchbuffer[7]+pitchbuffer[8]+pitchbuffer[9])/10;
            
            double trueyaw = (yawbuffer[0]+yawbuffer[1]+yawbuffer[2]
            +yawbuffer[3]+yawbuffer[4]+yawbuffer[5]+yawbuffer[6]
            +yawbuffer[7]+yawbuffer[8]+yawbuffer[9])/10;
            
            /*char out[200];
            sprintf(out, "%.1f, %.1f, %.1f\r\n", GXData, GYData, GZData);
            //printf("%.1f, %.1f, %.1f\r\n", finalroll, finalpitch, finalyaw);
            for(i = 0; i < strlen(out); ++i){
                PutChar(2, out[i]);
            }
            */
            char out[200];
            sprintf(out, "%.1f, %.1f, %.1f\r\n", trueroll, truepitch, trueyaw);
            //sprintf(out, "%.1f, %.1f, %.1f\r\n", decroll, decpitch, decyaw);
            for(i = 0; i < strlen(out); ++i){
                PutChar(2, out[i]);
            }
            
          // IMU cannot run fast if printing with GPS: needs to be at least 10 Hz or slower
            delay2 = delay2 + timer_delay;
        }
    }
    
}