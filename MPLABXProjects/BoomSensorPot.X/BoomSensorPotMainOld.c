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
#include "Oled.h"
#include "OledDriver.h"

/*
 * 
 */
int main(void) {

    BOARD_Init();
    AD_Init();
    OledInit();
    
    AD_AddPins(AD_A1);
    
    int PotVal = 0;
    int Actual = 0;
    
    // x in val[x] is the exponent 10^x-1
    // we add 1 to compensate for the null character
    // so if pot goes up to 1000, x = 4
    // if pot goes up to 1000000, x = 7
    char Val[6];
    
    for(;;){
        
        // clear screen of past stuff
        // makes it white 
        // should make numbers easier to see
        OledClear(1);
        
        // read potentiometer value
        // may need to linearize it
        // will check values to see how they
        // correlate to certain angles
        PotVal = AD_ReadADPin(AD_A1);
        Actual = PotVal-150; //*(0.2571429);
        
        // relate pot value to angle
        
        // turn value into string
        sprintf(Val, "%d\n", Actual);
        
        // print value and update screen to display
        OledDrawString(Val);
        OledUpdate();
        
        // check if correct value
        // prints to motor shield terminal
        printf("%d    \n", Actual);
        
    }
    // could use
}

