/* *****************************************************************************
 * File:   Timers.c
 * Author: Damyan Neev
 * Created on 2022 02 27
 *
 * Description: source file for timers handling.
 *      Device:  CS-1301_00  PIC16F1773
 *    Compiler:  XC8 v2.40   MPLAB X v6.00
 **************************************************************************** */


#ifdef _WIN32
#pragma once
#endif // _WIN32


//===================================
// Header Includes
//===================================
#include "mcc_Files/tmr1.h"
#include "mcc_Files/tmr5.h"

#include "BoardConfig.h"
#include "DBGmeasurements.h"
#include "Timers.h"


//===================================
// Configuration Definitions
//===================================


//===================================
// Constants and Macros Definitions
//===================================


//===================================
// Enumeration Definitions
//===================================


//===================================
// Type Definitions
//===================================


//===================================
// Function-Like Macros
//===================================


//===================================
// Variables Definitions
//===================================
uint64_t currentTimeMs    = 0;  // system time in milliseconds
uint64_t currentTime100us = 0;  // system time in milliseconds
bool     bCheckUART = false;

uint8_t delayFromPrevRxByteMs = 0xFF;  //
uint8_t delayResponseTimeMs   = 0xFF;  //


//===================================
// Prototype of functions definitions
//===================================


//===================================
// Functions
//===================================

uint64_t Get_currentTimeMs( void )
{
    return currentTimeMs;
}

//uint64_t Get_currentTime100us( void )
//{
//    return currentTime100us;
//}

uint8_t Get_delayFromPrevRxByteMs( void )
{
    return delayFromPrevRxByteMs;
}

void Clear_delayFromPrevRxByteMs( void )
{
    delayFromPrevRxByteMs = 0;
}

uint8_t Get_delayResponseTimeMs( void )
{
    return delayResponseTimeMs;
}

void Clear_delayResponseTimeMs( void )
{
    delayResponseTimeMs = 0;
}

void Set_bCheckUART( bool val )
{
    bCheckUART = val;
}

bool Get_bCheckUART( void )
{
    return bCheckUART;
}


void TMR1_CountMs(void)
{
//    T1measHigh();

    currentTimeMs += 1;
    
    if ( delayFromPrevRxByteMs < 0xFF )
    {
        delayFromPrevRxByteMs++;
    }
    if( delayResponseTimeMs < 0xFF )
    {
        delayResponseTimeMs++;
    }
    
//    T1measLow();  //every 1ms
}


//void TMR5_Count100us(void)
//{
////    T2measHigh();  //every 105us
//
//    currentTime100us += 1;
//    
////    T2measLow();  //1.7us
//}


void InitTimers( void )
{
    TMR1_SetInterruptHandler ( &TMR1_CountMs );
//    TMR5_SetInterruptHandler ( &TMR5_Count100us );
    
    TMR1_StartTimer();
    TMR5_StartTimer();
}

