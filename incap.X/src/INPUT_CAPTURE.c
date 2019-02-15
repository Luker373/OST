/*
 * File:   INPUT_CAPTURE.c
 * Author: Joe
 *
 * Created on February 11, 2019, 1:50 PM
 */

/*
 * NOTE: Given the limited number of timers on board this module is incompatible with PWM
 */


#include "BOARD.h"
#include <xc.h>
#include <plib.h>
#include <INPUT_CAPTURE.h>
#include <math.h>

static unsigned int prevTime = 0, curTime = 0, elapsedTime = 1, secondEntry = 0, freq;

void __ISR(_INPUT_CAPTURE_4_VECTOR, ipl1auto) InputCapture4Handler(void) {
    INTClearFlag(INT_IC4);
    // IC4BUF contains the timer value when the triggered edge occurred.
    if (secondEntry) {
        elapsedTime = IC4BUF - prevTime;
        secondEntry = 0;
    } else {
        prevTime = IC4BUF;
        secondEntry = 1;
    }
}
//
//void __ISR(_INPUT_CAPTURE_1_VECTOR, ipl1auto) InputCapture1Handler(void) {
//    INTClearFlag(INT_IC1);
//    // IC4BUF contains the timer value when the triggered edge occurred.
//    if (secondEntry) {
//        elapsedTime = IC1BUF - prevTime;
//        secondEntry = 0;
//        printf("%d", elapsedTime);
//    } else {
//        prevTime = IC1BUF;
//        secondEntry = 1;
//    }
//
//
//}

/**
 * @function    INCAP_Init(void)
 * @brief       This function initializes the module for use. Initialization is 
 *              done by opening and configuring timer 2, opening and configuring the input capture
 *              peripheral, and setting up the interrupt.
 * @return      SUCCESS or ERROR (as defined in BOARD.h)
 */
char INCAP_Init(void) {
    //OpenTimer2(T2_ON | T2_PS_1_64, 0xFFFF);
    //OpenTimer2(T2_ON | T2_PS_1_256, 0xFFFF);
    OpenTimer23(T23_ON | T23_SOURCE_INT | T23_PS_1_256 | T23_32BIT_MODE_ON, 0xFFFFFFFF);
    OpenCapture4(IC_EVERY_FALL_EDGE | IC_TIMER2_SRC | IC_CAP_32BIT| IC_ON);
    //OpenCapture1(IC_EVERY_4_RISE_EDGE | IC_INT_1CAPTURE | IC_CAP_32BIT | IC_FEDGE_RISE | IC_ON);
    INTClearFlag(INT_IC4);
    INTSetVectorPriority(INT_INPUT_CAPTURE_4_VECTOR, 1);
    INTSetVectorSubPriority(INT_INPUT_CAPTURE_4_VECTOR, 1);
    INTEnable(INT_IC4, INT_ENABLED);
    /*******************************************************/

    TRISDbits.TRISD11 = 1; //pin 35 IC4
    return 1;
}

/*
 * Uses a 32 bit timer(2+3), prescaled to run at 156,250 Hz, PR4 rollover = 27487 sec = 7.6 hours 
 */
//char INCAP_Init(void) {
//    OpenTimer23(T23_ON | T23_SOURCE_INT | T23_PS_1_256 | T23_32BIT_MODE_ON, 0xFFFF);
//    OpenCapture1(IC_EVERY_4_RISE_EDGE | IC_INT_1CAPTURE | IC_CAP_32BIT | IC_FEDGE_RISE | IC_ON);
//    INTEnable(INT_IC1, INT_ENABLED);
//    INTSetVectorPriority(INT_INPUT_CAPTURE_1_VECTOR, INT_PRIORITY_LEVEL_2);
//    INTSetVectorSubPriority(INT_INPUT_CAPTURE_1_VECTOR, INT_SUB_PRIORITY_LEVEL_0);
//    
//    //INTEnable(INT_IC1, INT_ENABLED);
//    
//    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
//    INTEnableInterrupts();
//    
//    TRISDbits.TRISD8 = 1; //pin 2, IC1, portRD8
//    return 1;
//}


/**
 * @function    INCAP_getFreq(void)
 * @brief       Prescaled imer frequency scaled by 1000 for uint math resolution
 * @return      frequency*1000
 */
unsigned int INCAP_getFreq(void) {
    //freq = (float)(156250.0001/(float)elapsedTime); //float arithmetic no work?
    freq = 156250000/elapsedTime;  
    //printf("%f \r\n", freq);
    return freq;

}


