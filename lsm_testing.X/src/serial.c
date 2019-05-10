
/*
 * File:   uart.c
 * Author: mdunne
 * Modified by: lhartlag
 *
 * Created on November 10, 2011, 8:42 AM
 * Modified on February 2, 2019
 */

#include <xc.h>
#include "serial.h"

#include "BOARD.h"
#include <peripheral/uart.h>
#include <stdint.h>
#include <plib.h>
//#include <stdlib.h>



/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/

#define F_PB (BOARD_GetPBClock())
#define QUEUESIZE 512

/*******************************************************************************
 * PRIVATE DATATYPES                                                           *
 ******************************************************************************/
typedef struct CircBuffer {
    unsigned char buffer[QUEUESIZE];
    int head;
    int tail;
    unsigned int size;
    unsigned char overflowCount;
} CircBuffer;
typedef struct CircBuffer* CBRef;


/*******************************************************************************
 * PRIVATE FUNCTIONS PROTOTYPES                                                *
 ******************************************************************************/
void newCircBuffer(CBRef cB);
void freeCircBuffer(CBRef* cB);
unsigned int getLength(CBRef cB);
int readHead(CBRef cB);
int readTail(CBRef cB);
unsigned char peak(CBRef cB);
unsigned char readFront(CBRef cB);
unsigned char writeBack(CBRef cB, unsigned char data);

/*******************************************************************************
 * PRIVATE VARIABLES                                                           *
 ******************************************************************************/
struct CircBuffer outgoingUart1;
CBRef transmitBuffer1;
struct CircBuffer incomingUart1;
CBRef receiveBuffer1;
static uint8_t AddingToTransmit1 = FALSE;
static uint8_t GettingFromReceive1 = FALSE;
static uint8_t TransmitCollisionOccured1 = FALSE;
static uint8_t ReceiveCollisionOccured1 = FALSE;

struct CircBuffer outgoingUart2;
CBRef transmitBuffer2;
struct CircBuffer incomingUart2;
CBRef receiveBuffer2;
static uint8_t AddingToTransmit2 = FALSE;
static uint8_t GettingFromReceive2 = FALSE;
static uint8_t TransmitCollisionOccured2 = FALSE;
static uint8_t ReceiveCollisionOccured2 = FALSE;


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

int getLen(void){
    return getLength(transmitBuffer2);
}


/**
 * @Function SERIAL_Init(void)
 * @param none
 * @return none
 * @brief  Initializes the UART subsystem to 115200 and sets up the circular buffer
 * @author Max Dunne, 2011.11.10 */

void SERIAL_Init(void)
{
    transmitBuffer1 = (struct CircBuffer*) &outgoingUart1; //set up buffer for receive
    newCircBuffer(transmitBuffer1);

    receiveBuffer1 = (struct CircBuffer*) &incomingUart1; //set up buffer for transmit
    newCircBuffer(receiveBuffer1);

    UARTConfigure(UART1, 0x00);
    UARTSetDataRate(UART1, F_PB, 9600);
    UARTSetFifoMode(UART1, UART_INTERRUPT_ON_RX_NOT_EMPTY | UART_INTERRUPT_ON_RX_NOT_EMPTY);

    INTSetVectorPriority(INT_UART_1_VECTOR, INT_PRIORITY_LEVEL_4); //set the interrupt priority

    UARTEnable(UART1, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_TX | UART_RX));
    INTEnable(INT_U1RX, INT_ENABLED);
    INTEnable(INT_U1TX, INT_ENABLED);
    
    transmitBuffer2 = (struct CircBuffer*) &outgoingUart2; //set up buffer for receive
    newCircBuffer(transmitBuffer2);

    receiveBuffer2 = (struct CircBuffer*) &incomingUart2; //set up buffer for transmit
    newCircBuffer(receiveBuffer2);

    UARTConfigure(UART2, 0x00);
    UARTSetDataRate(UART2, F_PB, 9600);
    UARTSetFifoMode(UART2, UART_INTERRUPT_ON_RX_NOT_EMPTY | UART_INTERRUPT_ON_RX_NOT_EMPTY);

    INTSetVectorPriority(INT_UART_2_VECTOR, INT_PRIORITY_LEVEL_4); //set the interrupt priority

    UARTEnable(UART2, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_TX | UART_RX));
    INTEnable(INT_U2RX, INT_ENABLED);
    INTEnable(INT_U2TX, INT_ENABLED);
    
}

/**
 * @Function PutChar(char ch)
 * @param ch - the char to be sent out the serial port
 * @return None.
 * @brief  adds char to the end of the circular buffer and forces the interrupt flag 
 * high if nothing is currently transmitting
 * @author Max Dunne, 2011.11.10 */
void PutChar(int uart, char ch)
{
    if(uart == 1){
        if (getLength(transmitBuffer1) != QUEUESIZE) {
            AddingToTransmit1 = TRUE;
            writeBack(transmitBuffer1, ch);
            AddingToTransmit1 = FALSE;
            if (U1STAbits.TRMT) {
                INTSetFlag(INT_U1TX);
            }
            //re-enter the interrupt if we removed a character while getting another one
            if (TransmitCollisionOccured1) {
                INTSetFlag(INT_U1TX);
                TransmitCollisionOccured1 = FALSE;
            }
        }
    }
    if(uart == 2){
        if (getLength(transmitBuffer2) != QUEUESIZE) {
            AddingToTransmit2 = TRUE;
            writeBack(transmitBuffer2, ch);
            AddingToTransmit2 = FALSE;
            if (U2STAbits.TRMT) {
                INTSetFlag(INT_U2TX);
            }
            //re-enter the interrupt if we removed a character while getting another one
            if (TransmitCollisionOccured2) {
                INTSetFlag(INT_U2TX);
                TransmitCollisionOccured2 = FALSE;
            }
        }
    }
}

/**
 * @Function GetChar(void)
 * @param None.
 * @return ch - char from the serial port
 * @brief  reads first character from buffer or returns 0 if no chars available
 * @author Max Dunne, 2011.11.10 */
char GetChar(int uart)
{
    char ch;
    if(uart == 1){
        if (getLength(receiveBuffer1) == 0) {
            ch = 0;
        } else {
            GettingFromReceive1 = TRUE;
            ch = readFront(receiveBuffer1);
            GettingFromReceive1 = FALSE;
        }
        //re-enter the interrupt if we added a character while transmitting another one
        if (ReceiveCollisionOccured1) {
            INTSetFlag(INT_U1RX);
            ReceiveCollisionOccured1 = FALSE;
        }
    }
    if(uart == 2){
        if (getLength(receiveBuffer2) == 0) {
            ch = 0;
        } else {
            GettingFromReceive2 = TRUE;
            ch = readFront(receiveBuffer2);
            GettingFromReceive2 = FALSE;
        }
        //re-enter the interrupt if we added a character while transmitting another one
        if (ReceiveCollisionOccured2) {
            INTSetFlag(INT_U2RX);
            ReceiveCollisionOccured2 = FALSE;
        }
    }
    return ch;
}

/**
 * @Function _mon_putc(char c)
 * @param c - char to be sent
 * @return None.
 * @brief  overwrites weakly define extern to use circular buffer instead of Microchip 
 * functions
 * @author Max Dunne, 2011.11.10 */
void _mon_putc(int uart, char c)
{
    PutChar(uart, c);
}

/**
 * @Function _mon_puts(const char* s)
 * @param s - pointer to the string to be sent
 * @return None.
 * @brief  overwrites weakly defined extern to use circular buffer instead of Microchip 
 * functions
 * @author Max Dunne, 2011.11.10 */
void _mon_puts(int uart, const char* s)
{
    int i;
    for (i = 0; i<sizeof (s); i++)
        PutChar(uart, s[i]);
}

/**
 * @Function _mon_getc(int CanBlock)
 * @param CanBlock - unused variable but required to match Microchip form
 * @return None.
 * @brief  overwrites weakly defined extern to use circular buffer instead of Microchip 
 * functions
 * @author Max Dunne, 2011.11.10 */
int _mon_getc(int uart, int CanBlock)
{
    if (uart == 1){
        if (getLength(receiveBuffer1) == 0)
            return -1;
        return GetChar(1);
    }
    if (uart == 2){
        if (getLength(receiveBuffer2) == 0)
            return -1;
        return GetChar(2);
    }
    return -1;
}

/**
 * @Function IsReceiveEmpty(void)
 * @param None.
 * @return TRUE or FALSE
 * @brief  returns the state of the receive buffer
 * @author Max Dunne, 2011.12.15 */
char IsReceiveEmpty(int uart)
{
    if(uart == 1){
        if (getLength(receiveBuffer1) == 0)
            return TRUE;
    }
    if(uart == 2){
        if (getLength(receiveBuffer2) == 0)
            return TRUE;
    }
    return FALSE;
}

/**
 * @Function IsTransmitEmpty(void)
 * @param None.
 * @return TRUE or FALSE
 * @brief  returns the state of the receive buffer
 * @author Max Dunne, 2011.12.15 */
char IsTransmitEmpty(int uart)
{
    if (uart == 1){
        if (getLength(transmitBuffer1) == 0)
            return TRUE;
    }
    if(uart == 2){
        if (getLength(transmitBuffer2) == 0)
            return TRUE;
    }
    return FALSE;
}

/****************************************************************************
 Function
    IntUart1Handler

 Parameters
    None.

 Returns
    None.

 Description
    Interrupt Handle for the uart. with the PIC32 architecture both send and receive are handled within the same interrupt

 Notes


 Author
 Max Dunne, 2011.11.10
 ****************************************************************************/
void __ISR(_UART1_VECTOR, ipl4auto) IntUart1Handler(void)
{
    if (INTGetFlag(INT_U1RX)) {
        INTClearFlag(INT_U1RX);
        if (!GettingFromReceive1) {
            writeBack(receiveBuffer1, (unsigned char) U1RXREG);
        } else {
            //acknowledge we have a collision and return
            ReceiveCollisionOccured1 = TRUE;
        }
    }
    if (INTGetFlag(INT_U1TX)) {
        INTClearFlag(INT_U1TX);
        if (!(getLength(transmitBuffer1) == 0)) {
            if (!AddingToTransmit1) {
                U1TXREG = readFront(transmitBuffer1);
            } else {
                //acknowledge we have a collision and return
                TransmitCollisionOccured1 = TRUE;
            }
        }
    }

}

void __ISR(_UART2_VECTOR, ipl4auto) IntUart2Handler(void)
{
    if (INTGetFlag(INT_U2RX)) {
        INTClearFlag(INT_U2RX);
        if (!GettingFromReceive2) {
            writeBack(receiveBuffer2, (unsigned char) U2RXREG);
        } else {
            //acknowledge we have a collision and return
            ReceiveCollisionOccured2 = TRUE;
        }
    }
    if (INTGetFlag(INT_U2TX)) {
        INTClearFlag(INT_U2TX);
        if (!(getLength(transmitBuffer2) == 0)) {
            if (!AddingToTransmit2) {
                U2TXREG = readFront(transmitBuffer2);
            } else {
                //acknowledge we have a collision and return
                TransmitCollisionOccured2 = TRUE;
            }
        }
    }

}

/*******************************************************************************
 * PRIVATE FUNCTIONS                                                          *
 ******************************************************************************/

void newCircBuffer(CBRef cB)
{

    // initialize to zero
    int i;
    for (i = 0; i < QUEUESIZE; i++) {
        cB->buffer[i] = 0;
    }

    // initialize the data members
    cB->head = 0;
    cB->tail = 0;
    cB->size = QUEUESIZE;
    cB->overflowCount = 0;

}

// this function frees the Circular Buffer CB Ref

void freeCircBuffer(CBRef* cB)
{
    // if it is already null, nothing to free
    if (cB == NULL || *cB == NULL) {
        return;
    }

    // free and nil the pointer
    //free(*cB);
    *cB = NULL;
}




// Accesor Methods
// ===============

// returns the amount of unread bytes in the circular buffer

unsigned int getLength(CBRef cB)
{
    // if the circular buffer is not null
    if (cB != NULL) {
        if (cB->head <= cB->tail) {
            return (cB->tail - cB->head);
        } else {
            return (cB->size + cB->tail - cB->head);
        }
    } else {
        return 0;
    }


}

// returns the actual index of the head

int readHead(CBRef cB)
{
    // if the circular buffer is not null
    if (cB != NULL) {
        return (cB->head);
    } else {
        return 0;
    }

}

// returns the actual index of the tail

int readTail(CBRef cB)
{
    // if the circular buffer is not null
    if (cB != NULL) {
        return (cB->tail);
    } else {
        return 0;
    }

}

// returns the byte (actual value) that the head points to. this
// does not mark the byte as read, so succesive calls to peak will
// always return the same value

unsigned char peak(CBRef cB)
{
    // if the circular buffer is not null
    if (cB != NULL) {
        // if there are bytes in the buffer
        if (getLength(cB) > 0) {
            return cB->buffer[cB->head];
        }
    }
    return 0;
}


// Manipulation Procedures
// ======================
// returns the front of the circular buffer and marks the byte as read

unsigned char readFront(CBRef cB)
{
    // if the circular buffer is not null
    if (cB != NULL) {
        char retVal;
        // if there are bytes in the buffer
        if (getLength(cB) > 0) {
            retVal = cB->buffer[cB->head];
            cB->head = cB->head < (cB->size - 1) ? cB->head + 1 : 0;
            return retVal;
        }
        return 128;
    }
    return 254;
}

// writes one byte at the end of the circular buffer,
// increments overflow count if overflow occurs

unsigned char writeBack(CBRef cB, unsigned char data)
{
    // if the circular buffer is not null
    if (cB != NULL) {
        if (getLength(cB) == (cB->size - 1)) {
            cB->overflowCount++;
            //return 1;
        } else {
            cB->buffer[cB->tail] = data;
            cB->tail = cB->tail < (cB->size - 1) ? cB->tail + 1 : 0;
            //return 0;
        }
        //return 0;
    } else {
        return 1;
    }
    return 0;
}

// empties the circular buffer. It does not change the size. use with caution!!

void makeEmpty(CBRef cB)
{
    if (cB != NULL) {
        int i;
        for (i = 0; i < cB->size; ++i) {
            cB->buffer[i] = 0;
        }
        cB->head = 0;
        cB->tail = 0;
        cB->overflowCount = 0;
    }
}

// returns the amount of times the CB has overflown;

unsigned char getOverflow(CBRef cB)
{
    if (cB != NULL) {
        return cB->overflowCount;
    }
    return 0;
}



//#define SERIAL_TEST
#ifdef SERIAL_TEST
#include "serial.h"
#include "BOARD.h"
#include <GenericTypeDefs.h>
#include <stdio.h>

//#include <plib.h>
#define MAX_RAND (1<<10)
#define INUNDATION_TEST

int main(void)
{
    BOARD_Init();
    unsigned int i;
    printf("\r\nUno Serial Test Harness\r\nAfter this Message the terminal should mirror any single character you type.\r\n");
    // while(!IsTransmitEmpty());
    unsigned int NopCount = 0;
    unsigned char CharCount = 0;
#ifdef INUNDATION_TEST
    while (1) {
        NopCount = rand() % MAX_RAND + 1;
        //printf("%X\r\n",rand());
        for (i = 0; i < NopCount; i++) {
            asm("Nop");
        }
        for (CharCount = 32; CharCount < 128; CharCount++) {
            //printf("%c", CharCount);
            putchar(CharCount);
        }

    }
#endif
    GetChar();
//    unsigned char ch = 0;
    while (1) {
        if (IsTransmitEmpty() == TRUE)
            if (IsReceiveEmpty() == FALSE)
                PutChar(GetChar());
    }

    return 0;
}

#endif