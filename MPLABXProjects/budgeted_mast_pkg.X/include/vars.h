extern int biasCount;
extern int attEstDelay;
extern float deltaT;
extern float roll, pitch, yaw;
extern int loopStep;

//extern float biasX = 17, biasY = 30, biasZ = -45; // rammess gyro biases
//extern int biasX = 40, biasY = -118, biasZ = 44;   // 8.75 mdps/LSB biases
extern float biasX, biasY, biasZ;   // 70 mdps/LSB biases
extern float wnorm, s, c;

extern float gyroX, gyroY, gyroZ;
extern float accelX, accelY, accelZ;

extern float eye[3][3];

extern float gyroInput[3][1];

extern float Ro[3][3];
extern float R[3][3];
extern float Rplus[3][3];
extern float Rtrans[3][3];
extern float RplusTrans[3][3];
extern float eyeTest[3][3];

extern float skewSymGyrosDeltaT[3][3];
extern float RSkew[3][3];
extern float RSkewDelta[3][3];
extern float rx[3][3];
extern float gyrosDeltaT[3][1];
extern float termOne[3][3];
extern float termTwo[3][3];
extern float rxrx[3][3];
extern float rodrig[3][3];
extern float Rexp[3][3];
////////////////////////////////////////////
extern float accelReading[3][1];
extern float accelInertialReading[3][1];
extern float normAccel;
extern float normAccelInertial;
extern float accel[3][1];
extern float accelInertial[3][1];
//
extern float biasEstimate[3][1];
extern float Bminus[3][1];
extern float gyroInWithBiasEst[3][1];
//
extern float accelSkew[3][3];
extern float Rminus[3][3];
extern float RminusXaccelInterial[3][1];
extern float wmeas_a[3][1];
//
extern float KpXwmeas_a[3][1];
extern float gyroInputWithFeedback[3][1];
//
extern float KiXwmeas_a[3][1];
extern float bdot[3][1];
//
extern float Bplus[3][1];
