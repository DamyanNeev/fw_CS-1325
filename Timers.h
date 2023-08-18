/* *****************************************************************************
 * File:   Timers.h
 * Author: Damyan Neev
 * Created on 2023 02 27
 *
 * Description: header file for Timers.
 *      Device:  CS-1301_01  PIC16F1773
 *    Compiler:  XC8 v2.40   MPLAB X v6.00
 **************************************************************************** */


#ifndef TIMERS_H
#define	TIMERS_H


//===================================
// Header Includes
//===================================
#include <stdbool.h>


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
// Function-Like Macro
//===================================


//===================================
// Variables External Usage
//===================================


//===================================
// Function Prototypes
//===================================
void InitTimers( void );
    
uint64_t Get_currentTimeMs( void );
void Set_bCheckUART( bool val );
bool Get_bCheckUART( void );



uint8_t Get_delayFromPrevRxByteMs( void );
void Clear_delayFromPrevRxByteMs( void );

uint8_t Get_delayResponseTimeMs( void );
void Clear_delayResponseTimeMs( void );


#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus
     // TODO If C++ is being used, regular C code needs function names to have C 
     // linkage so the functions can be used by the c code. 
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // TIMERS_H