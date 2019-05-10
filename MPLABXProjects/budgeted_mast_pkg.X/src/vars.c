int biasCount = 1;
int attEstDelay = 500;
float deltaT = 0.05;
float roll, pitch, yaw;
int loopStep = 0;

//float biasX = 17, biasY = 30, biasZ = -45; // rammess gyro biases
//int biasX = 40, biasY = -118, biasZ = 44;   // 8.75 mdps/LSB biases
float biasX = -0.134259259, biasY = -33.1219135, biasZ = 17.83641975;   // 70 mdps/LSB biases
float wnorm, s, c;

float gyroX, gyroY, gyroZ;
float accelX, accelY, accelZ;

float eye[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
};

float gyroInput[3][1] = {};

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

float skewSymGyrosDeltaT[3][3] = {
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
////////////////////////////////////////////
float accelReading[3][1] = {};
float accelInertialReading[3][1] = {
    {0},
    {0},
    {1}
};
float normAccel;
float normAccelInertial;
float accel[3][1] = {};
float accelInertial[3][1] = {};
//
float biasEstimate[3][1] = {
    {0},
    {0},
    {0}
};
float Bminus[3][1] = {
    {0},
    {0},
    {0}
};
float gyroInWithBiasEst[3][1] = {};
//
float accelSkew[3][3] = {};
float Rminus[3][3] = {};
float RminusXaccelInterial[3][1] = {};
float wmeas_a[3][1] = {};
//
float KpXwmeas_a[3][1] = {};
float gyroInputWithFeedback[3][1] = {};
//
float KiXwmeas_a[3][1] = {};
float bdot[3][1] = {};
//
float Bplus[3][1] = {};
