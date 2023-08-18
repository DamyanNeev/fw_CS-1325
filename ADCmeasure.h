/* *****************************************************************************
 * File:   ADCmeasure.h
 * Author: Damyan Neev
 * Created on 2022 11 01
 *
 * Description: header file for CurrentRMS and NTC measurements.
 *      Device:  CS-1301_00  PIC16F1773
 *    Compiler:  XC8 v2.40   MPLAB X v6.00
 **************************************************************************** */

 
#ifndef ADC_MEASURE_H
#define	ADC_MEASURE_H

    
//===================================
// Header Includes
//===================================


//===================================   
// Configuration Definitions
//===================================
    

//===================================
// Constants and Macros Definitions
//===================================


//===================================
// Enumeration Definitions
//===================================
typedef enum 
{
    ADC_POS_IDC,
    ADC_POS_AMB,
    ADC_POS_HS,
    ADC_POS_IND,
    ADC_POS_EX24V,

    ADC_POS_COUNT
} ADC_ChannelPosition_t;


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
void InitNTC_Order( void );

 int16_t GetIDCoffset( void );

void ReadADCchannels( void );
void vADCprocess( void );

 int16_t Get_ntcDeciValue( ADC_ChannelPosition_t addrDeciValue );

void Set_ntcOffset( ADC_ChannelPosition_t ntcPos,  int16_t ntcVal );
void Set_ntcCoef  ( ADC_ChannelPosition_t ntcPos, uint16_t coefVal );


#ifdef	__cplusplus
extern "C" {
#endif // __cplusplus
    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 
#ifdef	__cplusplus
}
#endif // __cplusplus

#endif // ADC_MEASURE_H