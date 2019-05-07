#include "serialcomm.h"
#include <GenericTypeDefs.h>
#include <plib.h>
#include <stdio.h>
#include <string.h>
#include "serial.h"

static char str1[200];
static int idx1=0;
static char str2[200];
static int idx2=0;

static int pktUpdated=0;
static int imuUpdated=0;
static char imuLast[50];
static char pktLast[100];

int isPacketNew(){
    return pktUpdated;
}

int isImuNew(){
    return imuUpdated;
}

void setPacketNew(int i){
    pktUpdated = i;
}

void setImuNew(int i){
    imuUpdated = i;
}

void getPacket(char *buffer){
    strcpy(buffer, pktLast);
}
void setPacket(char *buffer){
    strcpy(pktLast, buffer);
}
void getImu(char *buffer){
    strcpy(buffer, imuLast);
}
void setImu(char *buffer){
    strcpy(imuLast, buffer);
}

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
        
        if (character == '\n'){
            if(uart == 1){
                str1[idx1] = '\n';
                idx1++;
                str1[idx1] = '\0';
                idx1 = 0;
                num_char+=2;
                
                return 1;
            }
            if(uart == 2){
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


/* *****************************************************************************
 End of File
 */
