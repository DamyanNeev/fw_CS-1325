/* *****************************************************************************
 * File:   TinyMClib.c
 * Author: Damyan Neev
 * Created on 2022 11 01
 *
 * Description: source file for tiny Math and Control Library.
 *      Device:  CS-1301_00  PIC16F1773
 *    Compiler:  XC8 v2.40   MPLAB X v6.00
 **************************************************************************** */



//===================================
// Header Includes
//===================================
#include "DBGmeasurements.h"
#include "TinyMClib.h"


//===================================
// Configuration Definitions
//===================================
#define USE_DIV_IN_U16_FILTER_AVG 0


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


//===================================
// Prototype of functions definitions
//===================================


//===================================
// Functions
//===================================


/* *****************************************************************************
 * MCLIB_u16FilterAvg
 * 
 * Description: Moving Average Filter of unsigned 16 bit input to 16 bit output
 *              u16NSamples means count samples to average
 **************************************************************************** */
void MCLIB_u16FilterAvgInit( uint16_t u16NSamples, MCLIB_sFilterAVGu16_t* psFilterMA )
{
    uint32_t u32ChangeMultiplier;   /* Q16_16 */
    
    if ((psFilterMA)->u16NSamples != u16NSamples)
    {
        u32ChangeMultiplier = MCLIB_u32Div_u32u16( (uint32_t)(u16NSamples) << 16, (psFilterMA)->u16NSamples );
        (psFilterMA)->u32Acc = (uint32_t) (MCLIB_s32Mul_s32u32((psFilterMA)->u32Acc, u32ChangeMultiplier));
        (psFilterMA)->u16NSamples = u16NSamples;
        (psFilterMA)->u32Mult = MCLIB_u32Div_u32u16( (uint32_t)UINT16_MAX+1, (psFilterMA)->u16NSamples );
    }
}

uint16_t MCLIB_u16FilterAvg( uint16_t u16Input, MCLIB_sFilterAVGu16_t* psFilterMA )
{
//    T1measHigh();
    
    uint16_t u16Output;
    uint32_t u32Acc;

    u32Acc = (psFilterMA)->u32Acc;

    u32Acc = MCLIB_u32AddSat_u32u32(u16Input, u32Acc);

    u16Output = MCLIB_u16Mul_u32u32(u32Acc, (psFilterMA)->u32Mult);

    u32Acc = MCLIB_u32SubSat_u32u32(u32Acc, (uint32_t)u16Output);

    (psFilterMA)->u32Acc = u32Acc;

//    T1measLow();//165us
    
    return u16Output;
}


/* *****************************************************************************
 * MCLIB_s16FilterAvg
 * 
 * Description: Moving Average Filter of signed 16 bit input to 16 bit output
 *              u16NSamples means count samples to average
 **************************************************************************** */

//void MCLIB_s16FilterAvgInit( uint16_t u16NSamples, MCLIB_sFilterAVGs16_t* psFilterMA)
//{
//    uint32_t u32ChangeMultiplier;   /* Q16_16 */
//    
//    if ((psFilterMA)->u16NSamples != u16NSamples)
//    {
//        //(psFilterMA)->u16NSamples >>= (psFilterMA)->u16NShift;
//        u32ChangeMultiplier = MCLIB_u32Div_u32u16( (uint32_t)(u16NSamples) << 16, (psFilterMA)->u16NSamples );
//        (psFilterMA)->s32Acc = MCLIB_s32Mul_s32u32((psFilterMA)->s32Acc, u32ChangeMultiplier);
//        (psFilterMA)->u16NSamples = u16NSamples;
//        //(psFilterMA)->u16NShift = 0;
//        (psFilterMA)->u32Mult = MCLIB_u32Div_u32u16( (uint32_t)UINT16_MAX+1, (psFilterMA)->u16NSamples );
//    }
//}

//int16_t MCLIB_s16FilterAvg( int16_t s16Input, MCLIB_sFilterAVGs16_t* psFilterMA)
//{
//    int16_t s16Output;
//    int32_t s32Acc;
//    
//    s32Acc = (psFilterMA)->s32Acc;
//
//    s32Acc = MCLIB_s32AddSat_s32s32(s16Input, s32Acc);
//
//    #if USE_DIV_IN_U16_FILTER_AVG
//    s16Output = MCLIB_s16Div_s32u16(s32Acc, (psFilterMA)->u16NSamples);
//    #else
//    s16Output = MCLIB_s16Mul_s32u32(s32Acc, (psFilterMA)->u32Mult);
//    #endif
//
//    s32Acc = MCLIB_s32SubSat_s32s32(s32Acc, s16Output);
//
//    (psFilterMA)->s32Acc = s32Acc;
//
//
//    return s16Output;
//}
