/* *****************************************************************************
 * File:   FlashStore.c
 * Author: Damyan Neev
 * Created on 2023 03 08
 *
 * Description: source file permanent storage of parameters.
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

#include "DBGmeasurements.h"
#include "FlashStore.h"
#include "TinyModbus.h"


//===================================
// Configuration Definitions
//===================================


//===================================
// Constants and Macros Definitions
//===================================
//#define FLASH_ROW4_ADDRESS     0x3F80

#define FLASH_ROW1_ADDRESS    0x3F80
#define FLASH_ROW2_ADDRESS    0x3FA0
#define FLASH_ROW3_ADDRESS    0x3FC0
#define FLASH_ROW4_ADDRESS    0x3FE0

#define FLASH_BLOCK_SIZE    32
//#define BLOCK_SIZE_U16      28

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
uint16_t flashBlock14bitData[FLASH_BLOCK_SIZE];

uint16_t wrBlockData[FLASH_BLOCK_SIZE] = 
{
    0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007,
    0x0008, 0x0009, 0x000A, 0x000B, 0x000C, 0x000D, 0x000E, 0x000F,
    0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017,
    0x0018, 0x0019, 0x001A, 0x001B, 0x001C, 0x001D, 0x001E, 0x001F
};

uint16_t flashBlockData[FLASH_BLOCK_SIZE] = 
{
    0xFEDC, 0xFEDC, 0xFEDC, 0xFEDC, 0xFEDC, 0xFEDC, 0xFEDC, 0xFEDC,
    0x0028, 0x0029, 0x002A, 0x002B, 0x002C, 0x002D, 0x002E, 0x002F,
    0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037,
    0x0038, 0x0039, 0x003A, 0x003B, 0x003C, 0x003D, 0x003E, 0x003F
};




//===================================
// Prototype of functions definitions
//===================================


//===================================
// Functions
//===================================

uint16_t Get_rdBlockData( uint8_t pos )
{
    return flashBlockData[pos];
}


bool IsFlashEmpty( void )
{
    bool empty = true;
    int n;
    
    for( n = 0; n < FLASH_BLOCK_SIZE; n++ )
    {
        if( flashBlock14bitData[n] != EMPTY_FLASH )
        {
            return false;
        }
    }
    return empty;
}


void InitFlashBlockData( void )
{
    flashBlockData[FLASH_TRIP_DC_AMPERE] = DEFAULT_TRIP_DC_AMPERE;
    flashBlockData[FLASH_WARNING_EX24V]  = DEFAULT_TRIP_EX24V;
    flashBlockData[FLASH_TRIP_AMB_TEMP]  = DEFAULT_TRIP_AMB_TEMP;
    flashBlockData[FLASH_TRIP_HS_TEMP]   = DEFAULT_TRIP_HS_TEMP;
    flashBlockData[FLASH_TRIP_IND_TEMP]  = DEFAULT_TRIP_IND_TEMP;
    flashBlockData[FLASH_DEAD_TIME]      = DEAD_TIME_DEFAULT;
    flashBlockData[FLASH_COEF_IDC]       = COEF_IDC_DEFAULT;
    flashBlockData[FLASH_0_7]            = 0x0000;
            
    flashBlockData[FLASH_COEF_AMB]       = COEF_AMB_DEFAULT;
    flashBlockData[FLASH_COEF_HS]        = COEF_HS_DEFAULT;
    flashBlockData[FLASH_COEF_IND]       = COEF_IND_DEFAULT;
    flashBlockData[FLASH_OFFSET_IDC]     = OFFSET_IDC_DEFAULT;
    flashBlockData[FLASH_OFFSET_AMB]     = OFFSET_AMB_DEFAULT;
    flashBlockData[FLASH_OFFSET_HS]      = OFFSET_HS_DEFAULT;
    flashBlockData[FLASH_OFFSET_IND]     = OFFSET_IND_DEFAULT;
    flashBlockData[FLASH_8_14]           = 0x0000;
}


int8_t ReadParams16_FlashBlock( void )
{
//    Flash1High();
    uint16_t n;
    uint16_t adr;
    int8_t   bErrorWrite = false;
    uint16_t ind;
    uint16_t msbShift;
    uint16_t mask;
    uint16_t msb_14bitVal;
    uint16_t msb_16bitVal;
    uint16_t f_16bitVal;
    
    for ( n = 0; n < FLASH_BLOCK_SIZE; n++ )
    {
        adr = (uint16_t) ( FLASH_ROW4_ADDRESS + n );
//        __delay_us(1);
        flashBlock14bitData[n] = FLASH_ReadWord( adr );
//        __delay_us(10);
    }
    
    for ( n = 0; n < (FLASH_BLOCK_SIZE-1); n++ )
    {
        if( !((n+1) % MSB_BYTE_POS) & (n!=0) )
        {
            n++;
        }
        ind = (MSB_BYTE_POS-1) * ( (n+1)/MSB_BYTE_POS + 1) + 1*(n)/MSB_BYTE_POS;
        msb_14bitVal = flashBlock14bitData[ind];
        
        msbShift = (n % MSB_BYTE_POS);
        mask = (MASK_16_MSB >> (FLASH_BYTE_SIZE - msbShift*2));
        
        msb_14bitVal = msb_14bitVal & mask;
        msb_16bitVal = (msb_14bitVal << (FLASH_BYTE_SIZE - msbShift*2));
        
        f_16bitVal = flashBlock14bitData[n] + msb_16bitVal;
        
        flashBlockData[n] = f_16bitVal;
    }
//    Flash1Low();
            
    return bErrorWrite;
}


void Update16_FlashBlock( Flash_Params16_Position_t pos, uint16_t fValue)
{
    uint16_t msb_fValue;
    uint16_t mask;
    uint16_t ind;
    uint16_t msbShift;
    uint16_t fValue_ToWrite;
    
    wrBlockData[pos] = fValue;  // loose 2 msb
    
    msbShift = (pos % MSB_BYTE_POS);
    msb_fValue = (fValue & MASK_16_MSB) >> (FLASH_BYTE_SIZE - msbShift*2);
    
    ind = (MSB_BYTE_POS-1) * ( (pos+1)/MSB_BYTE_POS + 1) + 1*(pos)/MSB_BYTE_POS;
    mask = ~(MASK_16_MSB >> (FLASH_BYTE_SIZE - msbShift*2));
    
    fValue_ToWrite = wrBlockData[ind] & mask;
    fValue_ToWrite += msb_fValue;
    
    wrBlockData[ind] = fValue_ToWrite;
}


int8_t EraseFlashBlock( void )
{
    int8_t bErrorWrite = false;
    
    FLASH_EraseBlock( (uint16_t)FLASH_ROW4_ADDRESS );
    
    return bErrorWrite;
}


int8_t WriteFlashBlock( void )
{
    int8_t bErrorWrite = false;
    
    bErrorWrite = FLASH_WriteBlock((uint16_t)FLASH_ROW4_ADDRESS, (uint16_t*)wrBlockData);
    
    return bErrorWrite;
}