/* 
 * File:   OpenLoopIntegration.c
 * Author: RARogers
 *
 * Created on March 8, 2019, 3:54 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "xc.h"
#include "MatrixFunctions.h"
#include "DCM.h"

/*
 * 
 */

void IntegrateOpenLoop(float Rminus[3][3], float gyroInput[3][1], float Rplus[3][3], 
float timeChange, int useExpo){
    
    float rxRes[3][3], rcRes[3][3], msmRes[3][3], mmRes[3][3];
    float gyroTC[3][1], vsmRes[3][1];
    float ioltC[1];
    //printf("NANNI\n");
    ioltC[0] = timeChange;
    int i, j;
    
    if(useExpo == 1){    
        VectorScalarMultiply(timeChange, gyroInput, vsmRes, 3);
        rexp(vsmRes, rxRes);
        MatrixMultiply(Rminus, rxRes, Rplus, 3, 3, 3, 3);
        printf("Rplus is \r\n"); 
        for (i = 0; i < 3; i++){ 
            for (j = 0; j < 3; j++){ 
                printf("%f ", Rplus[i][j]); 
            }
            printf("\r\n"); 
        }
    } else {
        rcross(gyroInput, rcRes);
        MatrixScalarMultiply(ioltC, rcRes, msmRes, 3, 3);
        MatrixMultiply(Rminus, msmRes, mmRes, 3, 3, 3, 3);
        MatrixAdd(Rminus, mmRes, Rplus, 3, 3, 3, 3);
        printf("Result matrix is \r\n"); 
        for (i = 0; i < 3; i++){ 
            for (j = 0; j < 3; j++){ 
                printf("%f ", Rplus[i][j]); 
            }
            printf("\r\n"); 
        }
    }
    
}

void OpenLoop(float bias[3][1], float gyroInput[3][1], int steps, 
float BetterR[3][3], int useExpo){
    
    float tC[1];
    tC[0] = 1;
    float realGyro[3][1], realGyroCopy[3][1];
    //float bias[3][1] = {{0.05}, {0.04}, {0.03}};
    float newR[3][3], Rexp[3][3];
    float RCopy[3][3];
    float BRT[3][3];
    float R[3][3] = {{1,0,0},{0,1,0},{0,0,1}};
    
    int i = 0, a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, k = 0, l = 0;

    rexp(gyroInput, Rexp);
    
    for(a = 0; a < 3; a++){
        realGyroCopy[a][0] = gyroInput[a][0];
    }
    
    for(c = 0; c < 3; c++){
        for(d = 0; d < 3; d++){
            RCopy[c][d] = R[c][d];
            //printf("%f\n", RCopy[c][d]);
        }
    }
    
    ColVecAdd(realGyroCopy, bias, realGyro); // gives us correct values
    for(b = 0; b < 3; b++){
        realGyroCopy[b][0] = realGyro[b][0];
            //printf("%f\n", realGyroCopy[b][0]);
            //printf("\n");
    }
    
    //for(i = 0; i < steps; i++){
        
        IntegrateOpenLoop(RCopy, realGyroCopy, BetterR, 0.2, useExpo);
        
        MatrixTranspose(BetterR, BRT);
        
        for(e = 0; e < 3; e++){
            for(f = 0; f < 3; f++){
                RCopy[e][f] = BetterR[e][f];
                //printf("%f\n", RCopy[e][f]);
            }
        }
        //printf("\n");
    //}
}