/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "MatrixFunctions.h"

/* TODO:  Include other files here if needed. */

/** 
  @Function
    void rcross(float vec[3][1])

  @Summary
 Makes skew-symmetric matrix from 3x1 vector.

 */
void rcross(float vec[3][1], float skewm[3][3]){
    
    //float skewm[3][3];
    
    skewm[0][0] = 0; skewm[0][1] = -1*(vec[2][0]); skewm[0][2] = vec[1][0];
    skewm[1][0] = vec[2][0]; skewm[1][1] = 0; skewm[1][2] = -1*(vec[0][0]);
    skewm[2][0] = -1*(vec[1][0]); skewm[2][1] = vec[0][0]; skewm[2][2] = 0;
    
}

void colnorm(float mat[3][3], float result[3][3], int mr, int mc){
    
    float sqm[3][3];
    float rnorm[3][1], rnormpn1[3][1];
    float cvofones[3][1] = {1,1,1};
    float denom[1];
    //float normd[3][3];
    int Count = 0;
    
    MatSquared(mat, sqm, 3, 3); // square the matrix
    MatNorm(sqm, rnorm, 3, 3); // sum up column elements in squared matrix to
                                // make up row vector, then sqrt of each element
    
//    VecToNegFirstPower(rnorm, rnormpn1, 1, 3); // calculate norm to neg 1 power
    
    //for(Count = 0; Count < 3; Count++){
    //    denom[0] = denom[0] + (cvofones[Count][0]*rnormpn1[0][Count]);
    //}
    
    MatrixScalarMultiply(denom, mat, result, 3, 3);
    
}

void rexp(float vec[3][1], float rexp[3][3]){
    
    /*float skewSymGyrosDeltaT[3][3] = {
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
    float rx[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    float gyrosDeltaT[3][1] = {
        {0},
        {0},
        {0}
    };
    float termOne[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    float termTwo[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    float rxrx[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    float rodrig[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    float Rexp[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    float eye[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    
    float wnorm, s, c;
    
    wnorm = sqrt((vec[0][0] * vec[0][0]) + (vec[1][0] * vec[1][0]) + (vec[2][0] * vec[2][0]));
            //printf("wnorm = %0.3f\r\n", wnorm);
            rcross(vec, skewSymGyrosDeltaT);
            if (wnorm <= 0.01) {
                s = 1 - pow(wnorm / 2, 2) / 6 + pow(wnorm / 2, 4) / 120 - pow(wnorm / 2, 6) / 5040 + pow(wnorm / 2, 8) / 362880 - pow(wnorm / 2, 10) / 39916800;
            } else {
                s = sin(wnorm / 2) / (wnorm / 2);
            }
            c = cos(wnorm / 2);

            float x[1], y[1];
            x[0] = s*c;
            y[0] = s*(s/2);
            MatrixScalarMultiply(x, skewSymGyrosDeltaT, termOne, 3, 3);

            MatrixScalarMultiply(y, skewSymGyrosDeltaT, termTwo, 3, 3);
            MatrixMultiply(termTwo, skewSymGyrosDeltaT, rxrx, 3, 3, 3, 3);
            MatrixAdd(termOne, rxrx, rodrig, 3, 3, 3, 3);
            //            MatrixMultiply(skewSymGyrosDeltaT, skewSymGyrosDeltaT, rxrx);
            //            MatrixScalarMultiply(s * s / 2, rxrx, termTwo);
            //            MatrixAdd(termOne, termTwo, rodrig);

            MatrixAdd(eye, rodrig, Rexp, 3, 3, 3, 3);
     */
  //Original Code   
    float sqv[3][1];
    float vnorm[1], c[1], s[1], sc[1], s2[1];
    float Rexp[3][3], Rexp2[3][3], Rx2[3][3], 
    Rexp3[3][3], Rexp1P2[3][3], rx[3][3];
    float ID[3][3] = {{1,0,0},
                       {0,1,0},
                       {0,0,1}};
    //int Count = 0;
   
    VecSquared(vec, sqv, 3); // vector, return vector
    VecNorm(sqv, vnorm, 3); // vector,return floay
 
    rcross(vec, rx);
    
    c[0] = cos((vnorm[0])/2);
    
    if(vnorm[0] >= 0.01){
        s[0] = ((sin((vnorm[0])/2))/(vnorm[0]/2));
    } else {
        //s[0] = cos(vnorm[0])/1; // limit of sin(x)/x as x approaches zero uses 
                        // LHospital's rule, take lim of deriv of top and
                        // bottom, gets cos(x)/1
            // do Taylor series approximation of sinc function
        /*s[0] = ((sin(0.1))/0.1) 
        + (((cos(0.1)/(0.1))-((sin(0.1))/(0.1*0.1)))*((vnorm[0]/2)-0.1))
        + ((((((0.1*0.1)-2)*(sin(0.1)))+(2*0.1*(cos(0.1))))/(0.1*0.1*0.1))/2)
        *((((vnorm[0])/2)-0.1)*(((vnorm[0])/2)-0.1));*/
        
        /*s[0] = 1-(((vnorm[0]/2)*(vnorm[0]/2))/6)
        +(((vnorm[0]/2)*(vnorm[0]/2)*(vnorm[0]/2)*(vnorm[0]/2))/24)
        -(((vnorm[0]/2)*(vnorm[0]/2)*(vnorm[0]/2)*(vnorm[0]/2)
        *(vnorm[0]/2)*(vnorm[0]/2))/120)
        +(((vnorm[0]/2)*(vnorm[0]/2)*(vnorm[0]/2)*(vnorm[0]/2)
        *(vnorm[0]/2)*(vnorm[0]/2)*(vnorm[0]/2)*(vnorm[0]/2))/720);*/ // add the asterisk slash here
        s[0] = 1-(((vnorm[0]/2)*(vnorm[0]/2))/6)
        +(((vnorm[0]/2)*(vnorm[0]/2)*(vnorm[0]/2)*(vnorm[0]/2))/120)
        -(((vnorm[0]/2)*(vnorm[0]/2)*(vnorm[0]/2)*(vnorm[0]/2)
        *(vnorm[0]/2)*(vnorm[0]/2))/5040)
        +(((vnorm[0]/2)*(vnorm[0]/2)*(vnorm[0]/2)*(vnorm[0]/2)
        *(vnorm[0]/2)*(vnorm[0]/2)*(vnorm[0]/2)*(vnorm[0]/2))/362880);
        // factorial 3 = 6, factorial 4 = 24, factorial 5 = 120, factorial 6 = 720 
    }
    
    sc[0] = s[0]*c[0], s2[0] = s[0]*(s[0]/2);
    MatrixScalarMultiply(sc, rx, Rexp2, 3, 3); // make second r_exp term
    MatrixScalarMultiply(s2, rx, Rx2, 3 ,3); // make scaled up rx for 3rd rexp term
    MatrixMultiply(Rx2, rx, Rexp3, 3, 3, 3, 3);  // make 3rd rexp term
    MatrixAdd(ID, Rexp2, Rexp1P2, 3, 3, 3, 3);
    MatrixAdd(Rexp1P2, Rexp3, rexp, 3, 3, 3, 3);
    /*MatrixScalarMultiply(rexp2, rx, Rexp2, 3, 3);
    MatrixScalarMultiply(rexp3, rx, Rexp3, 3, 3);
    MatrixMultiply(Rexp3, rx, )*/
    // magnitude implementation
    //for(Count = 0; Count < 3; Count++){
    //w2cnorm[Count][0] = vnorm[0][Count]; // turns wnrm row vector into col vec
    
   // in the R_exp file, the s and c values are constants, not row vectors
    /*for(Count = 0; Count < 3; Count++){
        rexp2 = rexp2 + (s[0][Count]*c[Count][0]);
        rexp3 = rexp3 + (s[0][Count]*(sc[Count][0]));
    }*/
    
}

void ExtractEulerFromDCM(float mat[3][3], double angles[3]){
    
    double radpitch;
    double radyaw;
    double radroll;
    double degpitchpos;
    double degyawpos;
    double degrollpos;
    double degpitchneg;
    double degyawneg;
    double degrollneg;
    
    radpitch = (double)(-1*(asin((mat[0][2])))); // want to do inverse sin of this, not sin
    // do it the atan2 way
    radyaw = (double)(atan2(mat[0][1], mat[0][0])); // cosTcosY/cosTsinY = cosY/sinY
    radroll = (double)(atan2(mat[1][2], mat[2][2]));
    
    //radyaw = (double)(asin((mat[0][1])/cos(radpitch)));
    //degyawpos = radyaw*(180/3.141593);
    
    //radroll = (double)(asin((mat[1][2])/cos(radpitch)));
    //degrollpos = radroll*(180/3.141593);
    
    angles[0] = radroll*(180/3.141593);
    angles[1] = radpitch*(180/3.141593);
    angles[2] = radyaw*(180/3.141593);
       
}

void CheckOrtho(float R[3][3], float check[3][3], float error[3][1]){
    
    float RT[3][3], RRT[3][3], NID[3][3];
    float ID[3][3] = {{1,0,0},{0,1,0},{0,0,1}};
    float n1[1];
    n1[0] = -1.0;
    
    MatrixTranspose(R, RT); // if ortho, matrix times its transpose...
    MatrixMultiply(R, RT, RRT, 3, 3, 3, 3); // ...should equal the ID matrix
    MatrixScalarMultiply(n1, ID, NID, 3, 3); // if we subtract ID...
    MatrixAdd(RRT, NID, check, 3, 3, 3, 3); // we should get 0's in result matrix
    
    MatNorm(check, error, 3, 3);
    
}

void DCMFromTriad(float magData[3][1], float accelData[3][1], float magIn[3][1], 
float accelIn[3][1], float R[3][3]){
    
    float anorm[1], mnorm[1], ainorm[1], minorm[1],
    matnorm[1], mat2norm[1], A0[3][3], A1[3][3], aunorm, munorm, 
    aiunorm, miunorm, A1T[3][3], A[3][3], auv[3][1], muv[3][1], 
    aiuv[3][1], miuv[3][1], normM[3][1], adsq[3][1], mdsq[3][1], 
    aisq[3][1], misq[3][1], m[3][1], mm[3][3], 
    normm[3][1], A03[3][1], M[3][1], MM[3][3], A13[3][1], 
    rxmags[3][3], rxmagIn[3][3], matnormbox, mat2normbox;
    float mnsq[3][1], Mnsq[3][1];
            
            int j, i, k ,l;
    
    VecSquared(accelData, adsq, 3);
    VecNorm(adsq, anorm, 3);
    aunorm = 1.0/anorm[0];
    
    VecSquared(magData, mdsq, 3);
    VecNorm(mdsq, mnorm, 3);
    munorm = 1.0/mnorm[0];
    
    VecSquared(accelIn, aisq, 3);
    VecNorm(aisq, ainorm, 3);
    aiunorm = 1.0/ainorm[0];
    
    VecSquared(magIn, misq, 3);
    VecNorm(misq, minorm, 3);
    miunorm = 1.0/minorm[0];
    
    // make vectors unit vectors
    VectorScalarMultiply(aunorm, accelData, auv, 3);
    VectorScalarMultiply(munorm, magData, muv, 3);
    VectorScalarMultiply(aiunorm, accelIn, aiuv, 3);
    VectorScalarMultiply(miunorm, magIn, miuv, 3); 

    rcross(muv, mm);
    MatVecMultiply(mm, auv, m, 3, 3, 3);
    /*printf("1st m is \n"); 
    for (i = 0; i < 3; i++){ 
        //for(j = 0; j < 3; j++){
            printf("%f ", m[i][0]); 
        //}
        printf("\r\n");
    }
    printf("\r\n"); */
    VecSquared(m, mnsq, 3);
    VecNorm(mnsq, matnorm, 3);
   
    matnormbox = 1/matnorm[0]; 
    VectorScalarMultiply(matnormbox, m, normm, 3);
    /*printf("2nd m is \n"); 
    for (i = 0; i < 3; i++){ 
        //for(j = 0; j < 3; j++){
            printf("%f ", normm[i][0]); 
        //}
        printf("\r\n");
    }
    printf("\r\n"); */
    
    rcross(miuv, MM);
    MatVecMultiply(MM, aiuv, M, 3, 3, 3);

    VecSquared(M, Mnsq, 3);
    VecNorm(Mnsq, mat2norm, 3);
    mat2normbox = 1/mat2norm[0]; 
    VectorScalarMultiply(mat2normbox, M, normM, 3);// good
    /*printf("M matrix is \n"); 
    for (j = 0; j < 3; j++){ 
        printf("%f ", normM[j][0]); 
        printf("\r\n"); 
    }
    printf("\r\n");*/
    
    rcross(muv, rxmags);
    MatVecMultiply(rxmags, normm, A13, 3, 3, 3);
    // m is the issue
    rcross(miuv, rxmagIn);
    MatVecMultiply(rxmagIn, normM, A03, 3, 3, 3);
    
    /*printf("M unit vector is:\r\n");
    for(i = 0; i < 3; i++){
        printf("%f \r\n", muv[i][0]);
    }
    printf("\r\n"); 
    
    printf("mm = :\r\n");
    for(j = 0; j < 3; j++){
       printf("%f \r\n", normm[j][0]);
    }
    printf("\r\n"); 
    
    printf("A13 matrix is \n"); 
    for (i = 0; i < 3; i++){ 
        printf("%f ", A13[i][0]); 
        printf("\r\n"); 
    }
    printf("\r\n");
    
    printf("A03 matrix is \n"); 
    for (i = 0; i < 3; i++){ 
        printf("%f ", A03[i][0]); 
        printf("\r\n"); 
    }
    printf("\r\n");*/
    
    for(j = 0; j < 3; j++){
        A0[j][0] = miuv[j][0];
        A0[j][1] = M[j][0];
        A0[j][2] = A03[j][0];
    }
        //A0[j][1] = M[j][0];
        //A0[j][2] = A03[j][0];
    for(i = 0; i < 3; i++){    
        A1[i][0] = muv[i][0];
        A1[i][1] = normm[i][0];
        A1[i][2] = A13[i][0];
    }
    
   /* printf("A0 matrix is \n"); 
    for (i = 0; i < 3; i++){ 
        for(j = 0; j < 3; j++){
            printf("%f ", A0[i][j]); 
        }
        printf("\r\n"); 
    }
    printf("\r\n");
    
    printf("A1 matrix is \n"); 
    for (i = 0; i < 3; i++){ 
        for(j = 0; j < 3; j++){
            printf("%f ", A1[i][j]); 
        }
        printf("\r\n"); 
    }
    printf("\r\n");*/
    
    MatrixTranspose(A1, A1T);
    /*printf("Result matrix is \n"); 
    for (i = 0; i < 3; i++){ 
        for (j = 0; j < 3; j++){ 
           printf("%f ", A1[i][j]); 
        }
        printf("\r\n"); 
    }
    printf("\r\n");*/
    MatrixMultiply(A0, A1T, A, 3, 3, 3, 3);
    //MatrixTranspose(A1, A1T);
    /*printf("Result matrix is \n"); 
    for (i = 0; i < 3; i++){ 
        for (j = 0; j < 3; j++){ 
           printf("%f ", A[i][j]); 
        }
        printf("\r\n"); 
    }
    printf("\r\n");*/
    MatrixTranspose(A, R);
    /*printf("Result matrix is \n"); 
    for (i = 0; i < 3; i++){ 
        for (j = 0; j < 3; j++){ 
           printf("%f ", R[i][j]); 
        }
        printf("\r\n"); 
    }
    printf("\r\n");*/
    
}

/*void DCMFromTriad(float magData[3][1], float accelData[3][1], float magIn[3][1], 
float accelIn[3][1], float R[3][3]){
    
    float anorm[1], mnorm[1], ainorm[1], minorm[1],
    matnorm[1], Muv[3][1], mat2norm[1], A0[3][3], A1[3][3];
    float aunorm, munorm, aiunorm, miunorm, A1T[3][3], A[3][3];
    float auv[3][1], muv[3][1], aiuv[3][1], miuv[3][1], normM[3][1],
    adsq[3][1], mdsq[3][1], aisq[3][1], misq[3][1]; 
    float m[3][1], mm[3][3], normm[3][1], A03[3][1],
    M[3][1], MM[3][3], A13[3][1], rxmags[3][3], rxmagIn[3][3];
    float matnormbox, mat2normbox;
    float mnsq[3][1], Mnsq[3][1];
            
            int j;
    
    VecSquared(accelData, adsq, 3);
    VecNorm(adsq, anorm, 3);
    aunorm = 1.0/anorm[0];
    
    VecSquared(magData, mdsq, 3);
    VecNorm(mdsq, mnorm, 3);
    munorm = 1.0/mnorm[0];
    
    VecSquared(accelIn, aisq, 3);
    VecNorm(aisq, ainorm, 3);
    aiunorm = 1.0/ainorm[0];
    
    VecSquared(magIn, misq, 3);
    VecNorm(misq, minorm, 3);
    miunorm = 1.0/minorm[0];
    
    // make vectors unit vectors
    VectorScalarMultiply(aunorm, accelData, auv, 3);
    VectorScalarMultiply(munorm, magData, muv, 3);
    VectorScalarMultiply(aiunorm, accelIn, aiuv, 3);
    VectorScalarMultiply(miunorm, magIn, miuv, 3); 
    
    rcross(muv, mm);
    MatVecMultiply(mm, auv, m, 3 ,3 ,3);
    VecSquared(m, mnsq, 3);
    VecNorm(mnsq, matnorm, 3);
    matnormbox = 1/matnorm[0]; 
    VectorScalarMultiply(matnormbox, m, normm, 3);
    
    rcross(miuv, MM);
    MatVecMultiply(MM, aiuv, M, 3 ,3 ,3);
    VecSquared(M, Mnsq, 3);
    VecNorm(Mnsq, mat2norm, 3);
    mat2normbox = 1/mat2norm[0];
    VectorScalarMultiply(mat2normbox, M, normM, 3);
    
    rcross(muv, rxmags);
    MatVecMultiply(rxmags, m, A13, 3, 3, 3);
    
    rcross(miuv, rxmagIn);
    MatVecMultiply(rxmagIn, M, A03, 3, 3, 3);
    
    for(j = 0; j < 3; j++){
        
        A0[j][0] = miuv[j][0];
        A0[j][1] = M[j][0];
        A0[j][2] = A03[j][0];
        
        A1[j][0] = muv[j][0];
        A1[j][1] = m[j][0];
        A1[j][2] = A13[j][0];
        
    }
    
    MatrixTranspose(A1, A1T);
    MatrixMultiply(A0, A1T, A, 3, 3, 3, 3);
    MatrixTranspose(A, R);
    
}*/
/* *****************************************************************************
 End of File
 */
