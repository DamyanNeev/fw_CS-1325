/* *****************************************************************************
 * File:   Uarts.c
 * Author: Damyan Neev
 * Created on 2022 02 27
 *
 * Description: source file for uarts handling.
 *      Device:  CS-1301_00  PIC16F1773
 *    Compiler:  XC8 v2.40   MPLAB X v6.00
 **************************************************************************** */


#ifdef _WIN32
#pragma once
#endif // _WIN32


//===================================
// Header Includes
//===================================

//#include <xc.h>         /* XC8 General Include File */
//#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */
//#include <string.h>
//#include <stdio.h>
//#include "mcc_Files/tmr1.h"


#include "BoardConfig.h"
#include "DBGmeasurements.h"
#include "Uarts.h"


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
uint64_t byteReceivedLastTimeMs = 0;
uint64_t delayResponseTimeMs = 0;
bool  bStartOfFrame = false;


//===================================
// Prototype of functions definitions
//===================================


//===================================
// Functions
//===================================


uint64_t Get_delayResponseTimeMs( void )
{
    return delayResponseTimeMs;
}
