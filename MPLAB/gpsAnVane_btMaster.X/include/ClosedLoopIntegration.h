/* 
 * File:   ClosedLoopIntegration.h
 * Author: raaroger
 *
 * Created on March 11, 2019, 4:29 PM
 */

#ifndef CLOSEDLOOPINTEGRATION_H
#define	CLOSEDLOOPINTEGRATION_H

#ifdef	__cplusplus
extern "C" {
#endif

void IntegrateClosedLoop(float Rminus[3][3], float Bminus[3][1], float gyroInput[3][1], 
    float magData[3][1], float accelData[3][1], float magIn[3][1], float accelIn[3][1], 
    float timeChange, float kp_a, float kp_m, float ki_a, float ki_m, float Rplus[3][3],
    float Bplus[3][1]);   

void ClosedLoop(float bias[3][1], float gyroInput[3][1], float magData[3][1], 
float accelData[3][1], float magIn[3][1], float accelIn[3][1], int steps, float kp_a, 
float kp_m, float ki_a, float ki_m, float BetterR[3][3], float biasEst[3][1]);

#ifdef	__cplusplus
}
#endif

#endif	/* CLOSEDLOOPINTEGRATION_H */

