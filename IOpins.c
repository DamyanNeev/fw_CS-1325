/* *****************************************************************************
 * File:   TinyModbus.c
 * Author: Damyan Neev
 * Created on 2022 11 01
 *
 * Description: source file for reduced ModBus commands.
 *      Device:  CS-1301_00  PIC16F1773
 *    Compiler:  XC8 v2.40   MPLAB X v6.00
 **************************************************************************** */


#ifdef _WIN32
#pragma once
#endif // _WIN32


//===================================
// Header Includes
//===================================
#include "mcc_Files/mcc.h"

#include "BoardConfig.h"
#include "DBGmeasurements.h"
#include "IOpins.h"


//===================================
// Configuration Definitions
//===================================
#define KP_DEBOUNCE_COUNT 3

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
volatile uint8_t  rotaryValue = 0x00;

bool  iPwmEN_Sample = 0;
bool  iPwmEN_Last = 0;
bool  iPwmEN_Stable;  //debounced key values. Visible all the time

uint8_t  iPwmEN_DebounceCounter = 0;

uint8_t  iEN_Changed;



//===================================
// Prototype of functions definitions
//===================================


//===================================
// Functions
//===================================

uint8_t Get_RotaryValue( void )
{
    return rotaryValue;
}

bool Get_iPwmEN_Stable( void )
{
    return iPwmEN_Stable;
}

void InitRotary( void )
{
    
    Sw18_SetDigitalMode();
    Sw18_SetDigitalInput();
    Sw18_SetPullup();
    
    Sw14_SetDigitalMode();
    Sw14_SetDigitalInput();
    Sw14_SetPullup();
    
    Sw12_SetDigitalMode();
    Sw12_SetDigitalInput();
    Sw12_SetPullup();
    
    Sw11_SetDigitalMode();
    Sw11_SetDigitalInput();
    Sw11_SetPullup();
}
    

void CheckRotaryValue( void )
{
    uint8_t tmpVal = 0;
    rotaryValue = 0;
   
//    T1measHigh();
    tmpVal = !(Sw18_GetValue());
    rotaryValue |= ( tmpVal << 3 );
    tmpVal = !(Sw14_GetValue());
    rotaryValue |= ( tmpVal << 2 );
    tmpVal = !(Sw12_GetValue());
    rotaryValue |= ( tmpVal << 1 );
    tmpVal = !(Sw11_GetValue());
    rotaryValue |= ( tmpVal << 0 );

//    T1measLow();  //8us
//    SetValueInHoldingRegister( (uint16_t)MB_ADDR_SWITCH, (uint16_t)rotaryValue );
}


void PWM_STOP( void )
{
    COG1ASD0bits.ASE = 1;
    COG2ASD0bits.ASE = 1;
    COG3ASD0bits.ASE = 1;
}

void PWM_Enable( void )
{
    COG1ASD0bits.ASE = 0;
    COG2ASD0bits.ASE = 0;
    COG3ASD0bits.ASE = 0;
}


