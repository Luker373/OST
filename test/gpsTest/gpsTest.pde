#include <string.h>
#include <stdio.h>
#include <stdlib.h>
/*
  CUSTOM PACKET(S)
  
  $GNOST, (filtered), (lat), (long), (wind speed), (wind dir), (heading), (boom angle), (timestamp), *(checksum) <LF>
  any value that is -1 is invalid

*/
float longitude=0, latitude=0, alt=0;
int time[3];
int satellites=0, fix=0;
int i = 0;
char msg[79];
char tempMsg[79];
char printmsg[200];
char temp[30];

void setup(){
  Serial1.begin(9600); // GPS module
  Serial.begin(9600); // USB

}

void loop(){
  
  if (Serial1.available()) 
    {
    int rxgps=Serial1.read(); // read byte from gps
    msg[i%79] = rxgps;
    i++;
    if (rxgps==0x0A) // Line Feed detected => end of a sentence
      {
        msg[i] = '\0';
        // Serial.write(msg); 
        processSentence(msg);
        createGNOST(printmsg);
        Serial.write(printmsg);
        i = 0;
      }
    }
}

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
        }
}

// $GNOST, (filtered), (lat), (long), (wind speed), (wind dir), (heading), (boom angle), (timestamp), *(checksum) <LF>
void createGNOST(char *str){
        char csNL[5];
        char buffer[10];
        sprintf(str, "$GNOST,%d,%f,%f,%d,%d,%f,%f,", -1, getLat(), getLong(), -1,-1,-1.0,-1.0);
        if(getHour() < 10)
          strcat(str, "0");
        itoa(getHour(), buffer, 10);
        strcat(str, buffer);
        
        if(getMinute() < 10)
          strcat(str, "0");
        itoa(getMinute(), buffer, 10);
        strcat(str, buffer);
        
        if(getSecond() < 10)
          strcat(str, "0");
        itoa(getSecond(), buffer, 10);
        strcat(str, buffer);
        
        strcat(str, "*");
        
        strcpy(tempMsg, str);
        
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
          
        csNL[2] = '\n';
        csNL[3] = '\0';
        
        strcat(str, csNL);
        //Serial.write(str);
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
