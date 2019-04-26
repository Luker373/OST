/* 
 * File:   DCM.h
 * Author: raaroger
 *
 * Created on March 4, 2019, 5:25 PM
 */

#ifndef DCM_H
#define	DCM_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include "stdio.h"
#include "stdlib.h"
#include "MatrixFunctions.h"

void rcross(float vec[3][1], float skewm[3][3]);

void colnorm(float mat[3][3], int mr, int mc);

void rexp(float vec[3][1], float rexp[3][3]);

void ExtractEulerFromDCM(float mat[3][3], double angles[3]); // take in DCM and get euler angles out

/*void ExtractEulerFromRotM(float mat[3][3]); // take in any rotation matrix
                                            // and get euler angles out (but how?)*/
// we can assume dcm will always be given in the form in 1st part 2

//void DCMfromTriad(int ax, int ay, int az, int mx, int my, int mz, float mat[3][3]);
void DCMFromTriad(float magData[3][1], float accelData[3][1], float magIn[3][1], 
float accelIn[3][1], float R[3][3]);

void CheckOrtho(float R[3][3], float check[3][3], float error[3][1]);

#ifdef	__cplusplus
}
#endif

#endif	/* DCM_H */

