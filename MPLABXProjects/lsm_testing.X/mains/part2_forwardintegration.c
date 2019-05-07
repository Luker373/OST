/*
 * File:   part2.c
 * Author: Joe
 *
 * Created on March 3, 2019, 7:54 PM
 */


#include "xc.h"
#include <BOARD.h>
#include <I2C.h>
#include <AD.h>
#include <timers.h>
#include <stdio.h>
#include <stdlib.h>
#include <Oled.h>
#include <OledDriver.h>
#include <MatrixMath.h>
#include <math.h>

#define NUM_STEPS 20
#define p 3.14
#define q 0
#define r 0

int main(void) {
    BOARD_Init();
    TIMERS_Init();

    int delay = 1000;
    float deltaT = 0.01;
    float roll, pitch, yaw;
    int i, j, k, loopStep;
    float bias[3] = {0, 0, 0.03};

    float gyroInput[3][1] = {
        {p},
        {q},
        {r}
    };
    float gyroInputWithBias[3][1] = {
        {p + bias[0]},
        {q + bias[1]},
        {r + bias[2]}
    };
    float nvector[3][1] = {
        {1},
        {0},
        {0}
    };
    float evector[3][1] = {
        {0},
        {-1},
        {0}
    };
    float dvector[3][1] = {
        {0},
        {0},
        {-1}
    };
    float newNVector[3][1] = {
        {0},
        {0},
        {0}
    };
    float newEVector[3][1] = {
        {0},
        {0},
        {0}
    };
    float newDVector[3][1] = {
        {0},
        {0},
        {0}
    };
    float Ro[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    float R[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    float Rplus[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    float Rtrans[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    float skewSymGyro[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    float RSkew[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    float RSkewDelta[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    float RplusTrans[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    float eyeTest[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };

    printf("deltaT = %0.2f, bias = [%0.2f, %0.2f, %0.2f] p = %d, q = %d, r = %d\r\n", deltaT, bias[0], bias[1], bias[2], p, q, r);
    for (loopStep = 0; i < NUM_STEPS; loopStep++) {
        printf("time = %f \n", loopStep*deltaT);

        //open loop integrate (forward integration)
        //rcross(gyroInput, skewSymGyro);
        rcross(gyroInputWithBias, skewSymGyro);
        MatrixMultiply(R, skewSymGyro, RSkew);
        MatrixScalarMultiply(deltaT, RSkew, RSkewDelta);
        MatrixAdd(R, RSkewDelta, Rplus);

        MatrixTranspose(Rplus, RplusTrans);
        MatrixMultiply(Rplus, RplusTrans, eyeTest);

        pitch = asin(-Rplus[0][2]);
        roll = asin(Rplus[1][2] / cos(pitch));
        yaw = asin(Rplus[0][1] / cos(pitch));

        //        printf("roll = %0.2f, pitch = %0.2f, yaw = %0.2f\r\n", roll, pitch, yaw);
        printf("roll = %0.2f, pitch = %0.2f, yaw = %0.2f\n", roll * 180 / 3.14, pitch * 180 / 3.14, yaw * 180 / 3.14);
        printf("DCM\n");
        MatrixPrint2(Rplus);
        printf("R*R'=I\n");
        MatrixPrint2(eyeTest);
        /*
        MatrixTranspose(Rplus, Rtrans);
        MatrixMultiplyVector(Rtrans, nvector, newNVector);
        MatrixMultiplyVector(Rtrans, evector, newEVector);
        MatrixMultiplyVector(Rtrans, dvector, newDVector);
         */

        // copy R to be Rplus for next iteration
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                R[i][j] = Rplus[i][j];
            }
        }
        while (TIMERS_GetMilliSeconds() < delay) {
            ;
        }
        delay += 100;
    }
    while (1) {
        ;
    }
    return 0;

}


//Rplus = Rminus + Rminus * rcross(gyros)*deltaT;
/*
R=IntegrateOpenLoop(R,gyroInputWithBias,.5)
	
function [Rplus] = IntegrateOpenLoop(Rminus, gyros, deltaT)
% function [Rplus] = IntegrateOpenLoop(Rminus, gyros, deltaT)
%
% Function to Integrate the gyros to the attitude DCM
%
% Inputs: Previous attitute DCM (Rminus)
%         Body Fixed Rotation rates ([p;q;r]) in rad/s
%         Time between samples (deltaT) in seconds
%
% Outputs: New DCM (Rplus)

    Rplus = Rminus + Rminus * rcross(gyros)*deltaT;
 */