/*
 * File:   main.c
 * Author: Joe
 *
 * Created on February 14, 2019, 5:52 PM
 */

#include "xc.h"
#include <BOARD.h>
#include <Oled.h>
#include <OledDriver.h>
#include <stdio.h>
#include <math.h>
#include <INPUT_CAPTURE.h>

int main(void) {
    BOARD_Init();
    OledInit();
    INCAP_Init();
    
    char str[100] = "startup";
    float freq;

    while (1) {
        //printf("%d\r\n", freq);
        freq = INCAP_getFreq()/1000.000;
        //printf("%e\n", a);
        sprintf(str, "%0.3f Hz\n", freq);
        OledClear(OLED_COLOR_BLACK);
        OledDrawString(str);
        OledUpdate();

    }
    return 0;
}