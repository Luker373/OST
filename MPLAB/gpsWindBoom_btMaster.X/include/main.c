//#include "serialcomm.h"
#include <serial.h>
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
    
    AD_Init();
    AD_AddPins(AD_A1);
    AD_AddPins(AD_A2);
    INCAP_Init();
    TIMERS_Init();
    
    
    int PotVal = 0;
    int CurrAngle = 0, PrevAngle = 0, FinalAngle = 0;
    
    // x in val[x] is the exponent 10^x-1
    // we add 1 to compensate for the null character
    // so if pot goes up to 1000, x = 4
    // if pot goes up to 1000000, x = 7
    char Val[6];
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
    
    
    char tempOut[200];
    //float trueWindVec[2][1], boatWindVec[2][1], appWindVec[2][1];
//    trueWindVec = malloc(2*sizeof(float*));
//    boatWindVec = malloc(2*sizeof(float*));
//    appWindVec = malloc(2*sizeof(float*));
//    
//    trueWindVec[0] = malloc(sizeof(float));
//    trueWindVec[1] = malloc(sizeof(float));
//    
//    boatWindVec[0] = malloc(sizeof(float));
//    boatWindVec[1] = malloc(sizeof(float));
//    
//    appWindVec[0] = malloc(sizeof(float));
//    appWindVec[1] = malloc(sizeof(float));
    
    
    
    memset(str2, '\0', sizeof(str2));
    strcpy(str2, test);
    rx1_size = 0;
    int i=0, j=0;
    while(1){    
        j++;
     //   if(UpdateDataBuffer(1, 100)){
        //PutChar(2, '!');
        sprintf(tempOut, "Hello World!\r\n");
        printf(tempOut);
        if (j == 100000){
            
            j=0;
          //  GetDataBuffer(1, gpsPacket);
          //  processSentence(gpsPacket);
            //createGNOST(gnost);
            //createGNTST(gntst);
//            for(i = 0; i < strlen(gnost); i++){
//                PutChar(2, gnost[i]);
//            }
//            for(i = 0; i < strlen(gntst); i++){
//                PutChar(2, gntst[i]);
//            }
         //   PutChar(2, '!');
        }
        
        // accumulate average over delay period
        if (delay >= TIMERS_GetMilliSeconds()) {
            degVal += AD_ReadADPin(AD_A2);
            freq += INCAP_getFreq()/1000.000;
            numSamples++;
        }else{
            delay += 50;        
            degree = (((float)((float)degVal/numSamples)) - 1034.486486)/-2.942303732;
            freq = freq/numSamples;
            windSpeed = (freq + .00185)/0.524;

            setWindSpeed(windSpeed);
            setWindDegree(degree);
            
            numSamples = 0;
            degVal = 0;
            freq = 0;
        }
        
        //setBoatWindVec(&boatWindVec);
        //sprintf(tempOut, "heading: %f speed: %f {[%f],[%f]}\r\n", getTrack(), getSpeed(), boatWindVec[0][0], boatWindVec[1][0]);
        sprintf(tempOut, "Hello World!\r\n");
        
        
        
        // read potentiometer value
        // may need to linearize it
        // will check values to see how they
        // correlate to certain angles
        /*
        PotVal = AD_ReadADPin(AD_A1);
        
        //CurrAngle = (0.2072*PotVal)+37.032+2;
        if((CurrAngle >= 130) || (CurrAngle <= 160)){
            // if in ideal boom range for small craft
            // use this linear fit
            CurrAngle = (0.1895*PotVal)+44.865;
            //CurrAngle = (0.1996*PotVal)+40.154;
        } else if(((CurrAngle < 130)&&(CurrAngle >= 100)) 
        || ((CurrAngle > 160)&&(CurrAngle <= 190))){
            // within extended ideal boom range, use this fit
            CurrAngle = (0.2012*PotVal)+39.763;
        } else {
            // outside ideal boom range, use this fit
            CurrAngle = (0.1996*PotVal)+40.154;
        }
        
        // do simple filtering on Angle values
        if(abs(CurrAngle-PrevAngle) >= 1){
            // if the difference is big enough
        // we set the new value to be the value we send out
        // and hold the old value in a separate variable
            FinalAngle = CurrAngle;
            PrevAngle = FinalAngle;
        } else {
            // if the difference in values is too small,
        // we discard the current value
            PrevAngle = CurrAngle;
        }
   
        // copy to gpsLib field for BT packet creating
        setBoomAngle(FinalAngle);
        */
        
    }
}