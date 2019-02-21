#include "serialcomm.h"
#include <GenericTypeDefs.h>
#include <plib.h>
#include <stdio.h>
#include <string.h>
#include <serial.h>

static char str1[200];
static int idx1=0;
static char str2[200];
static int idx2=0;


// *****************************************************************************
// void GetDataBuffer(int uart, char *buffer)
// *****************************************************************************
void GetDataBuffer(int uart, char *buffer){
    if (uart == 1){
        strcpy(buffer, str1);
    }
    if (uart == 2){
        strcpy(buffer, str2);
    }
}

// *****************************************************************************
// int UpdateDataBuffer(int uart, int max_size)
// *****************************************************************************
int UpdateDataBuffer(int uart, int max_size)
{
    int num_char;
    num_char = 0;

    while(!IsReceiveEmpty(uart) && num_char < max_size)
    {
        char character;
        character = GetChar(uart);

        if(character == '\r'){
            if(uart == 1){
                str1[idx1] = '\r';
                idx1++;
                str1[idx1] = '\n';
                idx1++;
                str1[idx1] = '\0';
                idx1 = 0;
                num_char+=2;
                return 1;
            }
            if(uart == 2){
                str2[idx2] = '\r';
                idx2++;
                str2[idx2] = '\n';
                idx2++;
                str2[idx2] = '\0';
                idx2 = 0;
                num_char+=2;
                return 1;
            }
        }
        if (character == '\n'){
            if(uart == 1){
                str1[idx1] = '\r';
                idx1++;
                str1[idx1] = '\n';
                idx1++;
                str1[idx1] = '\0';
                idx1 = 0;
                num_char+=2;
                return 1;
            }
            if(uart == 2){
                str2[idx2] = '\r';
                idx2++;
                str2[idx2] = '\n';
                idx2++;
                str2[idx2] = '\0';
                idx2 = 0;
                num_char+=2;
                return 1;
            }
        }
        if(uart == 1){
            str1[idx1] = character;
            idx1++;
            num_char++;
        }
        if(uart == 2){
            str2[idx2] = character;
            idx2++;
            num_char++;
        }
        
    }
    return 0;
}



//// *****************************************************************************
//// void UARTTxBuffer(char *buffer, UINT32 size)
//// *****************************************************************************
//void SendDataBufferUART2(const char *buffer, UINT32 size){
//    while(size)
//    {
//        while(!UARTTransmitterIsReady(UART2));
//
//        UARTSendDataByte(UART2, *buffer);
//
//        buffer++;
//        size--;
//    }
//
//    while(!UARTTransmissionHasCompleted(UART2));
//}
//// *****************************************************************************
//// UINT32 GetDataBuffer(char *buffer, UINT32 max_size)
//// *****************************************************************************
//int GetDataBufferUART2(char *buffer, int max_size)
//{
//    int num_char;
//
//    num_char = 0;
//
//    while(num_char < max_size)
//    {
//        char character;
//
//        if(!UARTReceivedDataIsAvailable(UART2))
//            continue;
//
//        character = UARTGetDataByte(UART2);
//
//        if(character == '\r' || character == '\n'){
//            *buffer = '\r';
//            buffer++;
//            *buffer = '\n';
//            buffer++;
//            num_char += 2;
//            break;
//        }
//
//        *buffer = character;
//
//        buffer++;
//        num_char++;
//    }
//    *buffer = '\0';
//    return num_char;
//}


/* *****************************************************************************
 End of File
 */
