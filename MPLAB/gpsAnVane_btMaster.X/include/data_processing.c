#include "gpsLib.h"
#include "data_processing.h"
#include <math.h>

#define PI 3.14159

float appWindHeading, appWindSpeed;
float trueWindHeading, trueWindSpeed;

/*SetBATWindVec funcs set the 2D vector components, speed, heading for each wind vector*/
void setBoatWindVec(float boatWindVec[2][1]) {
    float track = getTrack();
    boatWindVec[0][0] = getSpeed() * sin(PI * track / 180);
    boatWindVec[1][0] = getSpeed() * cos(PI * track / 180);
}

void setAppWindVec(float appWindVec[2][1]) {
    appWindHeading = ((int) getTrack() + (int) getWindDegree()) % 360;
    appWindVec[0][0] = getWindSpeed() * sin(PI * appWindHeading / 180);
    appWindVec[1][0] = getWindSpeed() * cos(PI * appWindHeading / 180);
    appWindSpeed = sqrt(appWindVec[0][0] * appWindVec[0][0] + appWindVec[1][0] * appWindVec[1][0]);
}

void setTrueWindVec(float trueWindVec[2][1], float boatWindVec[2][1], float appWindVec[2][1]) {
    trueWindVec[0][0] = appWindVec[0][0] - boatWindVec[0][0];
    trueWindVec[1][0] = appWindVec[1][0] - boatWindVec[1][0];
    trueWindSpeed = sqrt(trueWindVec[0][0] * trueWindVec[0][0] + trueWindVec[1][0] * trueWindVec[1][0]);
    float XYangle = atan2(trueWindVec[1][0], trueWindVec[0][0]);
    //printf("XYangle = %.2f\r\n", XYangle);
    XYangle = 180 * XYangle / PI;
    if (XYangle >= 0 && XYangle < 90) {
        trueWindHeading = (90 - XYangle);
    } else if (XYangle > 90 && XYangle < 180) {
        trueWindHeading = 360.0 + (90 - XYangle);
    } else if (XYangle < 0){
        trueWindHeading = (-1.0 * (XYangle - 90));
    } else {
        trueWindHeading = -1;
    }
}

//getWindSpeed() in gpsLib.c?

//getBoatWindHeading() == getWindDegree() also in gpsLIb.c?

float getAppWindHeading(void) {
    return appWindHeading;
}

float getAppWindSpeed(void) {
    return appWindSpeed;
};

float getTrueWindHeading(void) {
    return trueWindHeading;
}

float getTrueWindSpeed(void) {
    return trueWindSpeed;
}


