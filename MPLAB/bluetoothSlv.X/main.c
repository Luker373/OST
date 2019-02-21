#include "serialcomm.h"
#include "serial.h"
#include "BOARD.h"
#include <GenericTypeDefs.h>
#include <string.h>
#include <plib.h>
#include <stdio.h>

#pragma config FPLLODIV = DIV_1, FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FWDTEN = OFF, FCKSM = CSECME, FPBDIV = DIV_1
#pragma config OSCIOFNC = ON, POSCMOD = XT, FSOSCEN = ON, FNOSC = PRIPLL
#pragma config CP = OFF, BWP = OFF, PWP = OFF

// DO NOT USE BOOTLOADER.LD IF NOT USING THE DEBUGGER 

int main(void){
    BOARD_Init();  // UART1 using serial.c
    
    char str2[1024];
    int rx2_size;
    int rx1_size=0;
    int i;
    
    char test[] = "TEST\r\n\0";
    char no[] = "no\r\n\0";
    char c = 43;
    while(1){
        char str1[200];
        
//        if(!IsReceiveEmpty(2)){
//            PutChar(1, GetChar(2));
//        }
        
        if(UpdateDataBuffer(2, 100)){
            GetDataBuffer(2, str1);
            for(i=0; i < strlen(str1); i++)
                PutChar(1, str1[i]);
        }

        
        
//        rx1_size = GetDataBufferUART2(rxgps, 1); //read byte from GPS
//        msg[i%79] = rxgps;
//        i++;
//        if (rxgps==0x0A) // Line Feed detected => end of a sentence
//          {
//            msg[i] = '\0';
//            // Serial.write(msg); 
//            processSentence(msg);
//            createGNOST(printmsg);
//            SendDataBufferUART1(printmsg, sizeof(printmsg));
//            i = 0;
//          }
    }
    
}



