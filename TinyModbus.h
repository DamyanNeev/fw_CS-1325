/* *****************************************************************************
 * File:   TinyModbus.h
 * Author: Damyan Neev
 * Created on 2023 11 01
 *
 * Description: header file for reduced ModBus commands.
 *      Device:  CS-1301_00  PIC16F1773
 *    Compiler:  XC8 v2.40   MPLAB X v6.00
 **************************************************************************** */


#ifndef TINNY_MODBUS_H
#define	TINNY_MODBUS_H


//===================================
// Header Includes
//===================================
#include "mcc_Files/adc.h"


//===================================   
// Configuration Definitions
//===================================


#define MB_COMMAND_LEN     8  //read Input regs + read/write Holding regs
//#define RESPONSE_DELAY     5
#define RESPONSE_DELAY     1
#define FRAME_TOUT_MS      2  // 115200 bauds char = 8.681uS  charNOK > 13.022uS  NewFrame > 30.384uS

/////////////////////////////////////////////
#define  DEFAULT_TRIP_DC_AMPERE  500
#define  TRIP_DC_AMPERE_MIN      100
#define  TRIP_DC_AMPERE_MAX     1000

#define  DEFAULT_TRIP_EX24V      199
#define  TRIP_EX24V_MIN          115
#define  TRIP_EX24V_MAX          310

/////////////////////////////////////////////
#define  DEFAULT_TRIP_AMB_TEMP    700
#define  TRIP_AMB_TEMP_MIN        200
#define  TRIP_AMB_TEMP_MAX       1250

#define  DEFAULT_TRIP_HS_TEMP     850
#define  TRIP_HS_TEMP_MIN         200
#define  TRIP_HS_TEMP_MAX        1250
         
#define  DEFAULT_TRIP_IND_TEMP   1050
#define  TRIP_IND_TEMP_MIN        200
#define  TRIP_IND_TEMP_MAX       1250
         
/////////////////////////////////////////////
#define  DEAD_TIME_DEFAULT       150
#define  DEAD_TIME_MIN             0
#define  DEAD_TIME_MAX           315
//#define  DEAD_TIME_MAX          1000  used to read dead time from internal registers register. Only lower 6 bits are stored in register

#define  CONTROL_START      1
#define  CONTROL_STOP       0

#define  ERASE_FLASH        2
#define  STORE_IN_FLASH     1
//#define  CALIBRATE_STOP     0

/////////////////////////////////////////////
#define  COEF_MULTIPLIER        1000

#define  COEF_IDC_DEFAULT       1000  //varry in both directions
#define  COEF_IDC_MIN            500
#define  COEF_IDC_MAX           2000

#define  COEF_AMB_DEFAULT       1000
#define  COEF_AMB_MIN            500
#define  COEF_AMB_MAX           2000

#define  COEF_HS_DEFAULT        1000
#define  COEF_HS_MIN             500
#define  COEF_HS_MAX            2000

#define  COEF_IND_DEFAULT       1000
#define  COEF_IND_MIN            500
#define  COEF_IND_MAX           2000

/////////////////////////////////////////////
#define  OFFSET_IDC_DEFAULT        0
#define  OFFSET_IDC_MAX          500
#define  OFFSET_IDC_MIN         -500

#define  OFFSET_AMB_DEFAULT        0
#define  OFFSET_AMB_MAX          500
#define  OFFSET_AMB_MIN         -500

#define  OFFSET_HS_DEFAULT         0
#define  OFFSET_HS_MAX           500
#define  OFFSET_HS_MIN          -500

#define  OFFSET_IND_DEFAULT        0
#define  OFFSET_IND_MAX          500
#define  OFFSET_IND_MIN         -500

/////////////////////////////////////////////


//===================================
// Constants and Macros Definitions
//===================================

//#define READ_COIL           0x01
//#define READ_IN_COIL        0x02
#define READ_HOLDING_REG    0x03
#define READ_IN_REG         0x04
//#define WRITE_COIL          0x05
#define WRITE_HOLDING_REG    0x06
//#define WRITE_MULTIPLE_REG  0x10
//#define WRITE_MULTIPLE_COIL 0x0F


#define  RECEIVE_REG_COUNT    128
#define  RESPONCE_REG_COUNT   2*MB_INPUT_REG_COUNT + 5



#define DATA_OK                 0x00
#define ILLEGAL_FUNCTION        0x01
#define ILLEGAL_DATA_ADDRESS    0x02
#define ILLEGAL_DATA_VALUE      0x03
#define SERVER_DEVICE_FAILURE   0x04
#define ILLEGAL_CHECK_SUM       0xFF

//===================================
// Enumeration Definitions
//===================================
typedef enum 
{
    MB_STA_IDLE,    
    MB_STA_RX_TOUT,
    MB_STA_RECEIVED,
    MB_STA_VERIFY_RECEIVED,
    MB_STA_DELAY,
    MB_STA_SEND,
    MB_STA_CLEAR_RECEIVED,
        
    MB_STATES_COUNT
}MB_State_t;


typedef enum 
{
    ERR_TRIP_DCLINK,     // 1 Err DC Link Trip Current
    ERR_WARNING_24V,     // 2 Err Warning 24 V supply
    ERR_AMB_TRIP_TEMP,   // 4 Err Ambient Trip Temperature
    ERR_HS_TRIP_TEMP,    // 8 Err HeatSink Trip Temperature
    ERR_IND_TRIP_TEMP,   //16 Err Inductor Trip Temperature
    ERR_iFLT_LOW,        //32 Err iFLT = Low
    ERR_iRDY_LOW,        //64 Err iRDY = Low
            
    ERR_STATUS_COUNT
}Err_ReadStatusRegs_t;


typedef enum 
{
    MB_H_TRIP_DC_AMPERE,  // trip current on DClink
    MB_H_WARNING_EX24V,   // 24v supply warning
    MB_H_TRIP_AMB_TEMP,   // trip Ambient temperature
    MB_H_TRIP_HS_TEMP,    // trip Heat Sink temperature
    MB_H_TRIP_IND_TEMP,   // trip Inductor temperature
    MB_H_DEAD_TIME,       // dead time value resolution 5ns
    MB_H_START,           // Software PWM Enable
    MB_H_FLASH_STORE,     // Store Coef and Offset values in flash
    MB_H_COEF_IDC,        //
    MB_H_COEF_AMB,        //
    MB_H_COEF_HS,         //
    MB_H_COEF_IND,        //
    MB_H_OFFSET_IDC,      //
    MB_H_OFFSET_AMB,      //
    MB_H_OFFSET_HS,       //
    MB_H_OFFSET_IND,      //
            
    MB_HOLDING_REG_COUNT   // 40001÷49999
}MB_HoldingRegs_t;


typedef enum 
{
    MB_I_DEVICE_ID,       // number of pcb
    MB_I_FW_VER,          // version of firmware
    MB_I_IDC,             // input current rms
    MB_I_IDC_HEX,         // hex value
    MB_I_NTC_AMB,         // in degree Celsius
    MB_I_NTC_HS,          // in degree Celsius
    MB_I_NTC_IND,         // in degree Celsius
    MB_I_NTC_AMB_HEX,     // hex value
    MB_I_NTC_HS_HEX,      // hex value HeatSink
    MB_I_NTC_IND_HEX,     // hex value Inductor
    MB_I_EX24V,           // power supply in deciVolts
    MB_I_EX24V_HEX,       // hex value power supply
    MB_I_ADDR_SWITCH,     //
    MB_I_STATUS,          // bit value for warnings and trips
    MB_I_DT1R,            // debug of DeadTime
    MB_I_DT1F,            // debug of DeadTime
    MB_I_DT2R,            // debug of DeadTime
    MB_I_DT2F,            // debug of DeadTime
    MB_I_DT3R,            // debug of DeadTime
    MB_I_DT3F,            // debug of DeadTime

    MB_INPUT_REG_COUNT     //30001÷39999
} MB_InputRegs_t;


typedef enum 
{
    TRIP_IDC_P_POS,
    TRIP_IDC_N_POS,
    TRIP_EX24V_P_POS,
    TRIP_EX24V_N_POS,
    TRIP_AMB_P_POS,  
    TRIP_AMB_N_POS,
    TRIP_HS_P_POS,
    TRIP_HS_N_POS,
    TRIP_IND_P_POS,
    TRIP_IND_N_POS,

    TRIP_POSITION_COUNT
} TripPositions_t;


//===================================
// Variables External Usage
//===================================

//extern volatile uint16_t  mbInputReg[MB_INPUT_REG_COUNT];


//===================================
// Function Prototypes
//===================================
uint16_t Get_controlValue( void );
uint16_t Get_storeFlashValue( void );
void Set_controlState( uint16_t state );

void SetValueInHoldingRegister( uint16_t addrHoldReg, uint16_t valHoldReg );

// Input registers
uint16_t GetValue_mbInputReg( uint16_t addrInputReg );
void     SetValue_mbInputReg( uint16_t addrInputReg, uint16_t valInReg );

// errors
void SetErr_MB_I_STATUS( Err_ReadStatusRegs_t err );
void ClearErr_MB_I_STATUS( Err_ReadStatusRegs_t err );

int16_t Get_tripValues( TripPositions_t pos );

void CheckUARTbuf( void );
void vModBusProcess( void );
void InitModbusRegisters( void );

void vUpdateMbRegsProcess( void );




#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif  // TINNY_MODBUS_H