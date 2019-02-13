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
    UINT8 str2[200];
    UINT32 rx2_size=0;
    
    UINT8 test[] = "AT\r\n";
    UINT8 test2[] = "GET GOT\n";
    
    memset(str1, '\0', sizeof(str1));
    memset(str2, '\0', sizeof(str2));
    rx1_size = 0;
    rx2_size = 0;
    
    // SLAVE ADDR: 98d3:81:fd4257
    
    while(1){
        
        if(rx1_size > 0){
            SendDataBufferUART2(str1, rx1_size);
            SendDataBufferUART1(str1, rx1_size);
            rx1_size = 0;
        }
        //SendDataBufferUART2(test, sizeof(test));
        
        if(UARTReceivedDataIsAvailable(UART2)){
            rx2_size = GetDataBufferUART2(str2, 200);
        }
        
        if(UARTReceivedDataIsAvailable(UART1)){
            rx1_size = GetDataBufferUART1(str1, 200);
        }
        
        if(rx2_size > 0){
            SendDataBufferUART1(str2, rx2_size);
            rx2_size = 0;
        }
        
        
        
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

