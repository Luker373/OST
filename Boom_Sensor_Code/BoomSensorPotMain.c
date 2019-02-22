

/* 
 * File:   BoomSensorPotMain.c
 * Author: RARogers
 *
 * Created on January 17, 2019, 5:12 PM
 */

#include "xc.h"
#include <stdio.h>
#include <stdlib.h>
#include "BOARD.h" // lets us interface with uno32 and io shield
#include "AD.h" // activates analog pins, enables readign and writing
#include "serial.h"
#include "ascii.h"
//#include "Oled.h"
//#include "OledDriver.h"

/*
 * 
 */
int main(void) {

    BOARD_Init();
    AD_Init();
    //ledInit();
    
    AD_AddPins(AD_A1);
    
    int PotVal = 0;
    int CurrAngle = 0, PrevAngle = 0, FinalAngle = 0;
    
    // x in val[x] is the exponent 10^x-1
    // we add 1 to compensate for the null character
    // so if pot goes up to 1000, x = 4
    // if pot goes up to 1000000, x = 7
    char Val[6];
    
    for(;;){
        
        // clear screen of past stuff
        // makes it white 
        // should make numbers easier to see
        //OledClear(1);
        
        // read potentiometer value
        // may need to linearize it
        // will check values to see how they
        // correlate to certain angles
        PotVal = AD_ReadADPin(AD_A1);
        
        //CurrAngle = (0.2072*PotVal)+37.032+2;
        if((CurrAngle >= 130) || (CurrAngle <= 160)){
            // if in ideal boom range for small craft
            // use this linear fit
            CurrAngle = (0.1895*Analog)+44.865;
            //CurrAngle = (0.1996*PotVal)+40.154;
        } else if(((CurrAngle < 130)&&(CurrAngle >= 100)) 
        || ((CurrAngle > 160)&&(CurrAngle <= 190))){
            // within extended ideal boom range, use this fit
            CurrAngle = (0.2012*Analog)+39.763;
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
   
        // check if correct value
        // prints to motor shield terminal
        printf("%d    \n", FinalAngle);
        
        // turn value into string
        //sprintf(Val, "%d\n", Actual);
        
        // print value and update screen to display
        //OledDrawString(Val);
        //OledUpdate();
        
    }
    // could use
}

