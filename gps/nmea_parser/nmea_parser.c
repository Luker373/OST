#include "nmea_parser.h"

double longitude, latitude, alt;
int time[3];
int satellites, fix;
void processSentence(char *str){
	char *tok = strtok(str, ",");
	if(!strcmp(tok, "$GNGGA")){
		processGGA(str);
        }
	else if(!strcmp(tok, "$GNGSA")){
		processGSA(str);
        }
}

// $GNGGA,225221.00,3658.85898,N,12201.65720,W,2,08,1.43,-16.8,M,-30.6,M,,0000*69
void processGGA(char *str){
	char *tok = strtok(NULL, ",");
	// tok = time of fix taken
	int t = atoi(tok);
	time[0] = t / 1000;
	time[1] = (t % 10000) / 100;
	time[2] = (t % 100);

	tok = strtok(NULL, ",");
	// tok = latitude
	latitude = atof(tok);

        tok = strtok(NULL, ",");
	// tok = N or S
	if(!strcmp(tok, "S"))
          latitude *= -1;

	tok = strtok(NULL, ",");
	// tok = longitude
	longitude = atof(tok);

        tok = strtok(NULL, ",");
	// tok = N or S
	if(!strcmp(tok, "W"))
          longitude *= -1;

	tok = strtok(NULL, ",");
	// tok = fix quality
	fix = atoi(tok);

	tok = strtok(NULL, ",");
	// tok = satellites tracked
	satellites = atoi(tok);

	tok = strtok(NULL, ",");
	// tok = horizontal dilution of pos

	tok = strtok(NULL, ",");
	// tok = altitude above mean sea level
	alt = atof(tok);
}

void processGSA(char *str){
	char *tok = strtok(NULL, ",");
	// tok = num sentences for full data
	tok = strtok(NULL, ",");
	// tok = sentence #
	tok = strtok(NULL, ",");
	// tok = num satellites in view
	satellites = atoi(tok);
}

double getLong(void){
	return longitude;
}

double getLat(void){
	return latitude;
}

double getAlt(void){
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