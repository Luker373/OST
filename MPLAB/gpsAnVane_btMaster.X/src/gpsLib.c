#include "gpsLib.h"
#include <stdlib.h>

float longitude=0, latitude=0, alt=0, speed=0;
float freq = 0, windDegree = 0, windSpeed = 0;
int time[3];
int satellites=0, fix=0;
int i = 0;
char msg[79];
char tempMsg[79];
char printmsg[200];
char temp[30];


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
    }
}

// $GNTST, (speed), (wind speed), (wind dir), (heading), (boom angle), (timestamp), *(checksum) <LF>
void createGNTST(char *str){
        char csNL[5];
        char buffer[10];
        char out[80];
        
        sprintf(out, "$GNTST,%.2f,%.2f,%.2f,%.2f,%.2f,", getSpeed(), getWindSpeed(),getWindDegree(),-1.0,-1.0);
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

// $GNOST, (filtered), (lat), (long), (wind speed), (wind dir), (heading), (boom angle), (timestamp), *(checksum) <LF>
void createGNOST(char *str){
        char csNL[5];
        char buffer[10];
        char out[80];
        
        sprintf(out, "$GNOST,%d,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,", -1, getLat()/100, getLong()/100, getWindSpeed(),getWindDegree(),-1.0,-1.0);
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
}

void setWindSpeed(float f){
    windSpeed = f;
}

void setWindDegree(float f){
    windDegree = f;
}

float getWindSpeed(void){
    return windSpeed;
}

float getWindDegree(void){
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