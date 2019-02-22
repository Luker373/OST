/*
 * File:   vaneDirection.c
 * Author: Joe
 *
 * Created on February 19, 2019, 9:54 AM
 */

#include "xc.h"
#include <BOARD.h>
#include <AD.h>
#include <Oled.h>
#include <OledDriver.h>
#include <stdio.h>
#include <math.h>

int main(void) {
    BOARD_Init();
    AD_Init();
    AD_AddPins(AD_A5);
    OledInit();

    unsigned int degVal = 0, numSamples = 0;
    int delay = 100;
    char str[10] = "startup";

    TIMERS_Init();

    //   an initial message on the board
    OledDrawString("Hello\nWorldI'm\nWorking!\n");
    OledUpdate();
    OledClear(OLED_COLOR_BLACK);

    while (1) {
        
        // accumulate average over delay period
        while (delay >= TIMERS_GetMilliSeconds()) {
            degVal += AD_ReadADPin(AD_A5);
            numSamples++;
        }
        delay += 100;        
        degVal = degVal/numSamples;
        
        sprintf(str, "%d\r\n", degVal);
        printf("%d\r\n", degVal);  
        
        numSamples = 0;
        degVal = 0;

        OledClear(OLED_COLOR_BLACK);
        OledDrawString(str);
        OledUpdate();

    }

    return 0;
}

