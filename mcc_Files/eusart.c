/**
  EUSART Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    eusart.c

  @Summary
    This is the generated driver implementation file for the EUSART driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides APIs for EUSART.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC16F1779
        Driver Version    :  2.1.1
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above
        MPLAB 	          :  MPLAB X 6.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

/**
  Section: Included Files
*/
#include "mcc.h"
#include "eusart.h"
#include "../Timers.h"
#include "pin_manager.h"
#include "../DBGmeasurements.h"
#include "../TinyModbus.h"



/**
  Section: Macro Declarations
*/

//#define EUSART_TX_BUFFER_SIZE  8
//#define EUSART_RX_BUFFER_SIZE  8

#define EUSART_TX_BUFFER_SIZE  RESPONCE_REG_COUNT*2
#define EUSART_RX_BUFFER_SIZE  RECEIVE_REG_COUNT

/**
  Section: Global Variables
*/
volatile uint8_t eusartTxHead = 0;
volatile uint8_t eusartTxTail = 0;
volatile uint8_t eusartTxBuffer[EUSART_TX_BUFFER_SIZE];
volatile uint8_t eusartTxBufferRemaining;

volatile uint8_t eusartRxHead = 0;
volatile uint8_t eusartRxTail = 0;
volatile uint8_t eusartRxBuffer[EUSART_RX_BUFFER_SIZE];
volatile eusart_status_t eusartRxStatusBuffer[EUSART_RX_BUFFER_SIZE];
volatile uint8_t eusartRxCount;
volatile eusart_status_t eusartRxLastError;


//uint64_t byteReceivedLastTimeMs = 0;

//uint64_t delayResponseTimeMs = 0;
//bool  bStartOfFrame = false;


uint64_t byteRxLastTimeMs = 0;

/**
  Section: EUSART APIs
*/
void (*EUSART_TxDefaultInterruptHandler)(void);
void (*EUSART_RxDefaultInterruptHandler)(void);

void (*EUSART_FramingErrorHandler)(void);
void (*EUSART_OverrunErrorHandler)(void);
void (*EUSART_ErrorHandler)(void);

void EUSART_DefaultFramingErrorHandler(void);
void EUSART_DefaultOverrunErrorHandler(void);
void EUSART_DefaultErrorHandler(void);




//uint64_t Get_delayResponseTimeMs( void )
//{
//    return delayResponseTimeMs;
//}

uint8_t Get_eusartRxCount( void )
{
    return eusartRxCount;
}

//void Reset_eusartRxCount( void )
//{
//    eusartRxCount = 0;
//}

//uint8_t Get_eusartRxHead( void )
//{
//    return eusartRxHead;
//}


void EUSART_Initialize(void)
{
    // disable interrupts before changing states
    PIE1bits.RCIE = 0;
    EUSART_SetRxInterruptHandler(EUSART_Receive_ISR);
    PIE1bits.TXIE = 0;
    EUSART_SetTxInterruptHandler(EUSART_Transmit_ISR);
    // Set the EUSART module to the options selected in the user interface.

//    BAUD1CON = 0x08;  // ABDOVF no_overflow; SCKP Non-Inverted; BRG16 16bit_generator; WUE disabled; ABDEN disabled; 
//    BAUD1CON = 0x18;  // ABDOVF no_overflow; SCKP Inverted; BRG16 16bit_generator; WUE disabled; ABDEN disabled; 
    BAUD1CON = 0x00;
    BAUD1CONbits.SCKP = 0;
    BAUD1CONbits.BRG16 = 1;

    // SPEN enabled; RX9 8-bit; CREN enabled; ADDEN disabled; SREN disabled; 
    RC1STA = 0x90;

    // TX9 8-bit; TX9D 0; SENDB sync_break_complete; TXEN enabled; SYNC asynchronous; BRGH hi_speed; CSRC slave; 
    TX1STA = 0x24;

    SP1BRGL = 0x44;  // SP1BRGL  68;  115200
//    SP1BRGL = 0x8A;  // SP1BRGL 138;   57600

    // SP1BRGH 0; 
    SP1BRGH = 0x00;


    EUSART_SetFramingErrorHandler(EUSART_DefaultFramingErrorHandler);
    EUSART_SetOverrunErrorHandler(EUSART_DefaultOverrunErrorHandler);
    EUSART_SetErrorHandler(EUSART_DefaultErrorHandler);

    eusartRxLastError.status = 0;

    // initializing the driver state
    eusartTxHead = 0;
    eusartTxTail = 0;
    eusartTxBufferRemaining = sizeof(eusartTxBuffer);

    eusartRxHead = 0;
    eusartRxTail = 0;
    eusartRxCount = 0;

    // enable receive interrupt
    PIE1bits.RCIE = 1;
}

//bool EUSART_is_tx_ready(void)
//{
//    return (eusartTxBufferRemaining ? true : false);
//}

//bool EUSART_is_rx_ready(void)
//{
//    return (eusartRxCount ? true : false);
//}

//bool EUSART_is_tx_done(void)
//{
//    return TX1STAbits.TRMT;
//}

//eusart_status_t EUSART_get_last_status(void){
//    return eusartRxLastError;
//}

uint8_t EUSART_Read(void)
{
    uint8_t readValue  = 0;
    
    while(0 == eusartRxCount)
    {
    }

    eusartRxLastError = eusartRxStatusBuffer[eusartRxTail];

    readValue = eusartRxBuffer[eusartRxTail++];
    if(sizeof(eusartRxBuffer) <= eusartRxTail)
    {
        eusartRxTail = 0;
    }
    PIE1bits.RCIE = 0;
    eusartRxCount--;
    PIE1bits.RCIE = 1;

    return readValue;
}

void EUSART_Write(uint8_t txData)
{
    while(0 == eusartTxBufferRemaining)
    {
    }

    if(0 == PIE1bits.TXIE)
    {
        TX1REG = txData;
    }
    else
    {
        PIE1bits.TXIE = 0;
        eusartTxBuffer[eusartTxHead++] = txData;
        if(sizeof(eusartTxBuffer) <= eusartTxHead)
        {
            eusartTxHead = 0;
        }
        eusartTxBufferRemaining--;
    }
    PIE1bits.TXIE = 1;
}


void EUSART_Transmit_ISR(void)
{
#ifdef DEBUG_TX_BUF
    BlueTicks ( 2 );
#endif
    // add your EUSART interrupt custom code
    if(sizeof(eusartTxBuffer) > eusartTxBufferRemaining)
    {
        TX1REG = eusartTxBuffer[eusartTxTail++];
        if(sizeof(eusartTxBuffer) <= eusartTxTail)
        {
            eusartTxTail = 0;
        }
        eusartTxBufferRemaining++;
    }
    else
    {
        PIE1bits.TXIE = 0;
    }
}


void RxDataHandler( void )
{
    eusartRxBuffer[eusartRxHead++] = RC1REG;
    if(sizeof(eusartRxBuffer) <= eusartRxHead)
    {
        eusartRxHead = 0;
    }
    eusartRxCount++;
    
    Clear_delayFromPrevRxByteMs();
    Set_bCheckUART( true );
}


void EUSART_Receive_ISR(void)
{
#ifdef DEBUG_RX_BUF
    BlueHigh();
#endif
            
    eusartRxStatusBuffer[eusartRxHead].status = 0;

    if( RC1STAbits.FERR )
    {
        #ifdef DEBUG_RX_BUF
//        GreenPosTicks( 1 );
        #endif
        eusartRxStatusBuffer[eusartRxHead].ferr = 1;
//        EUSART_FramingErrorHandler();
//        EUSART_DefaultOverrunErrorHandler();
    }

    if( RC1STAbits.OERR )
    {
        #ifdef DEBUG_RX_BUF
//        GreenPosTicks( 2 );
        #endif
        eusartRxStatusBuffer[eusartRxHead].oerr = 1;
//        EUSART_OverrunErrorHandler();
//        EUSART_DefaultFramingErrorHandler();
    }
    
    if( eusartRxStatusBuffer[eusartRxHead].status )
    {
        #ifdef DEBUG_RX_BUF
//        GreenPosTicks( 3 );
        #endif
//        EUSART_ErrorHandler();
        EUSART_DefaultErrorHandler();
    }
    else
    {
//        EUSART_RxDataHandler();
        RxDataHandler();
    }
    
#ifdef DEBUG_RX_BUF
    BlueLow();
#endif
}


//void __attribute__ ( (interrupt, auto_psv) ) _U1RXInterrupt( void )

//    
//    while (U1STAbits.URXDA == 1) 
//    {
//    if ((UARTRxBufferWRCount[UART_1] - UARTRxBufferRDCount[UART_1]) <= UART_RX_BUFFER_SIZE) 
//    {
//        u32TimeDiffNow[UART_1] = HMDRV_GET_FREE_RUN_TIMER();
//        UARTRxBufferTimeDiff[UART_1][UARTRxBufferWRIndex[UART_1]] = u32TimeDiffNow[UART_1] - u32TimeDiffLast[UART_1];
//        u32TimeDiffLast[UART_1] = u32TimeDiffNow[UART_1];
//        UARTRxBuffer[UART_1][UARTRxBufferWRIndex[UART_1]++] = U1RXREG;
//        UARTRxBufferWRCount[UART_1]++;
//        if (UARTRxBufferWRIndex[UART_1] >= UART_RX_BUFFER_SIZE)
//        {
//            UARTRxBufferWRIndex[UART_1] = 0;
//        } 
//        HMDRV_RESET_TX_DELAY(UART_1);
//    }
//    else
//    {
//        U1RXREG;
//        UART_RXIntOverflowCounter[UART_1]++;
//    }
//    }
//   
//    IFS0bits.U1RXIF = 0;
//    DEBUG_CLR_USART1_RX();
//}





void EUSART_DefaultFramingErrorHandler(void)
{
    // EUSART error - restart
    RC1STAbits.CREN = 0;
    RC1STAbits.CREN = 1;
}

void EUSART_DefaultOverrunErrorHandler(void)
{
    // EUSART error - restart
    RC1STAbits.CREN = 0;
    RC1STAbits.CREN = 1;
}

void EUSART_DefaultErrorHandler(void){
        // EUSART error - restart
    eusartRxStatusBuffer[eusartRxHead].ferr = 1;
    eusartRxStatusBuffer[eusartRxHead].oerr = 1;
        
    RC1STAbits.CREN = 0;
    RC1STAbits.CREN = 1;
}

void EUSART_SetFramingErrorHandler(void (* interruptHandler)(void)){
    EUSART_FramingErrorHandler = interruptHandler;
}

void EUSART_SetOverrunErrorHandler(void (* interruptHandler)(void)){
    EUSART_OverrunErrorHandler = interruptHandler;
}

void EUSART_SetErrorHandler(void (* interruptHandler)(void)){
    EUSART_ErrorHandler = interruptHandler;
}

void EUSART_SetTxInterruptHandler(void (* interruptHandler)(void)){
    EUSART_TxDefaultInterruptHandler = interruptHandler;
}

void EUSART_SetRxInterruptHandler(void (* interruptHandler)(void)){
    EUSART_RxDefaultInterruptHandler = interruptHandler;
}
/**
  End of File
*/
