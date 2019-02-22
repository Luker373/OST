/*
 * File:   main.c
 * Author: Joe
 *
 * Created on February 14, 2019, 5:52 PM
 */

#include "xc.h"
#include <AD.h>
#include <BOARD.h>
#include <Oled.h>
#include <OledDriver.h>
#include <stdio.h>
#include <math.h>
#include <INPUT_CAPTURE.h>

int main(void) {
    BOARD_Init();
    OledInit();
    AD_Init();
    AD_AddPins(AD_A5);
    INCAP_Init();
    
    char str[100] = "startup";
    float freq = 0, degree = 0, windSpeed = 0;
    unsigned int degVal = 0, numSamples = 0;
    int delay = 100;

    TIMERS_Init();

    while (1) {
                       
        // accumulate average over delay period
        while (delay >= TIMERS_GetMilliSeconds()) {
            degVal += AD_ReadADPin(AD_A5);
            freq += INCAP_getFreq()/1000.000;
            numSamples++;
        }
        
        delay += 50;        
        //degVal = degVal/numSamples;
        degree = (((float)((float)degVal/numSamples)) - 1034.486486)/-2.942303732;
        freq = freq/numSamples;
        windSpeed = (freq + .00185)/0.524;
        
        //sprintf(str, "%0.3f Hz\r\n%d\r\n%0.3f\r\n", freq, degVal, degree);
        sprintf(str, "%0.2f Hz\r\n%0.2f mph\r\n%0.2f degrees\r\n", freq, windSpeed, degree);
        numSamples = 0;
        degVal = 0;
        freq = 0;

        OledClear(OLED_COLOR_BLACK);
        OledDrawString(str);
        OledUpdate();


    }
    return 0;
}