#include "serialcomm.h"
#include "gpsLib.h"
#include <GenericTypeDefs.h>
#include <string.h>
#include <plib.h>
#include <peripheral/i2c.h>
#include <AD.h>
#include <stdio.h>
#include <math.h>
#include <INPUT_CAPTURE.h>

#pragma config FPLLODIV = DIV_1, FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FWDTEN = OFF, FCKSM = CSECME, FPBDIV = DIV_1
#pragma config OSCIOFNC = ON, POSCMOD = XT, FSOSCEN = ON, FNOSC = PRIPLL
#pragma config CP = OFF, BWP = OFF, PWP = OFF

int main(void){
    BOARD_Init();
    
//    AD_Init();
//    AD_AddPins(AD_A2);
//    INCAP_Init();
//    TIMERS_Init();
//    
    float freq = 0, degree = 0, windSpeed = 0;
    unsigned int degVal = 0, numSamples = 0;
    int delay = 100;
    
    char str1[200];
    UINT32 rx1_size=0;
    UINT8 str2[1024];
    UINT32 rx2_size;
    
    char  test[] = {
        "0123456789\r\n"
    };
    char gnost[100];
    char gntst[100];
    char gpsPacket[100];
    memset(str2, '\0', sizeof(str2));
    strcpy(str2, test);
    rx1_size = 0;
    int i=0, j=0;
    while(1){    
        j++;
     //   if(UpdateDataBuffer(1, 100)){
        //PutChar(2, '!');
        if (j == 1000000){
            j=0;
          //  GetDataBuffer(1, gpsPacket);
          //  processSentence(gpsPacket);
            //createGNOST(gnost);
            createGNTST(gntst);
//            for(i = 0; i < strlen(gnost); i++){
//                PutChar(2, gnost[i]);
//            }
            for(i = 0; i < strlen(gntst); i++){
                PutChar(2, gntst[i]);
            }
         //   PutChar(2, '!');
        }
        
//        // accumulate average over delay period
//        if (delay >= TIMERS_GetMilliSeconds()) {
//            degVal += AD_ReadADPin(AD_A2);
//            freq += INCAP_getFreq()/1000.000;
//            numSamples++;
//        }else{
//            delay += 50;        
//            degree = (((float)((float)degVal/numSamples)) - 1034.486486)/-2.942303732;
//            freq = freq/numSamples;
//            windSpeed = (freq + .00185)/0.524;
//
//            setWindSpeed(windSpeed);
//            setWindDegree(degree);
//            
//            numSamples = 0;
//            degVal = 0;
//            freq = 0;
//        }
        
    }
    
}