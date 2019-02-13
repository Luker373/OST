#include "serialcomm.h"
#include <GenericTypeDefs.h>
#include <string.h>
#include <plib.h>

#pragma config FPLLODIV = DIV_1, FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FWDTEN = OFF, FCKSM = CSECME, FPBDIV = DIV_1
#pragma config OSCIOFNC = ON, POSCMOD = XT, FSOSCEN = ON, FNOSC = PRIPLL
#pragma config CP = OFF, BWP = OFF, PWP = OFF

int main(void){
    initUART1();
    initUART2();
    UINT8 str1[200];
    UINT32 rx1_size=0;
    UINT8 str2[1024];
    UINT32 rx2_size;
    
    char *p;
    
    UINT8 test[] = "INIT\r\n";
    
    memset(str2, '\0', sizeof(str2));
    strcpy(str2, test);
    rx1_size = 0;
    while(1){
        
       // rx1_size = GetDataBufferUART2(str2, 200);
       // printf("rx1_size: %d\n", rx1_size);
        
       // SendDataBufferUART1(str2, strlen(str2));
       // rx1_size = GetDataBufferUART1(str2,200);
        
        if(UARTReceivedDataIsAvailable(UART2)){
            p = UARTGetDataByte(UART2);
            UARTSendDataByte(UART1, p);
        }
        
        
//        if(UARTReceivedDataIsAvailable(UART1)){
//            rx1_size = GetDataBufferUART1(str1, 1024);
//        }
        
//        rx1_size = GetDataBufferUART1(str1, 1024);
//        if(rx1_size > 0){
//            SendDataBufferUART2(str1, rx1_size);
//        }else{
//            sprintf(str1, "FAILED\n");
//            SendDataBufferUART1(str1, sizeof(str1));
//        }
//        
//        rx2_size = GetDataBufferUART2(str2, 1024);
//        if(rx2_size > 0){
//            SendDataBufferUART1(str1, rx2_size);
//        }else{
//            sprintf(str2, "FAILED\n");
//            SendDataBufferUART2(str2, sizeof(str2));
//        }
        
        
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

