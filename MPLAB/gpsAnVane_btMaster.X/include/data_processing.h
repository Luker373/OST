#ifndef _DATA_PROCESSING_H    /* Guard against multiple inclusion */
#define _DATA_PROCESSING_H

#include "gpsLib.h"
#include <math.h>

void setBoatWindVec(float boatWindVec[2][1]);

void setAppWindVec(float appWindVec[2][1]);

void setTrueWindVec(float trueWindVec[2][1], float boatWindVec[2][1], float appWindVec[2][1]);

float getAppWindHeading(void);

float getTrueWindHeading(void);

float getTrueWindSpeed(void);

#endif