#include "xc.h"
#include <BOARD.h>
#include <I2C.h>
#include <AD.h>
#include <timers.h>
#include <stdio.h>
#include <MPU9250.h>
#include <stdlib.h>
#include <MatrixMath.h>
#include <math.h>
#include "MPU9250.h"

#define ACCEL_X_NULL -0.0265
#define ACCEL_Y_NULL -0.0138
#define ACCEL_Z_NULL -0.0374
#define MAG_X_NULL -0.8223
#define MAG_Y_NULL -0.9022
#define MAG_Z_NULL 1.3509

#define MOVING 20

extern float radToDeg;
extern float rollAvg, pitchAvg, compassAvg, rollSum, pitchSum, compassSum, magHeading, rawCompassHeading, alignedCompassHeading;
extern float magXCorr, magYCorr, magZCorr;

extern float accel[3][1];
extern float roll[MOVING];
extern float pitch[MOVING];
extern float compass[MOVING];


extern float accelNullVec[3][1];

extern float accelScale[3][3];

extern float accelReading[3][1];
extern float accelVec[3][1];
extern float accelVecScaled[3][1];
extern float accelVecShifted[3][1];

extern float magNullVec[3][1];

extern float magScale[3][3];

extern float magReading[3][1];
extern float magReadingAligned[3][1];
extern float magVec[3][1];
extern float magVecScaled[3][1];
extern float magVecShifted[3][1];

extern float Rmis[3][3];
extern float RmisT[3][3];