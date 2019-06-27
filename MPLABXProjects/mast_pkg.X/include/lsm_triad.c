//#include "vars.h" // all the random variables needed
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

#define ACCEL_X_NULL 0	// no accel null shifts?
#define ACCEL_Y_NULL 0
#define ACCEL_Z_NULL 0
#define ACCEL_SENS_SCALE 0.732    //+/- 16g

#define MAG_X_NULL 0
#define MAG_Y_NULL 0
#define MAG_Z_NULL 0

int main(void) {
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

    int delay = 500;
    
    float roll, pitch, yaw, c2;
    //float gyroX, gyroY, gyroZ;
    float accelX, accelY, accelZ;
    float magX, magY, magZ;

    //    float biasX = 275.124451, biasY = 154.4904832, biasZ = -107.0673499;

    char str[100] = "startup";

    float eye[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    float eyeTest[3][3] = {};

    //float gyroInput[3][1] = {};

    float R[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    /////////////////////////////////////////

    float accelNullVec[3][1] = {
        {ACCEL_X_NULL},
        {ACCEL_Y_NULL},
        {ACCEL_Z_NULL}
    };
    float accelScale[3][3] = {
        {6.01332025760332e-05, 1.18090246189778e-07, 4.83022034325204e-08},
        {2.78584588255767e-07, 5.97364000754783e-05, -2.44328961780386e-07},
        {1.67237354044399e-08, -7.00685693778437e-08, 5.99705971242468e-05}
    };
    float accelVec[3][1] = {};
    float accelVecScaled[3][1] = {};
    float accelVecShifted[3][1] = {};

    float magNullVec[3][1] = {
        {MAG_X_NULL},
        {MAG_Y_NULL},
        {MAG_Z_NULL}
    };
    float magScale[3][3] = {
        {0.00375640345842856, 4.18160455046611e-06, -1.71566686746650e-05},
        {2.95805849882053e-06, 0.00383432383831521, 5.10586509796511e-05},
        {1.05150482498810e-05, 6.02570354685426e-05, 0.00355079993936427}
    };

    float magVec[3][1] = {};
    float magVecScaled[3][1] = {};
    float magVecShifted[3][1] = {};

    ////////////////////////////////////////////
    //NED
    float accelInertialReading[3][1] = {
        {0.0},
        {0.0},
        {1.0} // -1? accel actually reads pos
    };
    //NOAA NED comps
    float magInertialReading[3][1] = {
        {22819.3},
        {5363.1},
        {41558.8}
    };

    float normAccel, normMag, normMagInertial, normAccelInertial, mNorm, MNorm;

    //    float Rmis[3][3] = {
    //        {0.0559, 0.9846, 0.1655},
    //        {0.9715, -0.0919, 0.2187},
    //        {0.2305, 0.1485, -0.9617}
    //    };

    float Rmis[3][3] = {
        {0.0532, 0.9969, -0.0585},
        {0.9894, -0.0447, 0.1383},
        {0.1353, -0.0652, -0.9887}
    };
    float RmisT[3][3] = {};

    float magReading[3][1] = {};
    float accelReading[3][1] = {};
    float magReadingAligned[3][1] = {};
    float magInertialReadingAligned[3][1] = {};

    float mag[3][1] = {};
    float accel[3][1] = {};
    float magInertial[3][1] = {};
    float accelInertial[3][1] = {};
    float accelSkew[3][3] = {};
    float magSkew[3][3] = {};
    float magInertialSkew[3][3] = {};
    float magInterialSkewXM[3][1] = {};
    float magInertialSkewXM[3][1] = {};
    float magSkewXM[3][1] = {};
    float magSkewXm[3][1] = {};
    float M[3][1] = {};
    float m[3][1] = {};
    float MUnit[3][1] = {};
    float mUnit[3][1] = {};
    float A[3][3] = {};
    float B[3][3] = {};
    float BTrans[3][3] = {};
    float C[3][3] = {};




    while (1) {

        if (TIMERS_GetMilliSeconds() >= delay) {

            accelX = (float) LSM9DS1_ReadAccelX();
            accelY = (float) LSM9DS1_ReadAccelY();
            accelZ = (float) LSM9DS1_ReadAccelZ();
            accelX = (accelX - ACCEL_X_NULL) * ACCEL_SENS_SCALE / 1000;
            accelY = (accelY - ACCEL_Y_NULL) * ACCEL_SENS_SCALE / 1000;
            accelZ = (accelZ - ACCEL_Z_NULL) * ACCEL_SENS_SCALE / 1000;
            accelVec[0][0] = accelX;
            accelVec[1][0] = accelY;
            accelVec[2][0] = accelZ;
            MatrixMultiplyVector(accelScale, accelVec, accelVecScaled);
            VectorAdd(accelVecScaled, accelNullVec, accelVecShifted);
            accelReading[0][0] = accelVecShifted[0][0];
            accelReading[1][0] = accelVecShifted[1][0];
            accelReading[2][0] = accelVecShifted[0][0];
//            accelReading[0][0] = accelVec[0][0];
//            accelReading[1][0] = accelVec[1][0];
//            accelReading[2][0] = accelVec[2][0];

            magX = (float) LSM9DS1_ReadMagX();
            magY = (float) LSM9DS1_ReadMagY();
            magZ = (float) LSM9DS1_ReadMagZ();
            magVec[0][0] = magX;
            magVec[1][0] = magY;
            magVec[2][0] = magZ;
            MatrixMultiplyVector(magScale, magVec, magVecScaled);
            VectorAdd(magVecScaled, magNullVec, magVecShifted);
            magReading[0][0] = magVecShifted[0][0];
            magReading[1][0] = magVecShifted[1][0];
            magReading[2][0] = magVecShifted[2][0];
//            magReading[0][0] = magVec[0][0];
//            magReading[1][0] = magVec[1][0];
//            magReading[2][0] = magVec[2][0];

            // Align magnetometer to accelerometer coordinate frame
            MatrixTranspose(Rmis, RmisT);
            //MatrixMultiplyVector(RmisT, magReading, magReadingAligned);
            MatrixMultiplyVector(RmisT, magVecShifted, magReadingAligned);
            MatrixMultiplyVector(RmisT, magInertialReading, magInertialReadingAligned);

            normAccel = VectorNorm(accelVecShifted);
            VectorScalarMultiply(1 / normAccel, accelVecShifted, accel); //set accel to unit vector

            normMag = VectorNorm(magReadingAligned);
            VectorScalarMultiply(1 / normMag, magReadingAligned, mag); //set mag to unit vector

            normAccelInertial = VectorNorm(accelInertialReading);
            VectorScalarMultiply(1 / normAccelInertial, accelInertialReading, accelInertial);

            normMagInertial = VectorNorm(magInertialReadingAligned);
            //VectorScalarMultiply(1.0 / normMagInertial, magInertialReading, magInertial); //set mag inertial reference vectors to unit vectors
            VectorScalarMultiply(1 / normMagInertial, magInertialReadingAligned, magInertial); //does inertial reading need to be aligned too?

            rcross(mag, magSkew);
            MatrixMultiplyVector(magSkew, accel, m);
            mNorm = VectorNorm(m);
            VectorScalarMultiply(1 / mNorm, m, mUnit);

            rcross(magInertial, magInertialSkew);
            MatrixMultiplyVector(magInertialSkew, accelInertial, M);
            MNorm = VectorNorm(M);
            VectorScalarMultiply(1 / MNorm, M, MUnit);


            MatrixMultiplyVector(magInertialSkew, MUnit, magInertialSkewXM);
            MatrixMultiplyVector(magSkew, mUnit, magSkewXm);

            A[0][0] = magInertial[0][0];
            A[1][0] = magInertial[1][0];
            A[2][0] = magInertial[2][0];
            A[0][1] = MUnit[0][0];
            A[1][1] = MUnit[1][0];
            A[2][1] = MUnit[2][0];
            A[0][2] = magInertialSkewXM [0][0];
            A[1][2] = magInertialSkewXM [1][0];
            A[2][2] = magInertialSkewXM [2][0];

            B[0][0] = mag[0][0];
            B[1][0] = mag[1][0];
            B[2][0] = mag[2][0];
            B[0][1] = mUnit[0][0];
            B[1][1] = mUnit[1][0];
            B[2][1] = mUnit[2][0];
            B[0][2] = magSkewXm [0][0];
            B[1][2] = magSkewXm [1][0];
            B[2][2] = magSkewXm [2][0];

            MatrixTranspose(B, BTrans);
            MatrixMultiply(A, BTrans, C);
            MatrixTranspose(C, R);

            /* Euler Angles from DCM */
            pitch = asin(-R[0][2]);
            //            roll = asin(R[1][2] / cos(pitch));
            //            yaw = asin(R[0][1] / cos(pitch));
            //c2 = sqrt(R[0][0] * R[0][0] + R[0][1] * R[0][1]);
            c2 = sqrt(R[1][2] * R[1][2] + R[2][2] * R[2][2]);

            roll = atan2f(R[1][2], R[2][2]);
            //pitch = atan2(-R[0][2], c2);
            yaw = atan2f(R[0][1], R[0][0]);
            
            if(yaw > 0 ){
                yaw = yaw*1.18;
            }
            
            

            sprintf(str, "r%.2f\tp%.2f\ty%.2f\r\n", roll * 180 / 3.14, pitch * 180 / 3.14, yaw * 180 / 3.14);
            for(i = 0; i < strlen(str); ++i)
                PutChar(2, str[i]);

            delay += 70;
        }
    }

    return 0;

}
