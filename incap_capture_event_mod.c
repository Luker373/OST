#include <plib.h>
#include <BOARD.h>
#include <Oled.h>
#include <stdio.h>
//#include <timer.h>


// Configuration Bit settings
// SYSCLK = 80 MHz (8MHz Crystal / FPLLIDIV * FPLLMUL / FPLLODIV)
// PBCLK = 10 MHz (SYSCLK / FPBDIV)
// Primary Osc w/PLL (XT+,HS+,EC+PLL)
// WDT OFF
// Other options are don't care
#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_8
//#define SYS_FREQ (80000000L)


// from Luke
//#pragma config FPLLODIV = DIV_1, FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FWDTEN = OFF, FCKSM = CSECME, FPBDIV = DIV_1

#define SYS_FREQ (80000000L)

// this value can be used to change rollover count
#define PERIOD  0xFFFFFFFF // Timer period of ~ 4 billion (max period = 30.6 hrs?)


unsigned int CaptureTime, elapsedTime; // Used to store the captured timer value
unsigned int PrevCapTime = 0;
char str[20] = "startup";

int main(void) {
    BOARD_Init();
    OledInit();

    SYSTEMConfig(SYS_FREQ, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);


    //PPSInput(4,IC1, RPD8); // Use pin RD8 for input capture //////////////////
    //PPSInput(3, IC1, RD8);
    //PPSInput(IN_FN_PPS_ICx, 1);
    //PPSInput(3, IC1, RD8);

    //TRISDbits.TRISD8 = 1;   // UNECESSARY? Sets RD8 as input
    //PPSInput(4,IC1, RPD8); // FAIL Use pin RD8 for input capture/

    // Setup Timer 23 (timer 2 + timer 3, 32bit time)
    
    // Use PBCLK as source, FPB/256, Timer running at (???10E6???)/256 = 39KHz
    // use to determine PBClock?
    // #define F_PB (BOARD_GetPBClock())
    
    OpenTimer23(T23_ON | T23_SOURCE_INT | T23_PS_1_256 | T23_32BIT_MODE_ON, PERIOD);

    // Enable Input Capture Module 1
    // - Capture every falling edge
    // - Interrupt on first capture
    // - Use 32 bit timer 23 
    // - Capture falling edge first
    //OpenCapture1(IC_EVERY_FALL_EDGE | IC_INT_1CAPTURE | IC_CAP_32BIT | IC_FEDGE_FALL | IC_ON);

    //OpenCapture1(IC_EVERY_16_RISE_EDGE | IC_INT_1CAPTURE | IC_CAP_32BIT | IC_FEDGE_RISE | IC_ON);

    OpenCapture1(IC_EVERY_4_RISE_EDGE | IC_INT_1CAPTURE | IC_CAP_32BIT | IC_FEDGE_RISE | IC_ON);

    // Set up the input capture 1 interrupt with a priority of 2, subpriority of 0
    INTEnable(INT_IC1, INT_ENABLED);
    INTSetVectorPriority(INT_INPUT_CAPTURE_1_VECTOR, INT_PRIORITY_LEVEL_2);
    INTSetVectorSubPriority(INT_INPUT_CAPTURE_1_VECTOR, INT_SUB_PRIORITY_LEVEL_0);

    // Enable multi-vector interrupts
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
    INTEnableInterrupts();

    while (1) {
        // Wait for input capture interrupt
    }

    // Not executed
    CloseCapture1();
    CloseTimer23();

    return 0;
}

// Configure the input capture interrupt handler

void __ISR(_INPUT_CAPTURE_1_VECTOR, ipl2) InputCapture_Handler(void) {

    // Clear the interrupt flag
    INTClearFlag(INT_IC1);

    // Wait for capture data to be ready
    while (!mIC1CaptureReady());

    // Store the timer value of the capture event into CaptureTime variable
    // Calculate elapsed time
    CaptureTime = mIC1ReadCapture();
    //elapsedTime = CaptureTime - PrevCapTime;    
    //elapsedTime = (CaptureTime - PrevCapTime)/16;    
    elapsedTime = (CaptureTime - PrevCapTime) / 4;

    // Draw elapsed time to Oled
    sprintf(str, "%d", elapsedTime);
    OledClear(OLED_COLOR_BLACK);
    OledDrawString(str);
    OledUpdate();
    //printf("%d\n", elapsedTime);

    PrevCapTime = CaptureTime;

}







