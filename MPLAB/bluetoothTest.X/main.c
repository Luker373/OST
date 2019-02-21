#include "serialcomm.h"
#include "gpsLib.h"
#include <GenericTypeDefs.h>
#include <string.h>
#include <plib.h>

#pragma config FPLLODIV = DIV_1, FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FWDTEN = OFF, FCKSM = CSECME, FPBDIV = DIV_1
#pragma config OSCIOFNC = ON, POSCMOD = XT, FSOSCEN = ON, FNOSC = PRIPLL
#pragma config CP = OFF, BWP = OFF, PWP = OFF

int main(void){
    BOARD_Init();
    char str1[200];
    UINT32 rx1_size=0;
    UINT8 str2[1024];
    UINT32 rx2_size;
    
    char  test[] = {
        "0123456789\r\n"
    };
    char gnost[100];
    char gntst[100];
    char gpsPacket[100];
    memset(str2, '\0', sizeof(str2));
    strcpy(str2, test);
    rx1_size = 0;
    int i=0, j=0;
    while(1){    

        if(UpdateDataBuffer(1, 100)){
            GetDataBuffer(1, gpsPacket);
            processSentence(gpsPacket);
            createGNOST(gnost);
            createGNTST(gntst);
            for(i = 0; i < strlen(gnost); i++){
                PutChar(2, gnost[i]);
            }
//            for(i = 0; i < strlen(gntst); i++){
//                PutChar(2, gntst[i]);
//            }
        }
//            
//        if(j == 1234560){
//            //createGNOST(printmsg);
//            for(i = 0; i < strlen(gpsPacket); i++){
//                PutChar(2, gpsPacket[i]);
//            }
//            j =0;
//        }
//        j++;
      //  str1[i%79] = UARTGetDataByte(UART2); //read byte from GPS
//        char p = UARTGetDataByte(UART2);
//        str1[i%79] = p;
//        UARTSendDataByte(UART1, str1[i%79]);
        //i++;
//        if (p==0x0A) // Line Feed detected => end of a sentence
//          {
//            str1[i%79] = '\0';
//            // Serial.write(msg); 
////            processSentence(msg);
////            createGNOST(printmsg);
//            for(j=0; j <= i; j++){
//                UARTSendDataByte(UART1, str1[j%79]);
//            }
//            //SendDataBufferUART2(str1, strlen(str1));
//            i = 0;
//          }
//        else
//          {
//            SendDataBufferUART2(test, strlen(test));
//          }
    }
    
}

