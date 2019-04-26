/* 
 * File:   ClosedLoopIntegration.c
 * Author: raaroger
 *
 * Created on March 11, 2019, 4:30 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "xc.h"
#include "math.h"
#include "MatrixFunctions.h"
#include "DCM.h"

/*
 * 
 */

/*void IntegrateClosedLoop(float Rminus[3][3], float Bminus[3][1], float gyroInput[3][1], 
    float magData[3][1], float accelData[3][1], float magIn[3][1], float accelIn[3][1], 
    float timeChange, float kp_a, float kp_m, float ki_a, float ki_m, float Rplus[3][3], 
    float Bplus[3][1]){
    
    float anorm[1], mnorm[1], ainorm[1], minorm[1];
    float aunorm, munorm, aiunorm, miunorm;
    float auv[3][1], muv[3][1], aiuv[3][1], miuv[3][1], 
    negBminus[3][1], gyroPlusBias[3][1], RMPAI[3][1], 
    RMPMI[3][1], wmeasa[3][1], wmeasm[3][1], kpav[3][1],
    kpmv[3][1], gyroFeedback[3][1], bdot[3][1], kimv[3][1],
    kiav[3][1]; 
    float RMPrime[3][3], skewa[3][3], skewm[3][3],
    Rexpo[3][3]; 
    int Count = 0, iter = 0, addem = 0, addemagain = 0;
    
    // calculate norms for accel and mag data, put into 1/x form for scalar multiply
    VecNorm(accelData, anorm, 3);
    aunorm = 1/anorm[0];
    VecNorm(magData, mnorm, 3);
    munorm = 1/mnorm[0];
    VecNorm(accelIn, ainorm, 3);
    aiunorm = 1/ainorm[0];
    VecNorm(magIn, minorm, 3);
    miunorm = 1/minorm[0];
    
    // make vectors unit vectors
    VectorScalarMultiply(aunorm, accelData, auv, 3);
    VectorScalarMultiply(munorm, magData, muv, 3);
    VectorScalarMultiply(aiunorm, accelIn, aiuv, 3);
    VectorScalarMultiply(miunorm, magData, miuv, 3);
    
    // make Bminus negative
    //VectorScalarMultiply(-1.0, Bminus, negBminus, 3);
    
    // get gyro input with bias
    for(Count = 0; Count < 3; Count++){
        //gyroPlusBias[Count][0] = gyroInput[Count][0] + negBminus[Count][0];
        gyroPlusBias[Count][0] = gyroInput[Count][0] - Bminus[Count][0];
    }
    
    // get accel correction in body frame
    MatrixTranspose(Rminus, RMPrime);
    rcross(auv, skewa);
    MatVecMultiply(RMPrime, aiuv, RMPAI, 3, 3, 3);
    MatVecMultiply(skewa, RMPAI, wmeasa, 3, 3, 3);
    
    // get mag correction in body frame
    rcross(muv, skewm);
    MatVecMultiply(RMPrime, miuv, RMPMI, 3, 3, 3);
    MatVecMultiply(skewm, RMPMI, wmeasm, 3, 3, 3);
    
    // get gyro input with feedback
    VectorScalarMultiply(kp_a, wmeasa, kpav, 3);
    VectorScalarMultiply(kp_m, wmeasm, kpmv, 3);
    for(iter = 0; iter < 3; iter++){
        gyroFeedback[iter][0] = gyroPlusBias[iter][0] + kpav[iter][0] + kpmv[iter][0];
        //gyroOut[iter][0] = gyroFeedback[iter][0];
    }
    
    // calculate bdot
    VectorScalarMultiply(ki_a, wmeasa, kiav, 3);
    VectorScalarMultiply(ki_m, wmeasm, kimv, 3);
    for(addem = 0; addem < 3; addem++){
        bdot[addem][0] = -1*(kiav[addem][0]) - (kimv[addem][0]);
        //gyroOut[iter][0] = gyroFeedback[iter][0];
    }
    
    // caluclate Rplus and bplus
    rexp(gyroFeedback, Rexpo);
    MatrixMultiply(Rminus, Rexpo, Rplus, 3, 3, 3, 3);
    for(addemagain = 0; addemagain < 3; addemagain++){
        Bplus[addemagain][0] = (Bminus[addemagain][0]) + (bdot[addemagain][0]);
        //gyroOut[iter][0] = gyroFeedback[iter][0];
    }
}*/

void IntegrateClosedLoop(float Rminus[3][3], float Bminus[3][1], float gyroInput[3][1], 
float magData[3][1], float accelData[3][1], float magIn[3][1], float accelIn[3][1], 
float timeChange, float kp_a, float kp_m, float ki_a, float ki_m, float Rplus[3][3], 
float Bplus[3][1]){
    
    float anorm[1], mnorm[1], ainorm[1], minorm[1];
    float aunorm, munorm, aiunorm, miunorm;
    
    float auv[3][1], muv[3][1], aiuv[3][1], miuv[3][1], 
    gyroPlusBias[3][1], RMPAI[3][1], RMPMI[3][1], wmeasa[3][1], 
    wmeasm[3][1], wmeasia[3][1], wmeasim[3][1], kpav[3][1], 
    kpmv[3][1], gyroFeedback[3][1], bdot[3][1], kimv[3][1], kiav[3][1], 
    adsq[3][1], mdsq[3][1], aisq[3][1], misq[3][1]; 
    
    float RMPrime[3][3], skewa[3][3], skewm[3][3]; 
    float Rexpo[3][3];
    
    int Count = 0, iter = 0, addem = 0, addemagain = 0, m = 0;
    int i, j;
    
    // calculate norms for accel and mag data, put into 1/x form for scalar multiply
    VecSquared(accelData, adsq, 3);
    VecNorm(adsq, anorm, 3);
    aunorm = 1.0/anorm[0];
    
    VecSquared(magData, mdsq, 3);
    VecNorm(mdsq, mnorm, 3);
    munorm = 1.0/mnorm[0];
    
    VecSquared(accelIn, aisq, 3);
    VecNorm(aisq, ainorm, 3);
    aiunorm = 1.0/ainorm[0];
    
    VecSquared(magIn, misq, 3);
    VecNorm(misq, minorm, 3);
    miunorm = 1.0/minorm[0];
    
    // make vectors unit vectors
    VectorScalarMultiply(aunorm, accelData, auv, 3);
    VectorScalarMultiply(munorm, magData, muv, 3);
    VectorScalarMultiply(aiunorm, accelIn, aiuv, 3);
    VectorScalarMultiply(miunorm, magIn, miuv, 3); 
    /*for (m = 0; m < 3; m++){ 
        printf("%f ", miuv[m][0]); 
    }
    printf("\r\n");*/
    
    // get gyro input with bias
    for(Count = 0; Count < 3; Count++){
        //gyroPlusBias[Count][0] = gyroInput[Count][0] + negBminus[Count][0];
        gyroPlusBias[Count][0] = gyroInput[Count][0] - Bminus[Count][0]; // good up to here
        //printf("%f\r\n", gyroPlusBias[Count][0]);
    }
    
    // get accel correction in body frame
    MatrixTranspose(Rminus, RMPrime); // transpose is messed up?
    rcross(auv, skewa);
    MatVecMultiply(RMPrime, aiuv, RMPAI, 3, 3, 3);
    MatVecMultiply(skewa, RMPAI, wmeasa, 3, 3, 3);
    /*for (m = 0; m < 3; m++){ 
        printf("%f ", wmeasa[m][0]); 
    }*/
    
    // get mag correction in body frame
    rcross(muv, skewm);
    MatVecMultiply(RMPrime, miuv, RMPMI, 3, 3, 3);
    MatVecMultiply(skewm, RMPMI, wmeasm, 3, 3, 3);
    /*for (m = 0; m < 3; m++){ 
        printf("%f ", wmeasm[m][0]); 
    }*/
    
    // get gyro input with feedback
    VectorScalarMultiply(kp_a, wmeasa, kpav, 3);
    VectorScalarMultiply(kp_m, wmeasm, kpmv, 3);
    for(iter = 0; iter < 3; iter++){
        gyroFeedback[iter][0] = gyroPlusBias[iter][0] + kpav[iter][0] + kpmv[iter][0];
        //printf("%f\r\n", gyroFeedback[iter][0]);
        //gyroOut[iter][0] = gyroFeedback[iter][0];
    } // good
    
    // calculate bdot
    VectorScalarMultiply(ki_a, wmeasa, kiav, 3);
    VectorScalarMultiply(ki_m, wmeasm, kimv, 3);
    for(addem = 0; addem < 3; addem++){
        bdot[addem][0] = (-(kiav[addem][0])) - (kimv[addem][0]);
        //printf("%f\r\n", bdot[addem][0]);
        //gyroOut[iter][0] = gyroFeedback[iter][0];
    } // good
    
    // caluclate Rplus and bplus
    rexp(gyroFeedback, Rexpo);
    /*printf("Result matrix is \n"); 
    for (i = 0; i < 3; i++){ 
        for (j = 0; j < 3; j++){ 
           printf("%f ", Rexpo[i][j]); 
        }
        printf("\r\n"); 
    }*/
    //printf("\r\n");
    MatrixMultiply(Rminus, Rexpo, Rplus, 3, 3, 3, 3);
    /*printf("Result matrix is \n"); 
    for (i = 0; i < 3; i++){ 
        for (j = 0; j < 3; j++){ 
           printf("%f ", Rplus[i][j]); 
        }
        printf("\r\n"); 
    }*/
    
    for(addemagain = 0; addemagain < 3; addemagain++){
        Bplus[addemagain][0] = (Bminus[addemagain][0]) + (bdot[addemagain][0]);
        //gyroOut[iter][0] = gyroFeedback[iter][0];
        //printf("%f\r\n", Bplus[addemagain][0]);
    }
    
}

void ClosedLoop(float bias[3][1], float gyroInput[3][1], float magData[3][1], 
float accelData[3][1], float magIn[3][1], float accelIn[3][1], int steps, float kp_a, 
float kp_m, float ki_a, float ki_m, float BetterR[3][3], float biasEst[3][1]){
    
    float rotXY[3][3], newR[3][3], Rexp[3][3], RCopy[3][3], BRT[3][3];
    //BetterR[3][3];
    float INV[3][1], IEV[3][1], IDV[3][1], realGyro[3][1], realGyroCopy[3][1];
    //float bias[3][1] = {{0.05}, {0.04}, {0.03}};
    int i = 0, a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, k = 0, l = 0;
  
    float Ro[3][3] = {{1,0,0},{0,1,0},{0,0,1}}; 
    
    for(a = 0; a < 3; a++){
        realGyroCopy[a][0] = gyroInput[a][0];
    }
    
    for(c = 0; c < 3; c++){
        for(d = 0; d < 3; d++){
            RCopy[c][d] = Ro[c][d];
            //printf("%f\n", RCopy[c][d]);
        }
    }
    
    ColVecAdd(realGyroCopy, bias, realGyro); // gives us correct values
    
    for(b = 0; b < 3; b++){
        realGyroCopy[b][0] = realGyro[b][0];
            //printf("%f\n", realGyroCopy[b][0]);
            //printf("\n");
    }
    
    for(i = 0; i < steps; i++){
        
        //IntegrateClosedLoop(RCopy, biasEst, realGyroCopy, BetterR, 1, useExpo);
        IntegrateClosedLoop(RCopy, biasEst, realGyroCopy, magData, accelData, 
        magIn, accelIn, 0.02, kp_a, kp_m, ki_a, ki_m, BetterR, biasEst);
        
        MatrixTranspose(BetterR, BRT);
        /*MatVecMultiply(BRT, NV, NNV, 3, 3, 3);
        MatVecMultiply(BRT, EV, NEV, 3, 3, 3);
        MatVecMultiply(BRT, DV, NDV, 3, 3, 3);*/
        
        
        for(e = 0; e < 3; e++){
            for(f = 0; f < 3; f++){
                RCopy[e][f] = BetterR[e][f];
                //printf("%f\n", RCopy[e][f]);
            }
        }
        
    }
    
}
