/* *****************************************************************************
 * File:   DBGmeasurements.h
 * Author: Damyan Neev
 * Created on 2022 11 01
 *
 * Description: header file for debug measurements in interrupts.
 *      Device:  CS-1301_00  PIC16F1773
 *    Compiler:  XC8 v2.40   MPLAB X v6.00
 **************************************************************************** */


#ifndef DBG_MEASUREMENTS_H
#define	DBG_MEASUREMENTS_H


//===================================
// Header Includes
//===================================
#include "mcc_Files/pin_manager.h"


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
#define  T1measHigh() //DBG1_SetHigh();
#define  T1measLow()  //DBG1_SetLow();

#define  T2measHigh() //DBG2_SetHigh();
#define  T2measLow()  //DBG2_SetLow();


#define  Flash1High() //DBG1_SetHigh();
#define  Flash1Low()  //DBG1_SetLow();

#define  Flash2High() //DBG2_SetHigh();
#define  Flash2Low()  //DBG2_SetLow();


#define  Mb1High() //DBG1_SetHigh();
#define  Mb1Low()  //DBG1_SetLow();

#define  Mb2High() //DBG2_SetHigh();
#define  Mb2Low()  //DBG2_SetLow();


#define  GreenHigh() //DBG1_SetHigh();
#define  GreenLow()  //DBG1_SetLow();

#define  BlueHigh() //DBG2_SetHigh();
#define  BlueLow()  //DBG2_SetLow();

    
//#define  DEBUG_RX_MESG( s, n )    for (; (s)<(n); (s)++) { GreenHigh();  GreenLow(); };
#define  DEBUG_RX_MESG()    GreenHigh(); GreenLow();


//#define  DEBUG_MB_RX

//#define  DEBUG_MB_PROCESS

//===================================
// Variables External Usage
//===================================


//===================================
// Function Prototypes
//===================================

void InitDBG( void );
//fast debug on pin
void GreenPosTicks( int ticks );
void BluePosTicks( int ticks );

void GreenNegTicks( int ticks );
void BlueNegTicks( int ticks );




#ifdef	__cplusplus
extern "C" {
#endif // __cplusplus
    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 
#ifdef	__cplusplus
}
#endif // __cplusplus

#endif	// DBG_MEASUREMENTS_H

