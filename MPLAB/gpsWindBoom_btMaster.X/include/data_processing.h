#ifndef _DATA_PROCESSING_H    /* Guard against multiple inclusion */
#define _DATA_PROCESSING_H

#include "gpsLib.h"
#include <math.h>

void setBoatWindVec(float **boatWindVec);

void setAppWindVec(float **appWindVec);

void setTrueWindVec(float **trueWindVec, float **boatWindVec, float **appWindVec);

float getTrueWindHeading(float **trueWindVec, float **boatWindVec, float **appWindVec);

float getTrueWindSpeed(float **trueWindVec);

#endif