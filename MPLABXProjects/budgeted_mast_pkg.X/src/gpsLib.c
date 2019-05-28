#include "gpsLib.h"
#include <stdlib.h>
#include <math.h>

#define WINDOW_SIZE 30
#define WINDOW_SUM (WINDOW_SIZE)*(WINDOW_SIZE+1)/2

float longitude=0, latitude=0, alt=0, speed=0;
float freq = 0, windDegree = 0, windSpeed = 0, track = 45;
int boomAngle = 0;
int time[3];
int satellites=0, fix=0;
int i = 0, startup = 1;
char msg[79];
char tempMsg[79];
char printmsg[200];
char temp[30];

int windSupdated=0, windDupdated=0, windSidx=0, windDidx=0, windSsum =0, windDsum =0;
int windSarr[WINDOW_SIZE];
int windDraw[WINDOW_SIZE];
int windDarr[WINDOW_SIZE];


int compassSupdated = 0, compassDupdated = 0, compassSidx = 0, compassDidx = 0, compassSsum = 0, compassDsum = 0, startup_c = 1, j;
int compassSarr[WINDOW_SIZE];
int compassDraw[WINDOW_SIZE];
int compassDarr[WINDOW_SIZE];
float compassDegree;

void processSentence(char *str){
    strcpy(tempMsg, str);
    
    int cs = checkCS(tempMsg);
    
    if(cs == 1){
        char *tok = strtok(str, ",");
        if(!strcmp(tok, "$GNGGA")){
            processGGA(str);
        }
        else if(!strcmp(tok, "$GNGSA")){
            processGSA(str);
        }
        else if(!strcmp(tok, "$GNRMC")){
            processRMC(str);
        }
        else if(!strcmp(tok, "$GNOST")){
            processGNOST(str);
        }
    }
}

// $GNTST, (speed), track, (wind speed), (wind dir), (boom angle), (timestamp), *(checksum) <CR><LF>
void createGNTST(char *str){
        char csNL[5];
        char buffer[10];
        char out[80];
        
        sprintf(out, "$GNTST,%.2f,%.2f,%.2f,%.2f,%d,", getSpeed(), track, getWindSpeed(),getWindDegree(),getBoomAngle());
        if(getHour() < 10)
          strcat(out, "0");
        itoa(buffer, getHour(), 10);
        strcat(out, buffer);
        if(getMinute() < 10)
          strcat(out, "0");
        itoa(buffer, getMinute(), 10);
        strcat(out, buffer);
        
        if(getSecond() < 10)
          strcat(out, "0");
        itoa(buffer, getSecond(), 10);
        strcat(out, buffer);
        
        strcat(out, "*");
        
        strcpy(tempMsg, out);
        
        int cs = calcCS(tempMsg);
        
        if(cs / 16 == 15)
          csNL[0] = 'F';
        else if(cs / 16 == 14)
          csNL[0] = 'E';
        else if(cs / 16 == 13)
          csNL[0] = 'D';
        else if(cs / 16 == 12)
          csNL[0] = 'C';
        else if(cs / 16 == 11)
          csNL[0] = 'B';
        else if(cs / 16 == 10)
          csNL[0] = 'A';
        else
          csNL[0] = cs/16 + 48;
        
        if(cs % 16 == 15)
          csNL[1] = 'F';
        else if(cs % 16 == 14)
          csNL[1] = 'E';
        else if(cs % 16 == 13)
          csNL[1] = 'D';
        else if(cs % 16 == 12)
          csNL[1] = 'C';
        else if(cs % 16 == 11)
          csNL[1] = 'B';
        else if(cs % 16 == 10)
          csNL[1] = 'A';
        else
          csNL[1] = cs%16 + 48;
          
        csNL[2] = '\r';
        csNL[3] = '\n';
        csNL[4] = '\0';
        
        strcat(out, csNL);
        strcpy(str, out);
}

// $GNOST, (filtered), (lat), (long), (wind speed), (wind dir), (speed), (heading), (boom angle), (timestamp), *(checksum) <LF>
void createGNOST(char *str){
        char csNL[5];
        char buffer[10];
        char out[80];
        
        sprintf(out, "$GNOST,%d,%.4f,%.4f,%.2f,%.2f,%.2f,%.2f,%.2f,%.0f,",-1, getLat()/100, getLong()/100, getWindSpeed(),getWindDegree(), getSpeed(),track,getBoomAngle(),getCompassDegree());

//        sprintf(out, "$GNOST,%d,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,", -1, getLat()/100, getLong()/100, getWindSpeed(),getWindDegree(),-1.0,getBoomAngle());
        if(getHour() < 10)
          strcat(out, "0");
        itoa(buffer, getHour(), 10);
        strcat(out, buffer);
        if(getMinute() < 10)
          strcat(out, "0");
        itoa(buffer, getMinute(), 10);
        strcat(out, buffer);
        
        if(getSecond() < 10)
          strcat(out, "0");
        itoa(buffer, getSecond(), 10);
        strcat(out, buffer);
        
        strcat(out, "*");
        
        strcpy(tempMsg, out);
        
        int cs = calcCS(tempMsg);
        
        if(cs / 16 == 15)
          csNL[0] = 'F';
        else if(cs / 16 == 14)
          csNL[0] = 'E';
        else if(cs / 16 == 13)
          csNL[0] = 'D';
        else if(cs / 16 == 12)
          csNL[0] = 'C';
        else if(cs / 16 == 11)
          csNL[0] = 'B';
        else if(cs / 16 == 10)
          csNL[0] = 'A';
        else
          csNL[0] = cs/16 + 48;
        
        if(cs % 16 == 15)
          csNL[1] = 'F';
        else if(cs % 16 == 14)
          csNL[1] = 'E';
        else if(cs % 16 == 13)
          csNL[1] = 'D';
        else if(cs % 16 == 12)
          csNL[1] = 'C';
        else if(cs % 16 == 11)
          csNL[1] = 'B';
        else if(cs % 16 == 10)
          csNL[1] = 'A';
        else
          csNL[1] = cs%16 + 48;
          
        csNL[2] = '\r';
        csNL[3] = '\n';
        csNL[4] = '\0';
        
        strcat(out, csNL);
        strcpy(str, out);
}

int calcCS(char *str){
        str++;
        int tot = 0;
        // add values of all chars between $ and *
        while(*str != '*'){
          tot ^= *str;
          str++;
        }
        return tot;
}

int checkCS(char *str){
        // skip starting $
        str++;
        int tot = 0, ck = 0;
        // add values of all chars between $ and *
        while(*str != '*'){
          tot ^= *str;
          str++;
        }
        // *str is now at *
        str++;
        if(*str == 'F')
          ck += 15*16;
        else if(*str == 'E')
          ck += 14*16;
        else if(*str == 'D')
          ck += 13*16;
        else if(*str == 'C')
          ck += 12*16;
        else if(*str == 'B')
          ck += 11*16;
        else if(*str == 'A')
          ck += 10*16;
        else
          ck += 16*(*str - 48);
          
        str++;
        if(*str == 'F')
          ck += 15;
        else if(*str == 'E')
          ck += 14;
        else if(*str == 'D')
          ck += 13;
        else if(*str == 'C')
          ck += 12;
        else if(*str == 'B')
          ck += 11;
        else if(*str == 'A')
          ck += 10;
        else
          ck += *str - 48;
        
        return (ck == tot);
}

// $GNGGA,225221.00,3658.85898,N,12201.65720,W,2,08,1.43,-16.8,M,-30.6,M,,0000*69
void processGGA(char *str){
	char *tok = strtok(NULL, ",");
	// tok = time of fix taken
    if(tok != NULL){
        int t = atoi(tok);
        if (t < 0 || t > 999999)
            return;
        time[0] = t / 10000;
        time[1] = (t % 10000) / 100;
        time[2] = (t % 100);
    }

	tok = strtok(NULL, ",");
	// tok = latitude
    if(tok != NULL){
      latitude = atof(tok);
    }
        
    tok = strtok(NULL, ",");
	// tok = N or S
	if(tok != NULL && !strcmp(tok, "S"))
          latitude *= -1;

	tok = strtok(NULL, ",");
	// tok = longitude
    if(tok != NULL)
        longitude = atof(tok);

    tok = strtok(NULL, ",");
	// tok = N or S
	if(tok != NULL && !strcmp(tok, "W"))
        longitude *= -1;

	tok = strtok(NULL, ",");
	// tok = fix quality
    if(tok != NULL)
        fix = atoi(tok);

	tok = strtok(NULL, ",");
	// tok = satellites tracked
    if(tok != NULL)
        satellites = atoi(tok);

	tok = strtok(NULL, ",");
	// tok = horizontal dilution of pos

	tok = strtok(NULL, ",");
	// tok = altitude above mean sea level
    if(tok != NULL)
        alt = atof(tok);
}

// $GNOST, (filtered), (lat), (long), (wind speed), (wind dir), (speed), (heading), (boom angle), (timestamp), *(checksum) <LF>
void processGNOST(char *str){
    char *tok = strtok(NULL, ",");
    // tok = filtered stuff
    
    tok = strtok(NULL, ",");
    // tok = lat
    latitude = atof(tok);
            
    tok = strtok(NULL, ",");
    // tok = long
    longitude = atof(tok);
    
    tok = strtok(NULL, ",");
    // tok = wind speed
    windSpeed = atof(tok);
    
    tok = strtok(NULL, ",");
    // tok = wind dir
    windDegree = atof(tok);
    
    tok = strtok(NULL, ",");
    // tok = speed
    speed = atof(tok);
    
    tok = strtok(NULL, ",");
    // tok = heading
    track = atof(tok);
    
    tok = strtok(NULL, ",");
    // tok = boom angle
    
    tok = strtok(NULL, ",");
    if(tok != NULL){
        int t = atoi(tok);
        if (t < 0 || t > 999999)
            return;
        time[0] = t / 10000;
        time[1] = (t % 10000) / 100;
        time[2] = (t % 100);
    }
    
    tok = strtok(NULL, ",");
    // tok = checksum
       
}

void processGSA(char *str){
	char *tok = strtok(NULL, ",");
	// tok = num sentences for full data
	tok = strtok(NULL, ",");
	// tok = sentence #
	tok = strtok(NULL, ",");
	// tok = num satellites in view
    if(tok != NULL)
        satellites = atoi(tok);
}

// $GNRMC,time,Active?,lat,N,long,E,speed(knots),track(degrees),date,mag variation,W*6A
void processRMC(char *str){
    char *tok = strtok(NULL, ",");
    // tok = time
    tok = strtok(NULL, ",");
    // tok = active?
    tok = strtok(NULL, ",");
    // tok = lat
    tok = strtok(NULL, ",");
    // tok = N or S
    tok = strtok(NULL, ",");
    // tok = long
    tok = strtok(NULL, ",");
    // tok = W or E
    tok = strtok(NULL, ",");
    // tok = speed(knots)
    if(tok != NULL)
        speed = atof(tok);
    tok = strtok(NULL, ",");
    // tok = track(degrees)
    if(tok != NULL){
        float temp=0;
        temp = atof(tok);
        if(temp < 360 && temp > 0)
            track = temp;
    }
    
}

void setWindSpeed(float f){
    if (f > 100)
        f = 0;
    f = (int)f;
    windSupdated = 1;
    windSidx = windSidx % WINDOW_SIZE;
    windSsum += (f*1000*WINDOW_SIZE);
    for(i =0; i < WINDOW_SIZE; ++i){
        windSsum -= windSarr[i];
    }
    windSarr[windSidx] = (int)(f*1000);
    windSidx++;
    //windSpeed = f;
}

void setWindDegree(float f){
    windDupdated = 1;
    f += 360;
    f = (int)f;
    int windDold = (windDidx - 1) % WINDOW_SIZE;
    windDidx = windDidx % WINDOW_SIZE;
    windDraw[windDidx] = f;
    if(startup != 1){
        if(f < 410 && windDraw[windDold] > 660)
            f = windDarr[windDold]/10 + (360 - windDraw[windDold]) + f;
        else if(f > 660 && windDraw[windDold] < 410)
            f = windDarr[windDold]/10 - (360 - f + windDraw[windDold]);
        else
            f = windDarr[windDold]/10 - (windDraw[windDold] - f);
    }else{ startup = 0; }    
    windDsum += f*10*WINDOW_SIZE;
    for(i =0; i < WINDOW_SIZE; ++i){
        windDsum -= windDarr[i];
    }
    windDarr[windDidx] = (int)(f*10);
    ++windDidx;
    //windDegree = f;
}

void setBoomAngle(int i){
    boomAngle = i;
}

int getBoomAngle(void){
    return boomAngle;
}

float getTrack(void){
    return track;
}

float getWindSpeed(void){
    if(windSupdated == 0)
        return windSpeed;
    windSupdated = 0;
    windSpeed = (float)(windSsum) / (1000*WINDOW_SUM);
    return windSpeed;
}

float getWindDegree(void){
    if(windDupdated == 0)
        return windDegree;
    windDupdated = 0;
    windDegree = windDsum / (10*WINDOW_SUM);
    windDegree = fmod(windDegree, 360);
    return windDegree;
}

float getLong(void){
	return longitude;
}

float getLat(void){
	return latitude;
}

float getAlt(void){
	return alt;
}

int getHour(void){
	return time[0];
}

int getMinute(void){
	return time[1];
}

int getSecond(void){
	return time[2];
}

float getSpeed(void){
    return speed;
}

void setCompassDegree(float f) {
//    f = (int)f;
//    if (f < 0 || f > 360)
//        return;
//    compassDupdated = 1;
//    int compassDold = (compassDidx - 1) % WINDOW_SIZE;
//    compassDidx = compassDidx % WINDOW_SIZE;
//    compassDraw[compassDidx] = f;
//    if (startup_c != 1) {
//        if (f < 410 && compassDraw[compassDold] > 660)
//            f = compassDarr[compassDold] / 10 + (360 - compassDraw[compassDold]) + f;
//        else if (f > 660 && compassDraw[compassDold] < 410)
//            f = compassDarr[compassDold] / 10 - (360 - f + compassDraw[compassDold]);
//        else
//            f = compassDarr[compassDold] / 10 - (compassDraw[compassDold] - f);
//    } else {
//        startup_c = 0;
//    }
//    compassDsum += f * 10 * WINDOW_SIZE;
//    for (j = 0; j < WINDOW_SIZE; ++j) {
//        compassDsum -= compassDarr[j];
//    }
//    compassDarr[compassDidx] = (int) (f * 10);
//    ++compassDidx;
    compassDegree = f;
}

float getCompassDegree(void) {
    if (compassDupdated == 0)
        return compassDegree;
    compassDupdated = 0;
//    compassDegree = compassDsum / (10 * WINDOW_SUM);
//    compassDegree = fmod(compassDegree, 360);
    return compassDegree;
}