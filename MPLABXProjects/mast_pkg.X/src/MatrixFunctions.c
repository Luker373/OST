/* 
 * File:   MatrixFunctions.c
 * Author: RARogers
 *
 * Created on March 3, 2019, 10:00 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "math.h"
//#include "MatrixFunctions.h"

/*********************************************************************/
/***************************FUNCTIONS*********************************/
/*********************************************************************/

void MatrixMultiply(float mat1[3][3], float mat2[3][3], float result[3][3], int m1r, int m1c, int m2r, int m2c){
    
    int Row = 0;
    int Col = 0;
    int Count = 0;
    float multi = 0;
    int c1 = 0, r1 = 0, c2 = 0, r2 = 0;
  
        for (Row = 0; Row < 3; Row++) {
            for (Col = 0; Col < 3; Col++) {
                //result[Row][Col] = 0;
                for (Count = 0; Count < 3; Count++){
                    //result[Row][Col] = result[Row][Col] + (mat1[Row][Count] * mat2[Count][Col]);
                    multi = multi + mat1[Row][Count] * mat2[Count][Col];
                }
                result[Row][Col] = multi;
                multi = 0;
            }
            //result[Row][Col] = multi;
            //multi = 0;
        }
}

void MatNorm(float mat[3][3], float result[3][1], int mr, int mc){
    
    int Row = 0;
    int Col = 0;
    int Count = 0;
    float multi = 0;
    int r1 = 0, c1 = 0;
    
    r1 = mr, c1 = mc;
    
    for(Col = 0; Col < r1; Col++){
        result[Col][0] = sqrt(mat[0][Col] + mat[1][Col] + mat[2][Col]); 
        //printf("%f\n", result[0][Col]);
    }
}

void VecNorm(float vec[3][1], float result[1], int mr){
    
    //int Row = 0;
    //int Col = 0;
    //int Count = 0;
    float multi = 0;
    int r1 = 0, c1 = 0;
    
    r1 = mr; //c1 = mc;
    
    //for(Col = 0; Col < r1; Col++){
    result[0] = sqrt(vec[0][0] + vec[1][0] + vec[2][0]); 
        //printf("%f\n", result[0][Col]);
    //}
}

void MatSquared(float mat[3][3], float result[3][3], int mr, int mc){
    
    int Row = 0;
    int Col = 0;
    int Count = 0;
    int r1 = mr, c1 = mc;
    
    for(Row = 0; Row < r1; Row++){
        for(Col = 0; Col < c1; Col++){
            result[Row][Col] = mat[Row][Col] * mat[Row][Col];
        }
    }
}

void VecSquared(float vec[3][1], float result[3][1], int mr){
    
    int Row = 0;
    int Col = 0;
    int Count = 0;
    int r1 = mr; //c1 = mc;
    
    for(Row = 0; Row < r1; Row++){
        //for(Col = 0; Col < c1; Col++){
        result[Row][0] = vec[Row][0] * vec[Row][0];
        //}
    }
}

/*void VecToNegFirstPower(float vec[1][3], float result[1][3], int mr, int mc){
    
    int Row = 0;
    int Col = 0;
    int Count = 0;
    int r1 = mr, c1 = mc;
    
    for(Col = 0; Col < c1; Col++){
        result[Row][Col] = 1/vec[Row][Col];
    }
    
}*/

void MatToNegFirstPower(float mat[3][3], float result[3][3], int mr, int mc){
    
    int Row = 0;
    int Col = 0;
    int Count = 0;
    int r1 = mr, c1 = mc;
    
    for(Row = 0; Row < r1; Row++){
        for(Col = 0; Col < c1; Col++){
            result[Row][Col] = 1/mat[Row][Col];
        }
    }
    
}
/****************************************************************************/
/* Define Matrix times Vector function here.*/
/****************************************************************************/
void MatVecMultiply(float mat[3][3], float vec[3][1], float result[3][1], int mr1, int mc1, int vr){
    
    int Row = 0;
    int Col = 0;
    int Count = 0;
    float multi = 0;
    int c1 = 0, r1 = 0, vd = 0;
    
    r1 = mr1, c1 = mc1, vd = vr;
    
    for(Row = 0; Row < r1; Row++){
        result[Row][0] = (mat[Row][0]*vec[0][0])
            +(mat[Row][1]*vec[1][0])
            +(mat[Row][2]*vec[2][0]);
        //printf("%f\n", result[Row][0]);
        //multi = 0;
    }
}

/*****************************************************************************/
/*Define Matrix Addition Function here.*/

/*****************************************************************************/
void MatrixAdd(float mat1[3][3], float mat2[3][3], float result[3][3], int m1r, int m1c, int m2r, int m2c) {
    int Row = 0;
    int Col = 0;
    int Count = 0;
 
    for (Row = 0; Row < 3; Row++) {
        for (Col = 0; Col < 3; Col++) {
            //result[Row][Col] = 0;
            //for (Count = 0; Count < 3; Count++)
                result[Row][Col] = mat1[Row][Col] + mat2[Row][Col];
        }
    }
    //getch();
    //while (1);
}

void ColVecAdd(float vec1[3][1], float vec2[3][1], float result[3][1]){
    
    int Row = 0;
    int Col = 0;
    int Count = 0;
    
    for (Count = 0; Count < 3; Count++) {
        result[Count][0] = vec1[Count][0] + vec2[Count][0];
    }

}
/*****************************************************************************/
/*Define Matrix Equality Function here.*/

/*****************************************************************************/
int MatrixEquals(float mat1[3][3], float mat2[3][3]) {
    int Row = 0;
    int Col = 0;
    int Count = 0;
    int result = 0;
    int Equals = 0;
    int Total = 0;
    int Equality = 0;
    //int FP_DELTA = 0;
    /*for (Row = 0; Row < 3; Row++) {
        for (Col = 0; Col < 3; Col++) {
            scanf("%d\n", &mat1[Row][Col]);
        }
    }
    for (Row = 0; Row < 3; Row++) {
        for (Col = 0; Col < 3; Col++) {
            scanf("%d\n", &mat2[Row][Col]);
        }
    }*/
    for (Row = 0; Row < 3; Row++) {
        for (Col = 0; Col < 3; Col++) {
            Total++;
            if(mat1[Row][Col] == mat2[Row][Col]){
                Equals++;
            }
        }
    }
    
    if(Total != Equals){
        Equality = 0;
    } else {
        Equality = 1;
    }
    //getch();
    //while (1);
    return Equality;
}
/*****************************************************************************/
/*Define Matrix Scalar Multiplication Function here.*/

/*****************************************************************************/
void MatrixScalarMultiply(float x[1], float mat[3][3], float result[3][3], int mr, int mc) {
    int Row = 0;
    int Col = 0;
    int Count = 0;
    //int x = 0;
    /*for (Row = 0; Row < 3; Row++) {
        for (Col = 0; Col < 3; Col++) {
            scanf("%d\n", &mat[Row][Col]);
        }
    }*/
    for (Row = 0; Row < 3; Row++) {
        for (Col = 0; Col < 3; Col++) {
            result[Row][Col] = 0;
            for (Count = 0; Count < 3; Count++){
                result[Row][Col] = x[0]*mat[Row][Col];
            }
        }
    }
    //getch();
    //while (1);
}

void VectorScalarMultiply(float x, float vec[3][1], float result[3][1], int md){
    
    int Row = md;
    int Col = 0;
    int Count = 0;
    //int x = 0;
    /*for (Row = 0; Row < 3; Row++) {
        for (Col = 0; Col < 3; Col++) {
            scanf("%d\n", &mat[Row][Col]);
        }
    }*/
    for (Row = 0; Row < 3; Row++) {
        //for (Col = 0; Col < 3; Col++) {
        //result[Row][0] = 0;
        //for (Count = 0; Count < 3; Count++){
        result[Row][0] = x*vec[Row][0];
        //}
        //}
    }
    
}
/*****************************************************************************/
/*Define Matrix Scalar Addition Function here.*/

/*****************************************************************************/
void MatrixScalarAdd(float xx[1], float mat[3][3], float result[3][3]) {
    int Row =0;
    int Col = 0;
    int x[1];
    int Count = 0;
    for (Row = 0; Row < 3; Row++) {
        for (Col = 0; Col < 3; Col++) {
            scanf("%d\n", &mat[Row][Col]);
        }
    }
    for (Row = 0; Row < 3; Row++) {
        for (Col = 0; Col < 3; Col++) {
            result[Row][Col] = 0;
            for (Count = 0; Count < 3; Count++){
                result[Row][Col] = xx[0] + mat[Row][Col];
            }
        }
    }
    //getch();
    //while (1);
}
/*****************************************************************************/
/*Define Matrix Determinant Calculation Function here.*/

/*****************************************************************************/
float MatrixDeterminant(float mat[3][3]) {
    int Row =0;
    int Col = 0;
    int determinant = 0;
    for (Row = 0; Row < 3; Row++) {
        for (Col = 0; Col < 3; Col++) {
            scanf("%d\n", &mat[Row][Col]);
        }
    determinant = mat[0][0]*((mat[1][1]*mat[2][2]) - (mat[2][1]*mat[1][2])) - mat[0][1]*(mat[1][0]*mat[2][2] - mat[2][0]*mat[1][2]) + mat[0][2]*(mat[1][0]*mat[2][1] - mat[2][0]*mat[1][1]);
    while (1);
    //return determinant?
    }
}
/*****************************************************************************/
/*Define Matrix Trace Calculation Function here.*/

/*****************************************************************************/
float MatrixTrace(float mat[3][3]) {
    int Row = 0;
    int Col = 0;
    float trace = 0;
    for (Row = 0; Row < 3; Row++) {
        trace = trace + mat[Row][Row];
    }
}
//return trace?
/*****************************************************************************/
/*Define Matrix Transpose Calculation Function here.*/

/*****************************************************************************/
void MatrixTranspose(float mat[3][3], float result[3][3]) {
    int Row = 0;
    int Col = 0;
    for (Row = 0; Row < 3; Row++) {
        for (Col = 0; Col < 3; Col++) {
            scanf("%d\n", &mat[Row][Col]);
        }
    }
    for (Row = 0; Row < 3; Row++) {
        for (Col = 0; Col < 3; Col++) {
            result[Col][Row] = mat[Row][Col];
        }
    }
    //return result?       
}

void VectorTranspose(float vec[3][1], float result[1][3]) {
    int Row = 0;
    int Count = 0;
    /*for (Row = 0; Row < 3; Row++) {
        for (Col = 0; Col < 3; Col++) {
            scanf("%d\n", &mat[Row][Col]);
        }
    }*/
    //for (Row = 0; Row < 3; Row++) {
        for (Count = 0; Count < 3; Count++) {
            result[0][Count] = vec[Count][0];
        }
    //}
    //return result?       
}
/*****************************************************************************/
/*Define Matrix Inversion Function here.*/

/*****************************************************************************/
/*void MatrixInverse(float mat[3][3], float result[3][3]) {
    int Row = 0;
    int Col = 0;
    int determinant = 0;
    for (Row = 0; Row < 3; Row++) {
        for (Col = 0; Col < 3; Col++) {
            scanf("%d\n", &mat[Row][Col]);
        }
    }
    for (Row = 0; Row < 3; Row++){
    determinant = determinant + (mat[0][Row]*(mat[1][(Row+1)%3]*mat[2][(Row+2)%3] - mat[1][(Row+2)%3]*mat[2][(Row+1)%3]));
        for (Row = 0; Row < 3; Row++) {
            for (Col = 0; Col < 3; Col++) {
                result[][] = ((mat[(Row+1)%3][(Col+1)%3]
                        *mat[(Row+2)%3][(Col+2)%3])
                        -(mat[(Row+1)%3][(Col+2)%3]
                        *mat[(Row+2)%3][(Col+1)%3])
                        /determinant);
            }
        }
    }
}*/


//***Declare variables and/or matrices here.***//

/*****************************************************************************/
/*Define Matrix Multiplication Function here.*/
/*****************************************************************************/

/*****************************************************************************/
/*Define Matrix Printing Function here.*/
/*****************************************************************************/

void MatrixPrint(float mat[3][3]){
    int Col = 0;
    int Row = 0;
    for (Row = 0; Row < 3; Row++) {
        for (Col = 0; Col < 3; Col++) {
            printf(" %f", mat[Row][Col]);
        printf("\n");
        }
    }
}

//}
    /*for (Row = 0; Row < m1r; Row++) {
        for (Col = 0; Col < m2c; Col++) {
            result[Row][Col] = 0;
            for (Count = 0; Count < m2r; Count++){
              result[Row][Col] = result[Row][Col] + (mat1[Row][Count] * mat2[Count][Col]);
            }
        }
       // result[Row][Col] = multi;
        //result = 0;
    }*/
    //return 1; //or while (1)
/*for (Count = 0; Count < 3; Count++)
                result = abs(mat1[Row][Col] - mat2[Row][Col]);
            if (result != 0){
                result = result - FP_DELTA;
            }
            if (result != 0){
                
            } else {
                return result;  
             * } */     
    