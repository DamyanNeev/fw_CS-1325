/* *****************************************************************************
 * File:   IGBTdriver.c
 * Author: Damyan Neev
 * Created on 2022 03 24
 *
 * Description: source file for control of IGBT driver
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

#include "ADCmeasure.h"
#include "BoardConfig.h"
#include "DBGmeasurements.h"
#include "IGBTdriver.h"
#include "IOpins.h"
#include "TinyModbus.h"


//===================================
// Configuration Definitions
//===================================


//===================================
// Constants and Macros Definitions
//===================================
#define OFF    0
#define READY  1

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
IGBT_DRV_State_t  igbtDrvState = IGBT_STA_IDLE;


//===================================
// Prototype of functions definitions
//===================================


//===================================
// Functions
//===================================

//#define     pinFLT      PORTAbits.RA4
//#define     piRDY1      PORTBbits.RB2
//#define     piPWM_EN    PORTEbits.RE2

//#define     poDrvRst    PORTBbits.RB1
//#define     poFltOut    PORTBbits.RB7   // use CLCIN3 to reset ENABLE trigger
//#define     ponEN       PORTEbits.RE1

//#define     fFlt        CLC2CONbits.LC2OUT      // use CLC2 block = !FLT or !IOC
/*
 Error trigger logic:
 *  error set logic = !IOC | !FLT | SWerror | !PWM_EN
 *  error reset logic = SWreset
 *  !EN = Q error trigger
 * SWerror = CalculatedRMScurrent | over temperature 
 * SWreset = 
 * FltOut =  
 */


void STOP_SetERR( Err_ReadStatusRegs_t err )
{
    PWM_STOP(); // Stop PWMS
    SetErr_MB_I_STATUS( err ); // 
    Set_controlState( OFF );
    igbtDrvState = IGBT_STA_FAULT;
}











void vCheckTrips( void )
{
    if ( (Get_ntcDeciValue( ADC_POS_IDC ) > Get_tripValues( TRIP_IDC_P_POS )) | ( Get_ntcDeciValue(ADC_POS_IDC ) < Get_tripValues( TRIP_IDC_N_POS )) )
    {
        STOP_SetERR( ERR_TRIP_DCLINK );
    }

    if( Get_ntcDeciValue( ADC_POS_AMB ) > Get_tripValues( TRIP_AMB_P_POS ) )
    {
        STOP_SetERR( ERR_AMB_TRIP_TEMP );
    }

    if ( Get_ntcDeciValue( ADC_POS_HS ) > Get_tripValues( TRIP_HS_P_POS ) )
    {
        STOP_SetERR( ERR_HS_TRIP_TEMP );
    }

    if ( Get_ntcDeciValue( ADC_POS_IND ) > Get_tripValues( TRIP_IND_P_POS ) )
    {
        STOP_SetERR( ERR_IND_TRIP_TEMP );
    }
    
    
    if( Get_ntcDeciValue( ADC_POS_EX24V ) < Get_tripValues( TRIP_EX24V_P_POS ) )
    {
        SetErr_MB_I_STATUS( ERR_WARNING_24V );
    }
    else
    {
        ClearErr_MB_I_STATUS( ERR_WARNING_24V );
    }
}


void vIGBTcontrol( void )
{
    
    switch( igbtDrvState )
    {
        case IGBT_STA_IDLE:

            if ( CONTROL_START == Get_controlValue() )
            {
//                PWM_Enable();
                Set_controlState( READY );
                igbtDrvState = IGBT_STA_READY;    // leave fault state only if PWM_EN is high
            }
            break;

        case IGBT_STA_READY:
            if ( CONTROL_STOP == Get_controlValue() )
            {
                PWM_STOP();
                Set_controlState( OFF );
                igbtDrvState = IGBT_STA_IDLE;
            }
            if ( P_HIGH == Get_iPwmEN_Stable() )
            {
                PWM_Enable();
                igbtDrvState = IGBT_STA_DRIVE;  // goto driving state
            }
            break;

        case IGBT_STA_DRIVE:     // driving state
            if ( P_LOW == Get_iPwmEN_Stable() )
            {
                PWM_STOP();
                Set_controlState( OFF );
                igbtDrvState = IGBT_STA_IDLE;
            }
            if ( CONTROL_STOP == Get_controlValue() )
            {
                PWM_STOP();
                Set_controlState( OFF );
                igbtDrvState = IGBT_STA_IDLE;
            }
            break;

        case IGBT_STA_FAULT:  // halt here until clear start from ModBus
//            if ( CONTROL_STOP == Get_controlValue() )
//            {
//                igbtDrvState = IGBT_STA_RESET;
//            }
            if ( P_LOW == Get_iPwmEN_Stable() )
            {
                __delay_ms(20);
                igbtDrvState = IGBT_STA_RESET;
            }
            break;

        case IGBT_STA_RESET:

            SetValue_mbInputReg( MB_I_STATUS, 0x0000 );
            igbtDrvState = IGBT_STA_IDLE;
            break;

        default:
            PWM_STOP();
            Set_controlState( OFF );
            igbtDrvState = IGBT_STA_FAULT;  // illegal -> fault state
    }
}