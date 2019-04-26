/* 
 * File:   DS1AttitudeEstimationMain.c
 * Author: RARogers
 *
 * Created on March 3, 2019, 10:52 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "xc.h"
#include "BOARD.h"
//#include "Ascii.h"
#include "AD.h"
//#include "Oled.h"
//#include "OledDriver.h"
#include "I2C.h"
//#include "LSM9DS1.h"
#include "LSM9DS1_func.h"
#include "timers.h"
#include "serial.h"
#include "DCM.h"
#include "math.h"
#include "MatrixFunctions.h"
#include "OpenLoopIntegration.h"
#include "ClosedLoopIntegration.h"

/*
 * 
 */

// Notes about lab issues
// 1. Open Loop function adds bias to gyro only once, but function in c
// added it on each iteration: error accrued rapidly
// 2. Values from extract euler function are not accurate w/in 5 decimal places
// 3. mpu heats up when being run, with only 3.3 volt input... which worked fine b4
// Solution to 3: get another mpu, and see if scaling and null shifts work for new one

int main(void) {
    
    BOARD_Init();
    AD_Init();
    //OledInit();
    LSM9DS1_Init();
    TIMERS_Init();
    
     // try having these accurate to 5->8 decimal places ?
    char heading[100];
    int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, k = 0, l = 0, i = 0, j = 0;
    int g = 0, m = 0, n = 0, p = 0, x = 0, count = 0, delay = 20;
    float IDMat[3][3] = {{1,0,0},{0,1,0},{0,0,1}}; // fill this out with values around 90 degrees for each
    
    // clear out matrices on starting
    float newR[3][3] = {{1,0,0},{0,1,0},{0,0,1}}, Rexp[3][3] = {{1,0,0},{0,1,0},{0,0,1}}; 
    float RCopy[3][3] = {{1,0,0},{0,1,0},{0,0,1}}, BetterR[3][3] = {{1,0,0},{0,1,0},{0,0,1}}; 
    float orthoR[3][3] = {{1,0,0},{0,1,0},{0,0,1}}, rotXY[3][3] = {{1,0,0},{0,1,0},{0,0,1}}; 
    float Ro[3][3] = {{1,0,0},{0,1,0},{0,0,1}}, magVec[3][1] = {0,0,0}; 
    float realGyro[3][1] = {0,0,0}, realGyroCopy[3][1] = {0,0,0}, eR[3][1] = {0,0,0};
    
    // Angle holding variables
    double decpitch = 0.0, decyaw = 0.0, decroll = 0.0; 
    double prevroll = 0.0, prevyaw = 0.0, prevpitch = 0.0;
    double finalroll = 0.0, finalyaw = 0.0, finalpitch = 0.0;
    double rollbuffer[10] = {0,0,0,0,0,0,0,0,0,0};
    double pitchbuffer[10] = {0,0,0,0,0,0,0,0,0,0};
    double yawbuffer[10] = {0,0,0,0,0,0,0,0,0,0};
    double Angle[3] = {0,0,0};
    
    float avgGX = 0, avgGY = 0, avgGZ = 0, GX = 0, GY = 0, GZ = 0;
    float AZ = 0, avgAX = 0, avgAY = 0, avgAZ = 0, AX = 0, AY = 0;
    
    //float kp_a = 1.5, kp_m = 1.75;
    //float kp_a = 1.5, kp_m = 0.25; // pitch seems to get 90 rotation, roll rotates rouglhy 80
    // tuning factors: determine how much mag and accel data affect the gyro
    float kp_a = 1.5, kp_m = 0.3;
    //float kp_a = 1.75, kp_m = 2.25;
    float ki_a = kp_a/10, ki_m = kp_m/10;
    //float ki_a = 0/10, ki_m = 0/10;
    //float RMisSi5[3][3] = {{0,1,0},{1,0,0},{0,0,-1}}; // flip x and y, invert z
    //float RMisTumbleID[3][3] = {{0,-1,0}, {-1,0,0}, {0,0,1}};
    //float RMisTumbleID[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    /*float RMisTumbleID[3][3] = {{0.991013606061675, -0.111968515898226, 0.0731784397769429},
                                {0.110819375149583, 0.993647430232131, 0.0195921026064051},
                                {-0.0749072672849209, -0.0113064512838016, 0.997126403956527}};*/
    // multiply mag by this vector transposed, with corrected data
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
    
    // do this in ENU coordinates
    // x is north, y is east, z is down, 
    // so for ENU, x is east, y is north,
    // z is down
    float Mi[3][1] = {{0},{0},{1}};
    float Si[3][1] = {{-22793},{5340.6},{-41578}};
    //float Si[3][1] = {{5.3406},{22.793},{-41.578}};
    //float magData[3][1] = {{1}, {0}, {0}}; // hard code until part 7
    //float magInertial[3][1] = {{1}, {0}, {0}}; //match field vector in santacruz
    //float magInertial[3][1] = {{5.3406}, {22.793}, {-41.578}}; //match field vector in santacruz
    float magInertial[3][1] = {{-22793},{5340.6},{-41578}};
    //float magInertial[3][1] = {{0}, {0}, {1}};
    float accelInertial[3][1] = {{0}, {0}, {1}};
    float accelData[3][1] = {{0}, {0}, {1}};
    //float Si[3][1] = {{5340},{22793},{41578}};
    //float Si2[3][1] = {{5000},{22000},{-40000}};
    
    // data holding variables
    float GXData = 0, GYData = 0, GZData = 0;
    float AXData = 0, AYData = 0, AZData = 0;
    float MXData = 0, MYData = 0, MZData = 0;
    
    float biasEst[3][1] = {{0},{0},{0}};
    //float bias[3][1] = {{(0.1)}, {(0.1)}, {(0.1)}};
    float bias[3][1] = {{(0)}, {(0)}, {(0)}};
   
    for(c = 0; c < 3; c++){
        for(d = 0; d < 3; d++){
            RCopy[c][d] = IDMat[c][d];
        }
    }
    
    
    for(;;){
        
       /* while(TIMERS_GetMilliSeconds() <= 1000){ // ten seconds
        
            GX = GX + (LSM9DS1_ReadGyroX());
            GY = GY + (LSM9DS1_ReadGyroY());
            GZ = GZ + (LSM9DS1_ReadGyroZ());
            AX = AX + (LSM9DS1_ReadAccelX());
            AY = AY + (LSM9DS1_ReadAccelY());
            AZ = AZ + (LSM9DS1_ReadAccelZ());
            
            count++;
        
            avgGX = GX/count;
            avgGY = GY/count;
            avgGZ = GZ/count;
            avgAX = AX/count;
            avgAY = AY/count;
            avgAZ = AZ/count;
            
            //printf("%f, %f, %f\r\n", avgGX, avgGY, avgGZ);
        
        }*/
        
        // need the initial matrix to be an identity to start at zero
        // get angles from it, and then call open loop on those angles.
        // it should be zero, but it may drift
        //if((TIMERS_GetMilliSeconds()-1000) == delay){
        if((TIMERS_GetMilliSeconds()) == delay){
            // divide by 131 for mpu to get into angular velo, then multiply by 
            // end number to put it in radians/sec for program
            // assuming we get gyro rate back out in degrees/sec,
            // we still need to convert to radians
            /*GXData = (float)(((LSM9DS1_ReadGyroX())-(avgGX)))*0.0174533;
            GYData = (float)(((LSM9DS1_ReadGyroY())-(avgGY)))*0.0174533;
            GZData = (float)(((LSM9DS1_ReadGyroZ())-(avgGZ)))*0.0174533;*/
            /*GXData = (float)(((LSM9DS1_ReadGyroX())-(avgGX)));
            GYData = (float)(((LSM9DS1_ReadGyroY())-(avgGY)));
            GZData = (float)(((LSM9DS1_ReadGyroZ())-(avgGZ)));*/
            /*GXData = (float)(((LSM9DS1_ReadGyroX()))*0.0174533);
            GYData = (float)(((LSM9DS1_ReadGyroY()))*0.0174533);
            GZData = (float)(((LSM9DS1_ReadGyroZ()))*0.0174533);*/
           /* printf("%d, %d, %d\r\n", LSM9DS1_ReadGyroX()+17, 
            LSM9DS1_ReadGyroY()+30, LSM9DS1_ReadGyroZ()+45);*/
            
            /*GXData = (float)((((LSM9DS1_ReadGyroX())+12.42341)/10)*(3.14159/180));
            GYData = (float)((((LSM9DS1_ReadGyroY())+33.33777)/10)*(3.14159/180));
            GZData = (float)((((LSM9DS1_ReadGyroZ())+14.23882)/10)*0.0174533);*/
            
            GXData = (float)((((LSM9DS1_ReadGyroX())+17)/100)*(3.14159/180));
            GYData = (float)((((LSM9DS1_ReadGyroY())+30)/100)*(3.14159/180));
            GZData = (float)((((LSM9DS1_ReadGyroZ())+45)/100)*0.0174533);
            // YOU NEED TO SCALE THE GYRO DOWN BOI!!!!
            // corrected accel data
            
            /*AXData = (float)((LSM9DS1_ReadAccelX()-567.4217762));
            AYData = (float)((LSM9DS1_ReadAccelY()-79.33513514));
            AZData = (float)((LSM9DS1_ReadAccelZ()-862.809536));*/
            
            // the 26.2... number shifts the axes to be roughly equal in max magnitude
            /*AXData = (float)((LSM9DS1_ReadAccelX()-avgAX))*0.732;
            AYData = (float)((LSM9DS1_ReadAccelY()-avgAY))*0.732;
            AZData = (float)((LSM9DS1_ReadAccelZ()-avgAZ))*0.732;*/
            /*AXData = (float)((LSM9DS1_ReadAccelX()-avgAX));
            AYData = (float)((LSM9DS1_ReadAccelY()-avgAY));
            AZData = (float)((LSM9DS1_ReadAccelZ()-avgAZ));*/
            AXData = (float)((LSM9DS1_ReadAccelX()));
            AYData = (float)((LSM9DS1_ReadAccelY()));
            AZData = (float)((LSM9DS1_ReadAccelZ()));
            
            // magnetometer data
            MXData = (float)((LSM9DS1_ReadMagX()));
            MYData = (float)((LSM9DS1_ReadMagY()));
            MZData = (float)((LSM9DS1_ReadMagZ()));
            
            //printf("%f, %f, %f, %f, %f, %f\r\n", AXData, AYData, AZData, MXData, MYData, MZData);
            
            float GyroIn[3][1] = {{GXData},{GYData},{(GZData)}}; // use this for actual
            //float vec1[3][1] = {{0},{0},{0}}; // use this to check orthonormal
            float vec2[3][1] = {{AXData},{AYData},{(-1*AZData)}};
            //float vec2[3][1] = {{0},{0},{-1}};
            float vec3[3][1] = {{(-1*MXData)},{MYData},{(-1*MZData)}};
            //float vec1[3][1] = {{1},{2},{3}};
            
            /*printf("%f, %f, %f, %f, %f, %f, %f, %f, %f\r\n", 
            AXData, AYData, (-1*AZData), (-1*MXData), MYData, 
            (-1*MZData), GXData, GYData, (-1*GZData));*/
            
            
            // multiply accel and mag data by correction matrix to scale the data
            // automatically, add B to shift them to correct the data overall
            MatVecMultiply(AAtil, vec2, aAC, 3, 3, 3);
            MatVecMultiply(MAtil, vec3, mAC, 3, 3, 3);
            for(i = 0; i < 3; i++){
                magCorr[i][0] = mAC[i][0] + MBtil[i][0];
                accCorr[i][0] = aAC[i][0] + ABtil[i][0];
            }
            
            MatrixTranspose(RMisTumbleID, RMisTumbleT);
            MatVecMultiply(RMisTumbleT, magCorr, magVec, 3, 3, 3);
            MatVecMultiply(RMisTumbleT, magInertial, magInCorr, 3, 3, 3);
           // MatVecMultiply(RMisTumbleT, accelInertial, magInCorr, 3, 3, 3);
            //MatVecMultiply(RMisSi5T, vec3, magVec, 3, 3, 3);
            // closed loop integration stuff starts here
            
            for(a = 0; a < 3; a++){
                realGyroCopy[a][0] = GyroIn[a][0];
            }
            
            /*for(c = 0; c < 3; c++){
                for(d = 0; d < 3; d++){
                    RCopy[c][d] = IDMat[c][d];
            //printf("%f\n", RCopy[c][d]);
                }
            }*/
    
            ColVecAdd(realGyroCopy, bias, realGyro); // gives us correct values
            
            for(b = 0; b < 3; b++){
                realGyroCopy[b][0] = realGyro[b][0];
            }
            
            // previous version just ran closed loop with uncorrected sensor data.
            // accel was shifted, mag wasmultiplied by the transpose of the rotation matrix
            
            //IntegrateOpenLoop(RCopy, realGyroCopy, BetterR, 0.02, 1); // uncomment for part 2/4
            /*ClosedLoop(bias, GyroIn, magData, vec2, magInertial, accelInertial, 
            nv, ev, dv, 1, kp_a, kp_m, ki_a, ki_m, nnv, nev, ndv, BetterR, biasEst);*/ //Part 5 variant
            ClosedLoop(bias, GyroIn, magVec, accCorr, magInCorr, accelInertial, 
            1, kp_a, kp_m, ki_a, ki_m, BetterR, biasEst); // part 7 variant
            /*ClosedLoop(bias, vec1, magVec, vec2, magInertial, Mi, nv, ev, dv, 1, 
            kp_a, kp_m, ki_a, ki_m, nnv, nev, ndv, BetterR, biasEst);*/
            
            // for dcm triad, just do null shifts and scale factors
            //DCMFromTriad(vec3, vec2, magInertial, accelInertial, BetterR);
            //DCMFromTriad(magCorr, accCorr, magInertial, accelInertial, BetterR);
            
            printf("Rplus matrix is \r\n"); 
            for (i = 0; i < 3; i++){ 
                for (j = 0; j < 3; j++){ 
                    printf("%f ", BetterR[i][j]); 
                }
                printf("\r\n"); 
            }
            printf("\r\n");
            
            //printf("BiasEst matrix is \r\n"); 
            for (l = 0; l < 3; l++){ 
                bias[l][0] = biasEst[l][0]; 
                //printf("%f ", biasEst[l][0]);
                //printf("\r\n"); 
            }
            
            // also uncomment for part 4
            for(e = 0; e < 3; e++){
                for(f = 0; f < 3; f++){
                    RCopy[e][f] = BetterR[e][f];
                }
            }
            
            // use identity matrix for initial dcm
            ExtractEulerFromDCM(BetterR, Angle);
            //decroll = Angle[0]-22.5, decpitch = Angle[1]-18.5, decyaw = Angle[2]-50.5;
            decroll = Angle[0], decpitch = Angle[1], decyaw = Angle[2];
            
            // use this for arduino plotting program (real time graph of angles)
            //sprintf(s, "");
            //printf("%f %f %f \r\n",decroll, decpitch, decyaw);
            //while(!IsTransmitEmpty());
            
            //OledClear(1);
            /*sprintf(heading, "R = %.3f,\r\n P = %.3f,\r\n Y = %.3f\r\n", decroll, decpitch, decyaw);
            OledDrawString(heading);*/
            /*sprintf(heading, "R = %.1f,\r\n P = %.1f,\r\n Y = %.1f\r\n", decroll, decpitch, decyaw);
            OledDrawString(heading);
            OledUpdate();*/
            
            // the below if statements attempt to stabilize the output angle 
            // of the IMU
            
            //if((abs(decroll-prevroll) >= 1) && (abs(decroll-prevroll) <= 100)){
            /*if((abs(decroll-prevroll) >= 100)){
                prevroll = decroll;
            //} else if(abs(decroll-prevroll) > 100){
            //    decroll = prevroll;
            } else {
                finalroll = decroll;
                prevroll = finalroll;
            //printf("%d  \n", prevtime);
            }*/
            
            if(g < 10){
                rollbuffer[g] = decroll;
                pitchbuffer[g] = decpitch;
                yawbuffer[g] = decyaw;
                g++;
            } else {
                rollbuffer[g] = decroll;
                pitchbuffer[g] = decpitch;
                yawbuffer[g] = decyaw;
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
            
            /*if(abs(decpitch-prevpitch) >= 0.01){
                prevpitch = decpitch;
            } else {
                finalpitch = decpitch;
                prevpitch = finalpitch;
            //printf("%d  \n", prevtime);
            }
            
            if(abs(decyaw-prevyaw) >= 0.01){
                prevyaw = decyaw;
            } else {
                finalyaw = decyaw;
                prevyaw = finalyaw;
            //printf("%d  \n", prevtime);
            }*/
            
            printf("%.1f, %.1f, %.1f\r\n", trueroll, truepitch, trueyaw);
            //printf("%.1f, %.1f, %.1f\r\n", finalroll, finalpitch, finalyaw);
          
            delay = delay + 20;
        }
    }
    
}

//float nv[3][1] = {{1},{0},{0}};
    //float ev[3][1] = {{0},{-1},{0}};
    //float dv[3][1] = {{0},{0},{-1}};
    //float nnv[3][1], nev[3][1], ndv[3][1];

/*printf("Result matrix is \n"); 
    for (i = 0; i < 3; i++){ 
        for (j = 0; j < 3; j++){ 
           printf("%f ", res1[i][j]); 
        }
        printf("\n"); 
    }*/
    
    //ExtractEulerFromDCM(DCM1, Angle);
    
    //decpitch = Angle[0], decyaw = Angle[1], decroll = Angle[2];
    //pitch = (int)Angle[0], yaw = (int)Angle[1], roll = (int)Angle[2];
    
//rexp(vec1, Rexp);
    
            /*for(a = 0; a < 3; a++){
                realGyroCopy[a][0] = vec1[a][0];
            }
    
            ColVecAdd(realGyroCopy, bias, realGyro); // gives us correct values
            
            for(b = 0; b < 3; b++){
                realGyroCopy[b][0] = realGyro[b][0];
            //printf("%f\n", realGyroCopy[b][0]);
            //printf("\n");
            }
        
            // 100 Hz sample rate, set time change to 0.1 to reflect deg/sec
            IntegrateOpenLoop(RCopy, realGyroCopy, BetterR, 0.02, 1);
            
            for(e = 0; e < 3; e++){
                for(f = 0; f < 3; f++){
                    RCopy[e][f] = BetterR[e][f];
                //printf("%f\n", RCopy[e][f]);
                }
             * //float bias[3][1] = {{(70.17402597/131)}, {(244.8294372/131)}, {(-87.27099567/131)}};
    //float bias[3][1] = {{0}, {(0)}, {(0)}};
    //float bias[3][1] = {{(-70.17402597)}, {(-244.8294372)}, {(87.27099567)}};
    //float bias2[3][1] = {{0.05}, {0.04}, {0.03}};//float bias[3][1] = {{(70.17402597/131)}, {(244.8294372/131)}, {(-87.27099567/131)}};
    //float bias[3][1] = {{0}, {(0)}, {(0)}};
    //float bias[3][1] = {{(-70.17402597)}, {(-244.8294372)}, {(87.27099567)}};
    //float bias2[3][1] = {{0.05}, {0.04}, {0.03}};
            }*/
            
/*float rotX[3][3] = {{1,0,0},{0,cos(Angle[0]),-sin(Angle[0])}
            ,{0,sin(Angle[0]),cos(Angle[0])}}; 
            float rotY[3][3] = {{cos(Angle[1]),0,sin(Angle[1])},{0,1,0},
            {-sin(Angle[1]),0,cos(Angle[1])}};
            float rotZ[3][3] = {{cos(Angle[2]),-sin(Angle[2]),0},
            {sin(Angle[2]),cos(Angle[2]),0},{0,0,1}};
  
            MatrixMultiply(rotX, rotY, rotXY, 3, 3, 3, 3);
            MatrixMultiply(rotXY, rotZ, Ro, 3, 3, 3, 3);*/
            
/*printf("Error = \r\n");
            for(k = 0; k < 3; k++){
                printf("%f ", realGyro[k][0]);
            }
            printf("\r\n");*/

 /*for(c = 0; c < 3; c++){
                for(d = 0; d < 3; d++){
                    //RCopy[c][d] = Ro[c][d];
                  RCopy[c][d] = DCM2[c][d];
                }
            }*/
