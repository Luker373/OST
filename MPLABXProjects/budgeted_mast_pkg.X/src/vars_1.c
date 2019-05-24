  float radToDeg = 180 / 3.1415;
  float rollAvg, pitchAvg, compassAvg, rollSum = 0, pitchSum = 0, compassSum = 0, magHeading, rawCompassHeading, alignedCompassHeading;
  float magXCorr, magYCorr, magZCorr;
?
  float accel[3][1] = {};
  float roll[MOVING] = {};
  float pitch[MOVING] = {};
  float compass[MOVING] = {};
?
?
  float accelNullVec[3][1] = {
    {ACCEL_X_NULL},
    {ACCEL_Y_NULL},
    {ACCEL_Z_NULL}
  };
?
  float accelScale[3][3] = {
    {0.6064e-04, 0.0023e-04, 0.0007e-04},
    {0.0016e-04, 0.6062e-04, -0.0010e-04},
    {0.0006e-04, -0.0062e-04, 0.5977e-04}
  };
?
  float accelReading[3][1] = {};
  float accelVec[3][1] = {};
  float accelVecScaled[3][1] = {};
  float accelVecShifted[3][1] = {};
?
  float magNullVec[3][1] = {
    {MAG_X_NULL},
    {MAG_Y_NULL},
    {MAG_Z_NULL}
  };
  float magScale[3][3] = {
    {0.0083, 0.0000, 0.0001},
    {-0.0000, 0.0085, 0.0002},
    {0.0001, 0.0002, 0.0076}
  };
?
  float magReading[3][1] = {};
  float magReadingAligned[3][1] = {};
  float magVec[3][1] = {};
  float magVecScaled[3][1] = {};
  float magVecShifted[3][1] = {};

  //BASIC is BETTER
    float Rmis[3][3] = {
      {0, 1, 0},
      {1, 0, 0},
      {0, 0, -1}
    };
  float RmisT[3][3] = {};