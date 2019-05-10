//mml.c
//Joseph Skinner
//jlskinne
//Unit test for MatrixMath.c

// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

//CMPE13 Support Library
#include "BOARD.h"


// Microchip libraries
#include <xc.h>
#include <plib.h>

// User libraries
#include "MatrixMath.h"

// **** Set macros and preprocessor directives ****

// **** Define global, module-level, or external variables here ****
int i, j, testpass = 0;
float result[3][3];
float value = 0.0, percent  = 0, totalPass = 0;
float A[3][3];
float B[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};
float C[3][3] = {
    {2, 4, 6},
    {8, 10, 12},
    {14, 16, 18}
};
float D[3][3] = {
    {30, 36, 42},
    {66, 81, 96},
    {102, 126, 150}
};
float E[3][3] = {
    {1.0001, 2.0001, 3.0001},
    {4.0001, 5.0001, 6.0001},
    {7.0001, 8.0001, 9.0001}
};
float F[3][3] = {
    {1.0002, 2.0002, 3.0002},
    {4.0002, 5.0002, 6.0002},
    {7.0002, 8.0002, 9.0002}
};
float G[3][3] = {
    {2.0002, 4.0002, 6.0002},
    {8.0002, 10.0002, 12.0002},
    {14.0002, 16.0002, 18.0002}
};
float H[3][3] = {
    {-8.0002, 4.0002, 6.0002},
    {8.0002, -10.0002, 12.0002},
    {14.0002, 16.0002, 18.0002}
};
float I[3][3] = {
    {1, 4, 7},
    {2, 5, 8},
    {3, 6, 9}
};
float J[3][3] = {
    {-8.0002, 8.0002, 14.0002},
    {4.0002, -10.0002, 16.0002},
    {6.0002, 12.0002, 18.0002}
};
float K[3][3] = {
    {-3, 6, -3},
    {6, -12, 6},
    {-3, 6, -3}
};
float L[3][3] = {
    {1, 2, 0},
    {2, 5, -1},
    {4, 10, 0}
};
float M[3][3] = {
    {5.0000, 0, -1.0000},
    {-2.0000, 0, 0.5000},
    {0, -1.0000, 0.5000}
};
float N[3][3] = {
    {30, 36, 42},
    {8, -10, 12},
    {14, 16, 18}
};
float O[3][3] = {
    {-372, 24, 268},
    {24, -48, 24},
    {852, -24, -588}

};
float P[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 10.0002}

};
float Q[3][3] = {
    {2.0010, 1.9992, -3.0000},
    {3.9996, -10.9998, 6.0000},
    {-3.0000, 6.0000, -3.0000}
};
float R[3][3] = {
    {2.0010, 3.9996, -3.0000},
    {1.9992, -10.9998, 6.0000},
    {-3.0000, 6.0000, -3.0000}
};
float S[3][3] = {
    {21.4, 56.88, 67.8},
    {3, 5, 7},
    {0, 1, 3}
};

float T[3][3] = {
    {-0.0583, 0.7489, -0.4308},
    { 0.0655, -0.4675, -0.3903},
    { -0.0218, 0.1558, 0.4634}
};

float Identity[3][3] = {
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1}
};

float Zero[3][3] = {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
};



// **** Declare function prototypes ****
void MatrixEqualsTest();
void MatrixMultiplyTest();
void MatrixScalarMultiplyTest();
void MatrixDeterminantTest();
void MatrixAddTest();
void MatrixScalarAddTest();
void MatrixTraceTest();
void MatrixCofactorTest();
void MatrixAdjugateTest();
void MatrixInverseTest();
void MatrixTransposeTest();

int main() {
    BOARD_Init();

    /******************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     *****************************************************************************/
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            value = value + 1.0;
            A[i][j] = value;
        }
    }
    
    MatrixEqualsTest();
    MatrixMultiplyTest();
    MatrixScalarMultiplyTest();
    MatrixDeterminantTest();
    MatrixAddTest();
    MatrixScalarAddTest();
    MatrixTraceTest();
    MatrixTransposeTest();
    MatrixCofactorTest();
    MatrixAdjugateTest();
    MatrixInverseTest();
    
    percent = (totalPass / 10)*100;
    printf("\n----------------------------------------\n%1.0f out of 10 functions passed (%3.2f%%).\n", (double)totalPass, (double)percent);
    
    printf("\nOutput of MatrixPrint():\n");
    MatrixPrint(F);
    
    printf("\nExpected output of MatrixPrint():\n");
    printf("----------------------------\n"
            "| 1.0002 | 2.0002 | 3.0002 |"
            "\n----------------------------\n"
            "| 4.0002 | 5.0002 | 6.0002 |"
            "\n----------------------------\n"
            "| 7.0002 | 8.0002 | 9.0002 |"
            "\n----------------------------\n");
    


    /******************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     *****************************************************************************/

    // Returning from main() is bad form in embedded environments. So we sit and spin.
    while (1);
}

void MatrixEqualsTest() {
    testpass = 0;
    if (MatrixEquals(A, B)) {
        ++testpass;
    }
    if (MatrixEquals(A, E)) {
        ++testpass;
    } else {
        printf("fail here");
    }
    if (MatrixEquals(B, F) == 0) {
        ++testpass;
    }
    printf("\nPASSED (%d/3): MatrixEquals()", testpass);
    if (testpass == 3){
        ++totalPass;
    }
}

void MatrixMultiplyTest() {
    testpass = 0;
    MatrixMultiply(A, A, result);
    if (MatrixEquals(D, result)) {
        ++testpass;
    }
    MatrixMultiply(G, Identity, result);
    if (MatrixEquals(G, result)) {
        ++testpass;
    } else {
        printf("fail here!");
    }
    printf("\nPASSED (%d/2): MatrixMultiply()", testpass);
    if (testpass == 2){
        ++totalPass;
    }
}

void MatrixScalarMultiplyTest() {
    testpass = 0;
    MatrixScalarMultiply(2, B, result);
    if (MatrixEquals(C, result)) {
        ++testpass;
    }
    MatrixScalarMultiply(2, E, result);
    if (MatrixEquals(G, result)) {
        ++testpass;
    }
    printf("\nPASSED (%d/2): MatrixScalarMultiply()", testpass);
}

void MatrixDeterminantTest() {
    testpass = 0;
    //printf("\n%f",MatrixDeterminant(A));
    if (fabs(MatrixDeterminant(A)) - 0 <= FP_DELTA) {
        ++testpass;
    }
    if (fabs(MatrixDeterminant(A)) - 0 <= FP_DELTA) {
        ++testpass;
    }
    printf("\nPASSED (%d/2): MatrixDeterminant()", testpass);if (testpass == 2){
        ++totalPass;
    }
}

void MatrixAddTest() {
    testpass = 0;
    MatrixAdd(A, A, result);
    if (MatrixEquals(C, result)) {
        ++testpass;
    }
    if (MatrixEquals(C, result)) {
        ++testpass;
    }
    printf("\nPASSED (%d/2): MatrixAdd()", testpass);
    if (testpass == 2){
        ++totalPass;
    }
}

void MatrixScalarAddTest() {
    testpass = 0;
    MatrixScalarAdd(0.0002, A, result);
    if (MatrixEquals(F, result)) {
        ++testpass;
    }
    MatrixScalarAdd(0.0002, A, result);
    if (MatrixEquals(F, result)) {
        ++testpass;
    }
    printf("\nPASSED (%d/2): MatrixScalarAdd()", testpass);
    if (testpass == 2){
        ++totalPass;
    }
}

void MatrixTraceTest() {
    testpass = 0;
    float trace = MatrixTrace(F);
    if (equals(trace, 15.0006)) {
        ++testpass;
    }
    trace = MatrixTrace(H);
    if (equals(trace, -.0002)) {
        ++testpass;
    }
    printf("\nPASSED (%d/2): MatrixTrace()", testpass);
    if (testpass == 2){
        ++totalPass;
    }
}

void MatrixTransposeTest() {
    testpass = 0;
    MatrixTranspose(A, result);
    if (MatrixEquals(I, result)) {
        ++testpass;
    }
    MatrixTranspose(H, result);
    if (MatrixEquals(J, result)) {
        ++testpass;
    }
    printf("\nPASSED (%d/2): MatrixTranspose()", testpass);
    if (testpass == 2){
        ++totalPass;
    }
}

void MatrixAdjugateTest() {
    testpass = 0;
    MatrixAdjugate(Identity, result);
    if (MatrixEquals(Identity, result)) {
        ++testpass;
    }
    MatrixAdjugate(B, result);
    if (MatrixEquals(result, K)) {
        ++testpass;
    }
    MatrixAdjugate(P, result);
    if (MatrixEquals(result, R)) {
        ++testpass;
    }
    printf("\nPASSED (%d/3): MatrixAdjugate()", testpass);
    if (testpass == 3){
        ++totalPass;
    }
}

void MatrixCofactorTest() {
    testpass = 0;
    MatrixCofactor(K, result);
    if (MatrixEquals(result, Zero)) {
        ++testpass;
    }
    MatrixCofactor(N, result);
    if (MatrixEquals(result, O)) {
        ++testpass;
    }
    MatrixCofactor(P, result);
    if (MatrixEquals(result, Q)) {
        ++testpass;
    }
    printf("\nPASSED (%d/3): MatrixCofactor()", testpass);
    if (testpass == 3){
        ++totalPass;
    }
}

void MatrixInverseTest() {
    testpass = 0;
    MatrixInverse(L, result);
    if (MatrixEquals(result, M)) {
        ++testpass;
    }
    MatrixInverse(S, result);
    if (MatrixEquals(result, T)) {
        ++testpass;
    }
    printf("\nPASSED (%d/2): MatrixInverse()", testpass);
    if (testpass == 2){
        ++totalPass;
    }
}
