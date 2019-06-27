/* 
 * File:   MatrixFunctions.h
 * Author: RARogers
 *
 * Created on March 3, 2019, 10:00 AM
 */

#ifndef MATRIXFUNCTIONS_H
#define	MATRIXFUNCTIONS_H

#ifdef	__cplusplus
extern "C" {
#endif

/*********************************************************************/
/***************************FUNCTIONS*********************************/
/*********************************************************************/

void MatrixMultiply(float mat1[3][3], float mat2[3][3], float result[3][3], int m1r, int m1c, int m2r, int m2c);

void MatVecMultiply(float mat[3][3], float vec[3][1], float result[3][1], int mr1, int mc1, int vr);

void MatNorm(float mat[3][3], float result[3][1], int mr, int mc);

void VecNorm(float vec[3][1], float result[1], int mr);

void MatSquared(float mat[3][3], float result[3][3], int mr, int mc);

void VecSquared(float vec[3][1], float result[3][1], int mr);

void MatToNegFirstPower(float mat[3][3], float result[3][3], int mr, int mc);

//void VecToNegFirstPower(float vec[1][3], float result[1][3], int mr, int mc);

void MatrixAdd(float mat1[3][3], float mat2[3][3], float result[3][3], int m1r, int m1c, int m2r, int m2c);

void ColVecAdd(float vec1[3][1], float vec2[3][1], float result[3][1]);

int MatrixEquals(float mat1[3][3], float mat2[3][3]);

void VectorScalarMultiply(float x, float vec[3][1], float result[3][1], int md);

void MatrixScalarMultiply(float x[1], float mat[3][3], float result[3][3], int mr, int mc);

void MatrixScalarAdd(float x[1], float mat[3][3], float result[3][3]);

float MatrixDeterminant(float mat[3][3]);

float MatrixTrace(float mat[3][3]);

void MatrixTranspose(float mat[3][3], float result[3][3]);

void VectorTranspose(float vec[3][1], float result[1][3]);

void MatrixInverse(float mat[3][3], float result[3][3]);

void MatrixPrint(float mat[3][3]);

#ifdef	__cplusplus
}
#endif

#endif	/* MATRIXFUNCTIONS_H */

