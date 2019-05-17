/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _GPSLIB_H    /* Guard against multiple inclusion */
#define _GPSLIB_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
  CUSTOM PACKET(S)
  
  $GNOST,(filtered),(lat),(long),(wind speed),(wind dir),(heading),(boom angle),(timestamp),*(checksum) <LF>
  
  filtered   : is the data processed (1) or raw (0)
  lat        : latitude accurate to 2 decimal places
  long       : longitude accurate to 2 decimal places
  wind speed : wind speed in knots likely accurate to 2 decimal places
  wind dir   : wind dir in degrees likely accurate to 2 decimal places
  heading    : heading in degrees likely accurate to 0 decimal places
  boom angle : angle of the boom in degrees likely accurate to 0 decimal places
  timestamp  : hhmmss
  checksum   : XOR of all bytes between $ and *
  <CR>       : Carriage return
  <LF>       : line feed (newline)
  
  any value that is -1 is invalid
  each character is 1 byte

*/

void processSentence(char *str);
void createGNOST(char *str);
void createGNTST(char *str);
int calcCS(char *str);
int checkCS(char *str);
void processGGA(char *str);
void processGSA(char *str);
void processRMC(char *str);
void processGNOST(char *str);
void setWindSpeed(float f);
void setWindDegree(float f);
float getWindSpeed(void);
float getWindDegree(void);
float getLong(void);
float getLat(void);
float getAlt(void);
float getSpeed(void);
int getHour(void);
int getMinute(void);
int getSecond(void);


    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* GPSLIB_H */

/* *****************************************************************************
 End of File
 */
