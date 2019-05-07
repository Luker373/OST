/* 
 * File:   OpenLoopIntegration.h
 * Author: RARogers
 *
 * Created on March 8, 2019, 3:54 PM
 */

#ifndef OPENLOOPINTEGRATION_H
#define	OPENLOOPINTEGRATION_H

#ifdef	__cplusplus
extern "C" {
#endif

    void IntegrateOpenLoop(float Rminus[3][3], float gyroInput[3][1], float Rplus[3][3], 
    float timeChange, int useExpo);
    
    void OpenLoop(float bias[3][1], float gyroInput[3][1], int steps, float BetterR[3][3], 
    int useExpo);


#ifdef	__cplusplus
}
#endif

#endif	/* OPENLOOPINTEGRATION_H */

