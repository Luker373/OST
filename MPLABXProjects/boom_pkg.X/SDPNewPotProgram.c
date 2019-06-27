/* 
 * File:   SDPNewPotProgram.c
 * Author: SailTrim Team
 *
 * Created on May 4, 2019, 9:25 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "xc.h"
#include "BOARD.h"
#include "AD.h"
#include "serial.h"
#include "timers.h"
#include "serialcomm.h"
#include "ascii.h"
//#include "Oled.h"
//#include "OledDriver.h"

#define MAX_POT_ANGLE 271
#define HALF_POT_RANGE 116
#define SCALE_2_ANGLE 0.242
#define DEADBAND_OFFSET 24

#pragma config FPLLODIV = DIV_1, FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FWDTEN = OFF, FCKSM = CSECME, FPBDIV = DIV_1
#pragma config OSCIOFNC = ON, POSCMOD = XT, FSOSCEN = ON, FNOSC = PRIPLL
#pragma config CP = OFF, BWP = OFF, PWP = OFF

/*
 * 
 */
int main(void) {

    BOARD_Init();
    AD_Init();
    TIMERS_Init();
    OledInit();
    SERIAL_Init();
    
    AD_AddPins(AD_A2);
    
    int PotVal = 0, i = 0, calTime = 8000; //calTime = calibration time in milliseconds
    int CurrAngle = 0;
    char gnostPacket[100];
    char gnost[100];
    
    // x in val[x] is the exponent 10^x-1
    // we add 1 space to compensate for the null character
    // so if analog value goes up to 1000, x = 4
    // if analog goes up to 1000000, x = 7
    char Val[6];
    
    // make section to prompt user to hold boom roughly parallel with boat
    // and then calculate the potentiometer position error (ideally, the pot
    // is placed such that it is in the middle of its analog range when boom
    // is horizontal) for 8 seconds, then subtract it from angle calculation
    
    for(;;){
        
        // clear screen of past stuff
        // makes it white 
        // should make numbers easier to see
        OledClear(1);
        
        // read potentiometer value and place into float variable
        PotVal = AD_ReadADPin(AD_A2);
        
        // if boom angle in first dead band range (based on analog value)
        CurrAngle = MAX_POT_ANGLE-((PotVal*SCALE_2_ANGLE)+DEADBAND_OFFSET)-HALF_POT_RANGE;
        
        // turn variable value into string
        // transmit string through uart 2 on uc32 board
        // send over bluetooth
        
        sprintf(Val, "%d\r\n", CurrAngle);
        for(i = 0; i < strlen(Val); ++i){
            PutChar(2, Val[i]);
            //PutChar(Val[i]);
        }
   
        setBoomAngle(CurrAngle);
        
        if (UpdateDataBuffer(1, 100)){
            GetDataBuffer(1, gnostPacket);
            processSentence(gnostPacket);
            createGNOST(gnost);
            
            for(i = 0; i < strlen(gnost); ++i)
                PutChar(2, gnost[i]);
            for(i=0; i < 100000; ++i);
        }
        
        // print value and update screen to display
        //OledDrawString(Val);
        //OledUpdate();
        
    }
}

// previous code: the pot works well enough such that no filtering is currently needed

/*
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
        */
        /*
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
        */
   
        // check if correct value
        // prints to motor shield terminal
        
       //printf("P=:%.1f\r\n", CurrAngle

