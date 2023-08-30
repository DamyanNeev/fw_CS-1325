/* *****************************************************************************
 * File:   ADCmeasurements.c
 * Author: Damyan Neev
 * Created on 2022 11 01
 *
 * Description: source file for template.
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
#include "TinyMClib.h"
#include "TinyModbus.h"


//===================================
// Configuration Definitions
//===================================


//===================================
// Constants and Macros Definitions
//===================================
//#define LUT_LEN 25
#define LUT_LEN_NCP21     34
#define LUT_LEN_NTCLE350  46


#define DECI_DEGREE_STEP 50

#define ADC_RESULT_BITS                  10  // 10-bit ADC
#define ADC_MAX_RESULT                 1023
#define ADC_MIN_RESULT                    0
#define EX24_DIODE_DROP_DECI              3  // 0.3V drop over diode
#define EX24_MAX_IN_VOLT_DECI           315  // 31.5V max input on EX24 pin
#define EX24_ADC_TO_DECI_VOLT_MULT      EX24_MAX_IN_VOLT_DECI - EX24_DIODE_DROP_DECI  //

#define IDC_MAX_IN_AMP_DECI            1195  // 119.5A max sense
#define IDC_OFFSET                      512  // 0A expect to be 512 bits

//#define ADCResultToDeciVoltageMultiplier         312                           /* was ADC_RESULT_TO_VOLTS_DC_MULT */
//
//#define RES_DIVIDER_MULT            ( 8200.0F / (43000.0F + 8200.0F) )
//
//#define DIODE_DROP                  0.3F  // 0.3V drop over diode
//#define MAX_IN_VOLT                 31.5F  // 0.3V drop over diode
//#define MAX_ADC_IN_VOLT             5.0F  // 0.3V drop over diode
//
//#define ADC_DIVIDER_MULT            (( RES_DIVIDER_MULT << ADC_RESULT_BITS ) / MAX_ADC_IN_VOLT )
//
//#define ADC_RESULT_TO_UFBK_MULT     ( ( MAX_IN_VOLT - DIODE_DROP ) * RES_DIVIDER_MULT * MAX_ADC_IN_VOLT )


//===================================
// Enumeration Definitions
//===================================



//===================================
// Type Definitions
//===================================
typedef struct {
    uint16_t bits;
     int16_t tempr;
} adcCoord_t;


typedef enum
{
    ADC_STA_AMB,
    ADC_STA_HS,
    ADC_STA_IND,
    ADC_STA_EX24V,
//    ADC_STA_READY,
            
    ADC_STA_COUNT
}ADC_CalcState_t;


//===================================
// Function-Like Macros
//===================================


//===================================
// Variables Definitions
//===================================
volatile  int16_t ntcOffset[ADC_POS_COUNT];    // offset. Set from ModBus registers
volatile uint16_t ntcBuffered[ADC_POS_COUNT];  // values from ADC
volatile uint16_t ntcNoOffset[ADC_POS_COUNT];

MCLIB_sFilterAVGu16_t sNtc_ResultAvg[ADC_POS_COUNT];

volatile uint16_t ntcCoef[ADC_POS_COUNT];  // scaling coefficient 500 to 2000 (0.5 - 2.0). Set from ModBus registers

//volatile uint16_t coefBuffered;
//volatile    float scalerBuffered;

volatile  int16_t ntcDeciValue[ADC_POS_COUNT];  // calculated value multiplied x10


bool     bADCsamplesReady = false;
bool     bIDCsampleReady  = false;

//volatile    float scaled_idcDeciValue = 0.0;

volatile uint16_t ntcScaledDeciValue[6] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };  // scaled calculated value multiplied x10

ADC_CalcState_t ADC_CalcState = ADC_STA_AMB;


//===================================
// Prototype of functions definitions
//===================================


//===================================
// Functions
//===================================
int16_t Get_ntcDeciValue( ADC_ChannelPosition_t addrDeciValue )
{
    return ntcDeciValue[addrDeciValue];
}
        

void Set_ntcOffset( ADC_ChannelPosition_t ntcPos, int16_t offsetVal )
{
    ntcOffset[ntcPos] = offsetVal;
}

void Set_ntcCoef( ADC_ChannelPosition_t ntcPos, uint16_t coefVal )
{
    ntcCoef[ntcPos] = coefVal;
}

//int16_t GetIDCoffset( void )
//{
//    uint16_t tmp;
//     int16_t tmpOff;
//    
//    __delay_ms(1000);
//    
//    tmp = ADC_GetConversion( IDC );
//    
//    tmpOff = (int16_t)(tmp - IDC_OFFSET);
//    return tmpOff;
//
//}


void InitNTC_Order( void )
{
    int n;

    MCLIB_u16FilterAvgInit( IDC_SAMPLE_FILT, &sNtc_ResultAvg[ADC_POS_IDC]   );
    MCLIB_u16FilterAvgInit( NTC_SAMPLE_FILT, &sNtc_ResultAvg[ADC_POS_AMB]   );
    MCLIB_u16FilterAvgInit( NTC_SAMPLE_FILT, &sNtc_ResultAvg[ADC_POS_HS]    );
    MCLIB_u16FilterAvgInit( NTC_SAMPLE_FILT, &sNtc_ResultAvg[ADC_POS_IND]   );
    MCLIB_u16FilterAvgInit( NTC_SAMPLE_FILT, &sNtc_ResultAvg[ADC_POS_EX24V] );
    
    for( n = 0; n < ADC_POS_COUNT; n++)
    {
        ntcOffset[n]    = 0x0000;
        ntcBuffered[n]  = 0x0000;
        ntcNoOffset[n]  = 0x0000;
        ntcCoef[n]      = 0x03E8;  // 1000 => coef = 1.0
        ntcDeciValue[n] = 0x0000;
    }
    ntcBuffered[ADC_POS_AMB]   = 0x0200;
    ntcBuffered[ADC_POS_HS]    = 0x0200;
    ntcBuffered[ADC_POS_IND]   = 0x0200;
    ntcBuffered[ADC_POS_EX24V] = 0x030C;
}





void ReadADCchannels( void )
{
    uint16_t tmpOffset;
//    T1measHigh(); T2measHigh();
    ntcBuffered[ADC_POS_AMB]   = ADC_GetConversion( NTCAmb );
    ntcBuffered[ADC_POS_HS]    = ADC_GetConversion( NTCHS  );
    ntcBuffered[ADC_POS_IND]   = ADC_GetConversion( NTCInd );
    ntcBuffered[ADC_POS_EX24V] = ADC_GetConversion( ex24V  );

    int n;
    for ( n = ADC_POS_AMB; n <= ADC_POS_EX24V; n++ )
    {
        if ( ntcOffset[n] >= 0 )
        {
            ntcNoOffset[n] = ntcBuffered[n] + (uint16_t)ntcOffset[n];
            if ( ADC_MAX_RESULT < ntcNoOffset[n] )
            {
                ntcNoOffset[n] = ADC_MAX_RESULT;
            }
        }
        else
        {
            tmpOffset = (uint16_t)( 0 - ntcOffset[n]);
            if ( tmpOffset < ntcBuffered[n] )
            {
                ntcNoOffset[n] = ntcBuffered[n] - tmpOffset;
            }
            else 
            {
                ntcNoOffset[n] = ADC_MIN_RESULT;
            }
        }
    }
    bADCsamplesReady = true;
//    T2measLow();  //165us
}


adcCoord_t adcNCP21XV103[LUT_LEN_NCP21] = 
{
// ( bits  temperature ) 
    { 999, -400 },
    { 989, -350 },
    { 975, -300 },
    { 957, -250 },
    { 935, -200 },
    { 907, -150 },
    { 874, -100 },
    { 834,  -50 },
    { 789,    0 },
    { 739,   50 },
    { 684,  100 },
    { 628,  150 },
    { 570,  200 },
    { 512,  250 },
    { 456,  300 },
    { 404,  350 },
    { 355,  400 },
    { 311,  450 },
    { 271,  500 },
    { 235,  550 },
    { 204,  600 },
    { 177,  650 },
    { 154,  700 },
    { 133,  750 },
    { 116,  800 },
    { 101,  850 },
    {  88,  900 },
    {  77,  950 },
    {  67, 1000 },
    {  59, 1050 },
    {  52, 1100 },
    {  46, 1150 },
    {  40, 1200 },
    {  36, 1250 },  //LUT_LEN_NCP21 - 1  Max NTC temperature is 125 C
};  // NCP21XV103J03RA


int16_t InterpNCP21XV103( uint16_t adcVal )
{
//    T1measHigh(); T2measHigh();
    int vIndex;
//    float ddd = 0.0;
    float d1, d2, d3;
    int16_t result, delta;
    int16_t rrr = 0, uuu = 0;

    if ( adcVal < 53)  adcVal =  53;
    if ( adcVal > 739) adcVal = 739;
    
    //Calculate the range in the grid adcCoord.x, x is fallen 
    if ( adcVal > adcNCP21XV103[1].bits)
    {
        vIndex = 1;
    }
    else if ( adcVal < adcNCP21XV103[LUT_LEN_NCP21 - 2].bits)
    {
        vIndex = LUT_LEN_NCP21 - 1;
    }
    else
    {
        for ( vIndex = 1; vIndex < LUT_LEN_NCP21-1; vIndex++)
        {
            if ( adcVal > adcNCP21XV103[vIndex].bits )
            {
                break;  //keep vIndex
            }
        }
    }
//    T1measLow();  // upto 70us
    
    //Linear interpolation
//    ddd = ( adcVal - adcNCP18XH103[vIndex].bits ) * DECI_DEGREE_STEP / (adcNCP18XH103[vIndex+1].bits - adcNCP18XH103[vIndex].bits);
////    T2measLow();  // upto 270us
//    delta = (int16_t) ddd;
    d1 = ( adcVal - adcNCP21XV103[vIndex].bits ) * DECI_DEGREE_STEP;
    d2 = (adcNCP21XV103[vIndex-1].bits - adcNCP21XV103[vIndex].bits);
    d3 = d1 / d2;
    d3 += 0.5;
    delta = (int16_t) d3;
    
    rrr = adcNCP21XV103[vIndex].tempr;
    uuu = rrr - delta; 
    result = (adcNCP21XV103[vIndex].tempr - delta);
//    T2measLow();  // upto 330us
    return result;   
}   


adcCoord_t adcNTCLE350E4103[LUT_LEN_NTCLE350] = 
{
// ( bits  temperature ) 
    {1000, -400 },
    { 990, -350 },
    { 976, -300 },
    { 959, -250 },
    { 937, -200 },
    { 909, -150 },
    { 876, -100 },
    { 836,  -50 },
    { 791,    0 },
    { 741,   50 },
    { 686,  100 },
    { 629,  150 },
    { 570,  200 },
    { 512,  250 },
    { 456,  300 },
    { 403,  350 },
    { 354,  400 },
    { 309,  450 },
    { 269,  500 },
    { 233,  550 },
    { 202,  600 },
    { 175,  650 },
    { 151,  700 },
    { 131,  750 },
    { 114,  800 },
    {  99,  850 },
    {  86,  900 },
    {  75,  950 },
    {  65, 1000 },
    {  57, 1050 },
    {  50, 1100 },
    {  44, 1150 },
    {  39, 1200 },
    {  35, 1250 },
    {  31, 1300 },
    {  27, 1350 },
    {  24, 1400 },
    {  22, 1450 },
    {  19, 1500 },
    {  17, 1550 },
    {  16, 1600 },
    {  14, 1650 },
    {  13, 1700 },
    {  12, 1750 },
    {  11, 1800 },
    {  10, 1850 },  // LUT_LEN_NTCLE350 - 1  Max NTC temperature is 185 C
};  // NTCLE350E4103FHB0



int16_t InterpNTCLE350E4103( uint16_t adcVal )
{
//    T1measHigh(); T2measHigh();
    int vIndex;
    float d1, d2, d3;
    int16_t result, delta;
    int16_t rrr = 0, uuu = 0;

    if ( adcVal < 10)  adcVal =  10;
    if ( adcVal > 741) adcVal = 741;
    
    //Calculate the range in the grid adcCoord.x, x is fallen 
    if ( adcVal > adcNTCLE350E4103[1].bits)
    {
        vIndex = 1;
    }
    else if ( adcVal < adcNTCLE350E4103[LUT_LEN_NTCLE350 - 2].bits)
    {
        vIndex = LUT_LEN_NTCLE350 - 1;
    }
    else
    {
        for ( vIndex = 1; vIndex < LUT_LEN_NTCLE350-1; vIndex++)
        {
            if ( adcVal > adcNTCLE350E4103[vIndex].bits )
            {
                break;  //keep vIndex
            }
        }
    }
//    T1measLow();  // upto 70us
    
    //Linear interpolation
    d1 = ( adcVal - adcNTCLE350E4103[vIndex].bits ) * DECI_DEGREE_STEP;
    d2 = (adcNTCLE350E4103[vIndex-1].bits - adcNTCLE350E4103[vIndex].bits);
    d3 = d1 / d2;
    d3 += 0.5;
    delta = (int16_t) d3;
//    T2measLow();  // upto 270us
    
    rrr = adcNTCLE350E4103[vIndex].tempr;
    uuu = rrr - delta; 
    result = (adcNTCLE350E4103[vIndex].tempr - delta);
//    T2measLow();  // upto 330us
    return result;   
}   


void vADCprocess( void )
{
    uint16_t mbIDChexVal;
    uint16_t tmpIDCcoef;
    float    tmpIDCscaler;
    float    tmpIDCdeciValue;
    
    uint16_t mbNTChexVal;
    uint16_t tmpNTCcoef;
    float    tmpNTCscaler;
    float    tmpNTCdeciValue;
    
    if( true == bIDCsampleReady )
    {
        bIDCsampleReady = false;
        
//        T1measHigh();  T2measHigh();
        mbIDChexVal = MCLIB_u16FilterAvg( ntcNoOffset[ADC_POS_IDC], &sNtc_ResultAvg[ADC_POS_IDC] );
        SetValue_mbInputReg( MB_I_IDC_HEX, mbIDChexVal );
//        T1measLow();  // upto 200uS

        if ( mbIDChexVal >= IDC_OFFSET )
        {
            ntcDeciValue[ADC_POS_IDC] = (int16_t) ( (MCLIB_u32Mul_u16u16( ( mbIDChexVal - IDC_OFFSET), IDC_MAX_IN_AMP_DECI )) >> (ADC_RESULT_BITS-1) );
        }
        else
        {
            ntcDeciValue[ADC_POS_IDC] = (int16_t) ( - ( (MCLIB_u32Mul_u16u16( (IDC_OFFSET - mbIDChexVal), IDC_MAX_IN_AMP_DECI )) >> (ADC_RESULT_BITS-1) ) );
        }
//        T1measLow();  // upto 50uS
        tmpIDCcoef = ntcCoef[ADC_POS_IDC];
        tmpIDCscaler = (float)tmpIDCcoef / COEF_MULTIPLIER;
        tmpIDCdeciValue = (ntcDeciValue[ADC_POS_IDC] * tmpIDCscaler);
        tmpIDCdeciValue += 0.5;
        SetValue_mbInputReg( MB_I_IDC, (uint16_t)tmpIDCdeciValue );
//        T2measLow();  // upto 55uS
    }
    
    if( true == bADCsamplesReady )
    {
        switch( ADC_CalcState )
        {
            case ADC_STA_AMB:
//                T1measHigh();  T2measHigh();
                mbNTChexVal = MCLIB_u16FilterAvg( ntcNoOffset[ADC_POS_AMB], &sNtc_ResultAvg[ADC_POS_AMB] );
                SetValue_mbInputReg( MB_I_NTC_AMB_HEX, mbNTChexVal );
//                T1measLow();  // upto ???uS
                ntcDeciValue[ADC_POS_AMB] = InterpNCP21XV103( mbNTChexVal );
//                T2measLow();  // upto ???uS
                tmpNTCcoef = ntcCoef[ADC_POS_AMB];
                tmpNTCscaler = (float)tmpNTCcoef / COEF_MULTIPLIER;
                tmpNTCdeciValue =  ntcDeciValue[ADC_POS_AMB] * tmpNTCscaler;
                SetValue_mbInputReg( MB_I_NTC_AMB, (uint16_t)tmpNTCdeciValue);
                ADC_CalcState = ADC_STA_HS;
                break;

            case ADC_STA_HS:
                mbNTChexVal = MCLIB_u16FilterAvg( ntcNoOffset[ADC_POS_HS], &sNtc_ResultAvg[ADC_POS_HS] );
                SetValue_mbInputReg( MB_I_NTC_HS_HEX, mbNTChexVal );
                ntcDeciValue[ADC_POS_HS] = InterpNCP21XV103( mbNTChexVal );
                tmpNTCcoef = ntcCoef[ADC_POS_HS];
                tmpNTCscaler = (float)tmpNTCcoef / COEF_MULTIPLIER;
                tmpNTCdeciValue =  ntcDeciValue[ADC_POS_HS] * tmpNTCscaler;
                SetValue_mbInputReg( MB_I_NTC_HS, (uint16_t)tmpNTCdeciValue);
                ADC_CalcState = ADC_STA_IND;
                break;

            case ADC_STA_IND:
                mbNTChexVal = MCLIB_u16FilterAvg( ntcNoOffset[ADC_POS_IND], &sNtc_ResultAvg[ADC_POS_IND] );
                SetValue_mbInputReg( MB_I_NTC_IND_HEX, mbNTChexVal );
                ntcDeciValue[ADC_POS_IND] = InterpNTCLE350E4103( mbNTChexVal );
                tmpNTCcoef = ntcCoef[ADC_POS_IND];
                tmpNTCscaler = (float)tmpNTCcoef / COEF_MULTIPLIER;
                tmpNTCdeciValue =  ntcDeciValue[ADC_POS_IND] * tmpNTCscaler;
                SetValue_mbInputReg( MB_I_NTC_IND, (uint16_t)tmpNTCdeciValue);
                ADC_CalcState = ADC_STA_EX24V;
                break;

            case ADC_STA_EX24V:
                mbNTChexVal = MCLIB_u16FilterAvg( ntcNoOffset[ADC_POS_EX24V], &sNtc_ResultAvg[ADC_POS_EX24V] );
                SetValue_mbInputReg( MB_I_EX24V_HEX, mbNTChexVal );
                ntcDeciValue[ADC_POS_EX24V] = (int16_t) ( (MCLIB_u32Mul_u16u16( mbNTChexVal, EX24_ADC_TO_DECI_VOLT_MULT ) >> ADC_RESULT_BITS ) );
                ntcDeciValue[ADC_POS_EX24V] += EX24_DIODE_DROP_DECI;
                tmpNTCcoef = ntcCoef[ADC_POS_EX24V];
                tmpNTCscaler = (float)tmpNTCcoef / COEF_MULTIPLIER;
                tmpNTCdeciValue =  ntcDeciValue[ADC_POS_EX24V] * tmpNTCscaler;
                SetValue_mbInputReg( MB_I_EX24V, (uint16_t)tmpNTCdeciValue);
                ADC_CalcState = ADC_STA_AMB;
                break;

            default: 
                ADC_CalcState = ADC_STA_AMB;
                break;
        }
    }
}
