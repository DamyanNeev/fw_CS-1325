/* *****************************************************************************
 * File:   FlashStore.h
 * Author: Damyan Neev
 * Created on 2023 03 08
 *
 * Description: header file permanent storage of parameters.
 *      Device:  CS-1301_00  PIC16F1773
 *    Compiler:  XC8 v2.40   MPLAB X v6.00
 **************************************************************************** */


#ifndef FLASH_STORE_H
#define	FLASH_STORE_H


//===================================
// Header Includes
//===================================


//===================================   
// Configuration Definitions
//===================================


//===================================
// Constants and Macros Definitions
//===================================
#define EMPTY_FLASH  0x3FFF
//#define BYTE_SIZE        16
#define FLASH_BYTE_SIZE  14
#define MSB_BYTE_POS      8
#define MASK_16_MSB   0xC000

#define MASK_14_SIGN   0x2000
#define MASK_14_VALUE  0x1FFF


//===================================
// Enumeration Definitions
//===================================
typedef enum 
{
    FLASH_TRIP_DC_AMPERE,  // trip current on DClink
    FLASH_WARNING_EX24V,   // 24v supply warning
    FLASH_TRIP_AMB_TEMP,   // trip Ambient temperature
    FLASH_TRIP_HS_TEMP,    // trip Heat Sink temperature
    FLASH_TRIP_IND_TEMP,   // trip Inductor temperature
    FLASH_DEAD_TIME,       // dead time value
    FLASH_COEF_IDC,
        FLASH_0_7,
            
    FLASH_COEF_AMB,
    FLASH_COEF_HS,
    FLASH_COEF_IND,
    FLASH_OFFSET_IDC,
    FLASH_OFFSET_AMB,
    FLASH_OFFSET_HS,
    FLASH_OFFSET_IND,
        FLASH_8_14,

    FLASH_NU16,
    FLASH_NU17,
    FLASH_NU18,
    FLASH_NU19,
    FLASH_NU20,
    FLASH_NU21,
    FLASH_NU22,
        FLASH_16_22,

    FLASH_NU24,
    FLASH_NU25,
    FLASH_NU26,
    FLASH_NU27,
    FLASH_NU28,
    FLASH_NU29,
    FLASH_NU30,
        FLASH_24_30,

    FLASH_PARAM_COUNT   // 40001÷49999
}Flash_Params16_Position_t;


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
int8_t   ReadParams16_FlashBlock( void );
uint16_t Get_rdBlockData( uint8_t pos );
bool IsFlashEmpty( void );
void InitFlashBlockData( void );


void Update16_FlashBlock( Flash_Params16_Position_t pos, uint16_t fValue);


int8_t WriteFlashBlock( void );
int8_t EraseFlashBlock( void );



#ifdef	__cplusplus
extern "C" {
#endif // __cplusplus
    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 
#ifdef	__cplusplus
}
#endif // __cplusplus

#endif  // FLASH_STORE_H