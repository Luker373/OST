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
    char str[10] = "";

    while (1) {
        sprintf(str, "%d", INCAP_getFreq());
        OledClear(OLED_COLOR_BLACK);
        OledDrawString(str);
        OledUpdate();

    }
    return 0;
}