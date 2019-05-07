//MatrixMath.c
//Joseph Skinner
//jlskinne
//Library of matrix functions

#include "MatrixMath.h"
#include <Math.h>
#include <stdio.h>
#include "BOARD.h"
#define TRUE 1
#define FALSE 0
#define FP_DELTA 0.0001

int i, j, k;
float result[3][3], temp[3][3];
float a, b;

void VectorAdd(float vec1[3][1], float vec2[3][1], float resultVec[3][1]) {
    for (i = 0; i < 3; i++) {
        resultVec[i][0] = vec1[i][0] + vec2[i][0];
    }
}

void VectorScalarMultiply(float x, float vec[3][1], float result[3][1]) {
    for (i = 0; i < 3; i++) {
        result[i][0] = x * vec[i][0];
    }
}

void MatrixMultiplyVector(float mat[3][3], float vec[3][1], float result[3][1]) {
    float sum = 0;
    for (i = 0; i < 3; i++) {
        sum = 0;
        for (j = 0; j < 3; j++) {
            sum += mat[i][j] * vec[j][0];
            result[i][0] = sum;
        }
    }
}

void rcross(float vec[3][1], float result[3][3]) {
    result[0][0] = 0;
    result[0][1] = -vec[2][0];
    result[0][2] = vec[1][0];
    result[1][0] = vec[2][0];
    result[1][1] = 0;
    result[1][2] = -vec[0][0];
    result[2][0] = -vec[1][0];
    result[2][1] = vec[0][0];
    result[2][2] = 0;
}

float VectorNorm(float vec[3][1]){
      return(sqrt((vec[0][0] * vec[0][0]) + (vec[1][0] * vec[1][0]) + (vec[2][0] * vec[2][0])));
}

int MatrixEquals(float mat1[3][3], float mat2[3][3]) {
    k = 0;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (equals(mat1[i][j], mat2[i][j])) {
                //printf("\ndifference is: %f", (double) (fabs(mat1[i][j] - mat2[i][j])));
            } else if (fabs(mat1[i][j] - mat2[i][j]) > FP_DELTA) {
                //printf("\nFor elements %d,%d delta = %f", i, j, (double) (fabs(mat1[i][j] - mat2[i][j])));
                return 0;
            }
        }
    }
    return 1;
}

void MatrixAdd(float mat1[3][3], float mat2[3][3], float result[3][3]) {
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {

            result[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
}

void MatrixTranspose(float mat[3][3], float result[3][3]) {

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            result[i][j] = mat[j][i];
        }
    }
}

void MatrixScalarMultiply(float x, float mat[3][3], float result[3][3]) {
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            result[i][j] = x * mat[i][j];
        }
    }
}

void MatrixScalarAdd(float x, float mat[3][3], float result[3][3]) {
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            result[i][j] = x + mat[i][j];
        }
    }

}

void MatrixMultiply(float mat1[3][3], float mat2[3][3], float result[3][3]) {
    float sum = 0;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            sum = 0;
            for (k = 0; k < 3; k++) {
                sum += mat1[i][k] * mat2[k][j];
                result[i][j] = sum;
            }
        }
    }
}

float MatrixTrace(float mat[3][3]) {
    float traceSum = 0;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (i == j) {
                traceSum += mat[i][j];
            }

        }
    }
    return traceSum;
}

float MatrixDeterminant(float mat[3][3]) {
    float determinant = 0;
    determinant += mat[0][0] * mat[1][1] * mat[2][2];
    determinant += mat[0][1] * mat[1][2] * mat[2][0];
    determinant += mat[0][2] * mat[1][0] * mat[2][1];
    determinant -= mat[2][0] * mat[1][1] * mat[0][2];
    determinant -= mat[2][1] * mat[1][2] * mat[0][0];
    determinant -= mat[2][2] * mat[1][0] * mat[0][1];

    return determinant;
}

void MatrixInverse(float mat[3][3], float result[3][3]) {
    MatrixAdjugate(mat, result);
    MatrixScalarMultiply(1 / MatrixDeterminant(mat), result, result);
}

void MatrixAdjugate(float mat[3][3], float result[3][3]) {
    MatrixCofactor(mat, result);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            temp[i][j] = result[i][j];
        }
    }
    MatrixTranspose(temp, result);
}

void MatrixCofactor(float mat[3][3], float result[3][3]) {
    result[0][0] = mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1];
    result[0][1] = mat[1][2] * mat[2][0] - mat[1][0] * mat[2][2];
    result[0][2] = mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0];
    result[1][0] = mat[0][2] * mat[2][1] - mat[0][1] * mat[2][2];
    result[1][1] = mat[0][0] * mat[2][2] - mat[0][2] * mat[2][0];
    result[1][2] = mat[0][1] * mat[2][0] - mat[0][0] * mat[2][1];
    result[2][0] = mat[0][1] * mat[1][2] - mat[0][2] * mat[1][1];
    result[2][1] = mat[0][2] * mat[1][0] - mat[0][0] * mat[1][2];
    result[2][2] = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];

}

void MatrixPrint2(float mat[3][3]) {
    //printf("float name[3][3] = {\n{");
    for (i = 0; i < 3; i++) {
        printf("\r\n");
        for (j = 0; j < 3; j++) {
            printf("%0.2f, ", (double) mat[i][j]);
        }
    }
    printf("\r\n\r\n");

    //printf("}\n};");
}

void MatrixPrint(float mat[3][3]) {
    printf("----------------------------\r\n"
            "| %.4f | %.4f | %.4f |"
            "\r\n----------------------------\r\n"
            "| %.4f | %.4f | %.4f |"
            "\r\n----------------------------\r\n"
            "| %.4f | %.4f | %.4f |"
            "\r\n----------------------------\r\n"
            , (double) mat[0][0], (double) mat[0][1], (double) mat[0][2]
            , (double) mat[1][0], (double) mat[1][1], (double) mat[1][2]
            , (double) mat[2][0], (double) mat[2][1], (double) mat[2][2]);
}

int equals(float a, float b) {
    if ((a - FP_DELTA <= b) && (a + FP_DELTA >= b)) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/*//(mat1[i][j] - FP_DELTA <= mat2[i][j]) && (mat1[i][j] + FP_DELTA >= mat2[i][j])*/