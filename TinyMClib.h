/* *****************************************************************************
 * File:   TinyMClib.h
 * Author: Damyan Neev
 * Created on 2022 11 01
 *
 * Description: header file for tiny Math and Control Library.
 *      Device:  CS-1301_00  PIC16F1773
 *    Compiler:  XC8 v2.40   MPLAB X v6.00
 **************************************************************************** */


#ifndef TINY_MCLIB_H
#define	TINY_MCLIB_H


//===================================
// Header Includes
//===================================
#include <stdint.h>


//===================================   
// Configuration Definitions
//===================================


//===================================
// Constants and Macros Definitions
//===================================
#define  FRACT16_MAX (0.999969482421875)                 /* (2^15-1)/2^15 */
#define  FRACT16_MIN (-1.0)

#define  FRACT32_MAX (0.9999999995343387126922607421875) /* (2^31-1)/2^31 */
#define  FRACT32_MIN (-1.0)

#define UFRACT16_MAX (0.9999847412109375)               /* (2^16-1)/2^16 */
#define UFRACT16_MIN (0)

#define UFRACT32_MAX (0.99999999976716935634613037109375) /* (2^32-1)/2^32 */
#define UFRACT32_MIN (0)

#define UFRACTQ_16_16_MAX (65535.9999847412109375)  /* (2^32-1)/2^16 */

#define  FRACTQ_15_16_MAX (32767.9999847412109375)  /* (2^31-1)/2^16 */
#define  FRACTQ_15_16_MIN (-32768)  /* (2^31)/2^16 */


//===================================
// Enumeration Definitions
//===================================


//===================================
// Type Definitions
//===================================
typedef struct
{
    uint32_t u32Acc;
    uint16_t u16NSamples;
    uint16_t u16NShift;
    uint32_t u32Mult;       /* Q16_16 Format of 1/u16NSamples */
} MCLIB_sFilterAVGu16_t;

//typedef struct
//{
//     int32_t s32Acc;
//    uint16_t u16NSamples;
//    uint16_t u16NShift;
//    uint32_t u32Mult;       /* Q16_16 Format of 1/u16NSamples */
//} MCLIB_sFilterAVGs16_t;


//===================================
// Function-Like Macro
//===================================

/* *****************************************************************************
 * MCLIB_s16d
 * Description: signed 16 bit convert to deci-Degrees, Amperes, ... variable resolution
 **************************************************************************** */
#define MCLIB_s16d(x)   (int16_t)(10.0F * x)   /* dA(0.1A), dV(0.1V), dHz(0.1Hz) */
#define MCLIB_rToDeci(x)    (10.0F * x)   /* dA(0.1A), dV(0.1V), dHz(0.1Hz) */

/* *****************************************************************************
 * MCLIB_u16Fractional 
 * Description: unsigned 16 bit fractional [0..1] representation
 **************************************************************************** */
#define MCLIB_u16Fractional(fltValue)    \
    ((uint16_t) (((fltValue) < UFRACT16_MAX) \
        ? (((fltValue) >= 0) \
            ? ((uint16_t) ((fltValue)*65536.0F + 0.5F)) \
            : (uint16_t)0) \
        : (uint16_t)UINT16_MAX))

#define MCLIB_u16Fractional_XC8(fltValue)    \
    ((uint16_t) ((fltValue)*65536.0F + 0.5F)) 

/* *****************************************************************************
 * MCLIB_u32AddSat_u32u32 
 * Description: unsigned 32 bit add with saturation
 **************************************************************************** */
#define MCLIB_u32AddSat_u32u32(u32Input1, u32Input2)    \
    ((uint32_t)(u32Input1 + u32Input2) < (uint32_t)u32Input1) \
        ? UINT32_MAX \
        : (uint32_t)(u32Input1 + u32Input2)

/* *****************************************************************************
 * MCLIB_u32SubSat_u32u32 
 * Description: unsigned 32 bit sub with saturation
 **************************************************************************** */
#define MCLIB_u32SubSat_u32u32(u32Input1, u32Input2)    \
    ((uint32_t)(u32Input1 - u32Input2) > (uint32_t)u32Input1) \
        ? 0 \
        : (uint32_t)(u32Input1 - u32Input2)

/* *****************************************************************************
 * MCLIB_u32Div_u32u16
 * Description: unsigned 32 bit div with 16 bit unsigned output
 **************************************************************************** */
#define MCLIB_u32Div_u32u16(u32Input1, u16Input2)    \
    (uint32_t)((uint32_t)(u32Input1)/(u16Input2))

/* *****************************************************************************
 * MCLIB_s32Mul_s32u32 - -needs improvement to check overflow
 * Input1 - signed 32 bit fractional [-32768..32767.9999] Q_15_16
 * Input2 - unsigned 32 bit fractional [0..65535.9999] Q_16_16
 * Output - signed 32 bit fractional [-32768..32767.9999] Q_15_16
 * Description: signed 16 bit mul with 32 bit u32 Q_16_16 format. 
 *              Result is signed 16 bit output 
 **************************************************************************** */
#define MCLIB_s32Mul_s32u32(s32Input1_Q_15_16, u32Input2_Q_16_16) \
        (int32_t)((((int64_t)(s32Input1_Q_15_16) * (u32Input2_Q_16_16)) + \
        MCLIB_u16Fractional_XC8(0.5)) >> 16)

#define MCLIB_s16Mul_s32u32(s32Input1_Q_15_16, u32Input2_Q_16_16) \
        (int16_t)((((int64_t)(s32Input1_Q_15_16) * (u32Input2_Q_16_16)) + \
        MCLIB_u16Fractional_XC8(0.5)) >> 16)

/* *****************************************************************************
 * MCLIB_u32Mul_u32u32 - -needs improvement to check overflow
 * Input1 - unsigned 32 bit fractional [0..65535.9999] Q_16_16
 * Input2 - unsigned 32 bit fractional [0..65535.9999] Q_16_16
 * Output - unsigned 32 bit fractional [0..65535.9999] Q_16_16
 * Description: unsigned u32 Q_16_16 format mul with u32 Q_16_16 format. 
 *              Result is unsigned 32 bit u32 Q_16_16 format output 
 **************************************************************************** */
#define MCLIB_u32Mul_u32u32(u32Input1_Q_16_16, u32Input2_Q_16_16) \
        (uint32_t)((((uint64_t)(u32Input1_Q_16_16) * (u32Input2_Q_16_16)) + \
        MCLIB_u16Fractional(0.5)) >> 16)

#define MCLIB_u16Mul_u32u32(u32Input1_Q_16_16, u32Input2_Q_16_16) \
        (uint16_t)((((uint64_t)(u32Input1_Q_16_16) * (u32Input2_Q_16_16)) + \
        MCLIB_u16Fractional_XC8(0.5)) >> 16)




/* *****************************************************************************
 * MCLIB_s16Mul_s16u16 
 * Description: signed and unsigned 16 bit mul with round
 **************************************************************************** */
#define MCLIB_s16Mul_s16u16(s16Input1, u16Input2)    \
    (int16_t)((int32_t)(((int32_t)(s16Input1) * (u16Input2))+ MCLIB_u16Fractional(0.5)) >> 16)



/* *****************************************************************************
 * MCLIB_u16Mul_u16u16
 * 
 * Input1,Input2 - unsigned fractional[0..1] or unsigned int[0..65535]
 * Output - unsigned fractional[0..1] or unsigned int[0..65535]
 * 
 * Description: signed 16 bit mul with 32 bit u32 Q_16_16 format. 
 *              Result is signed 16 bit output 
 **************************************************************************** */
#ifdef __XC16
#define MCLIB_u16Mul_u16u16(u16Input1, u16Input2) \
        (uint16_t)((__builtin_muluu(u16Input1, u16Input2) + \
        MCLIB_u16Fractional(0.5))>>16)
#else
#define MCLIB_u16Mul_u16u16(u16Input1, u16Input2) \
        (uint16_t)((((uint32_t)(u16Input1) * (u16Input2)) + \
        MCLIB_u16Fractional(0.5))>>16)
#endif
#define MCLIB_u16Mul_u16u16Std(u16Input1, u16Input2) \
        (uint16_t)((((uint32_t)(u16Input1) * (u16Input2)) + \
        MCLIB_u16Fractional(0.5))>>16)



/* *****************************************************************************
 * MCLIB_u32Mul_u16u16
 * Description: unsigned 16 bit mul with 32 bit unsigned output 
 **************************************************************************** */
/* Function below not checked used in interpolation */
#ifdef __XC16
#define MCLIB_u32Mul_u16u16(u16Input1, u16Input2) \
    __builtin_muluu(u16Input1, u16Input2)
#else
#define MCLIB_u32Mul_u16u16(u16Input1, u16Input2)    \
    (uint32_t)((uint32_t)(u16Input1)*(u16Input2))
#endif


/* *****************************************************************************
 * MCLIB_s32AddSat_s32s32 
 * 
 * Description: signed 32 bit add with saturation
 **************************************************************************** */
#define MCLIB_s32AddSat_s32s32(s32Input1, s32Input2)    \
    (((int32_t)s32Input1 > 0) && ((int32_t)s32Input2 > 0) \
        && ((int32_t)(s32Input1 + s32Input2) < 0))\
            ? INT32_MAX \
            : (((int32_t)s32Input1 < 0) && ((int32_t)s32Input2 < 0) \
                && ((int32_t)(s32Input1 + s32Input2) > 0))\
                    ? INT32_MIN \
                    : (int32_t)(s32Input1 + s32Input2)

/* *****************************************************************************
 * MCLIB_s32SubSat_s32s32 
 * 
 * Description: signed 32 bit sub with saturation
 **************************************************************************** */
#define MCLIB_s32SubSat_s32s32(s32Input1, s32Input2)    \
    (((int32_t)s32Input1 > 0) && ((int32_t)s32Input2 < 0) \
        && ((int32_t)(s32Input1 - s32Input2) < 0))\
            ? INT32_MAX \
            : (((int32_t)s32Input1 < 0) && ((int32_t)s32Input2 > 0) \
                && ((int32_t)(s32Input1 - s32Input2) > 0))\
                    ? INT32_MIN \
                    : (int32_t)(s32Input1 - s32Input2)


//===================================
// Variables External Usage
//===================================


//===================================
// Function Prototypes
//===================================
void MCLIB_u16FilterAvgInit( uint16_t u16NSamples, MCLIB_sFilterAVGu16_t* psFilterMA );
uint16_t MCLIB_u16FilterAvg( uint16_t u16Input, MCLIB_sFilterAVGu16_t* psFilterMA );

//void MCLIB_s16FilterAvgInit( uint16_t u16NSamples, MCLIB_sFilterAVGs16_t* psFilterMA);
//int16_t MCLIB_s16FilterAvg( int16_t s16Input, MCLIB_sFilterAVGs16_t* psFilterMA);



#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus
     // TODO If C++ is being used, regular C code needs function names to have C 
     // linkage so the functions can be used by the c code. 
#ifdef __cplusplus
}
#endif // __cplusplus

#endif	/* TINY_MCLIB_H */
