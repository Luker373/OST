#include "gpsLib.h"
#include "data_processing.h"
#include <math.h>

#define PI 3.14159


void setBoatWindVec(float **boatWindVec) {
	float track = getTrack();
	boatWindVec[0][0] = getSpeed() * sin(PI*track/180);
	boatWindVec[1][0] = getSpeed() * cos(PI*track/180);
}

void setAppWindVec(float **appWindVec) {
	float appWindHeading = getTrack() + getWindDegree();
	appWindVec[0][0] = getWindSpeed() * sin(PI*appWindHeading/180);
	appWindVec[1][0] = getWindSpeed() * cos(PI*appWindHeading/180);
}


void setTrueWindVec(float **trueWindVec, float **boatWindVec, float **appWindVec) {
	trueWindVec[0][0] = boatWindVec[0][0] - appWindVec[0][0];
	trueWindVec[1][0] = boatWindVec[1][0] - appWindVec[1][0];
}

// trueWindVec = malloc(sizeofArr * sizeof(float*))
// for n in sizeofArr
    // trueWindVec[n] = malloc(sizeofRow * sizeof(float))

float getTrueWindHeading(float **trueWindVec, float **boatWindVec, float **appWindVec){
	//going to take some carefull thought, negative angles?, piecewise quadrant function, or trig function works in many quadrants?
	float XYangle = atan2(trueWindVec[1][0], trueWindVec[0][0]);
    XYangle = 180*XYangle/PI;
	if (XYangle >= 0){
		return (90 - XYangle);	
	}else if (XYangle < 0){
		return (-1.0*(XYangle - 90));
	}
	return -1;
}

float getTrueWindSpeed(float **trueWindVec){
	return sqrt(trueWindVec[0][0]*trueWindVec[0][0] + trueWindVec[1][0]*trueWindVec[1][0]);
}

