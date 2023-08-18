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

#include "ADCmeasure.h"
#include "BoardConfig.h"
#include "DBGmeasurements.h"
#include "FlashStore.h"
#include "IOpins.h"
#include "Timers.h"
#include "TinyModbus.h"


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
// Function-Like Macros
//===================================
#define CHECK_BIT(var,pos) !!((var) & (1 << (pos)))


//===================================
// Variables Definitions
//===================================

volatile  uint8_t  SlaveAddress ;

volatile uint16_t  mbHoldingReg[MB_HOLDING_REG_COUNT];
volatile uint16_t  mbInputReg[MB_INPUT_REG_COUNT];
//
volatile  int16_t tripValues[TRIP_POSITION_COUNT];

//volatile  int16_t dcAmpereTripValueP;
//volatile  int16_t dcAmpereTripValueN;
//volatile uint16_t ex24vWarnValue;
//
//volatile uint16_t tempTripAMBvalue;
//volatile uint16_t tempTripHSvalue;
//volatile uint16_t tempTripINDvalue;
//
volatile uint8_t  deadTimeValue;


//
volatile uint16_t controlValue;
volatile uint16_t controlState;
//
volatile uint16_t storeFlashValue;  //alibrateValue;

uint8_t  uartReceived[RECEIVE_REG_COUNT];
uint8_t  uartToSend[RESPONCE_REG_COUNT];

        
uint8_t  ModbusRXPos = 0;
uint8_t  nResponseBytes = 0;
bool  bCheckRxBuff  = false;
bool  bHoldingRegNewValue = false;


MB_State_t mbState = MB_STA_IDLE;


uint64_t rxToutLastTimeMs  = 0;
uint64_t adcReadLastTimeMs = 0;
uint64_t idcReadLastTimeMs = 0;


//===================================
// Prototype of functions definitions
//===================================


//===================================
// Functions
//===================================

int16_t Get_tripValues( TripPositions_t pos )
{
    return tripValues[pos];
}


uint16_t Get_storeFlashValue( void )
{
    return storeFlashValue;
}

void Clear_storeFlashValue( void )
{
    storeFlashValue = 0x000;
    mbHoldingReg[MB_H_FLASH_STORE] = 0x0000;
}

uint16_t Get_controlValue( void )
{
    return controlValue;
}

void Set_controlState( uint16_t state )
{
    controlState = state;
}



//uint16_t GetValue_mbHoldingReg( uint16_t addrHoldingReg )
//{
//    return mbHoldingReg[addrHoldingReg];
//}

//void SetValueInHoldingRegister( uint16_t addrHoldReg, uint16_t valHoldReg )
//{
//    mbHoldingReg[addrHoldReg]  = valHoldReg;
//}

// Input registers
//uint16_t GetValue_mbInputReg( uint16_t addrInputReg )
//{
//    return mbInputReg[addrInputReg];
//}

void SetValue_mbInputReg( uint16_t addrInputReg, uint16_t valInputReg )
{
    mbInputReg[addrInputReg]  = valInputReg;
}

// errors
void SetErr_MB_I_STATUS( Err_ReadStatusRegs_t err )
{
    Err_ReadStatusRegs_t tmperr = err;
    
    mbInputReg[MB_I_STATUS] |= 1UL << err;  // Set bit
    
//    mbInputReg[MB_I_DT1R]    = mbInputReg[MB_I_STATUS];  // Set bit
//    mbInputReg[MB_I_DT1F]   += 1;
//    mbInputReg[MB_I_DT2R]   |= 1UL << tmperr;
}

void ClearErr_MB_I_STATUS( Err_ReadStatusRegs_t err )
{
    mbInputReg[MB_I_STATUS] &= ~(1UL << err);  // Clear bit
}


void InitModbusRegisters( void )
{
    SlaveAddress = SLAVE_ADDR;
    CheckRotaryValue();
    SlaveAddress = Get_RotaryValue();

    mbInputReg[MB_I_DEVICE_ID]   = DEVICE_ID;
    mbInputReg[MB_I_FW_VER]      = FW_VERSION_ID;
    mbInputReg[MB_I_IDC]         =     0;  // DC current in deciAmpere
    mbInputReg[MB_I_IDC_HEX]     =   512;  // raw value of DC current
    mbInputReg[MB_I_NTC_AMB]     =   250;  // ambient temperature in deci°C
    mbInputReg[MB_I_NTC_HS]      =   251;  // heat sink temperature in deci°C
    mbInputReg[MB_I_NTC_IND]     =   252;  // inductor temperature in deci°C
    mbInputReg[MB_I_NTC_AMB_HEX] =   510;  // raw value of ambient temperature i
    mbInputReg[MB_I_NTC_HS_HEX]  =   511;  // raw value of heat sink temperature
    mbInputReg[MB_I_NTC_IND_HEX] =   512;  // raw value of inductor temperature 
    mbInputReg[MB_I_EX24V]       =   240;  // 24V power supply in deciVolt
    mbInputReg[MB_I_EX24V_HEX]   =   785;  // raw value of 24V power supply
    mbInputReg[MB_I_ADDR_SWITCH] = SlaveAddress;
    mbInputReg[MB_I_STATUS]      = 0x0000; //no errors
    mbInputReg[MB_I_DT1R]        = 0x0000;  // debug1
    mbInputReg[MB_I_DT1F]        = 0x0000;  // debug2
    mbInputReg[MB_I_DT2R]        = 0x0000;  // debug3
    mbInputReg[MB_I_DT2F]        =  1004;  // debug4
    mbInputReg[MB_I_DT3R]        =  1005;  // debug5
    mbInputReg[MB_I_DT3F]        =  1006;  // debug6
    
    ReadParams16_FlashBlock();
    
    if( IsFlashEmpty() )
    {
        mbHoldingReg[MB_H_TRIP_DC_AMPERE] = DEFAULT_TRIP_DC_AMPERE;
        mbHoldingReg[MB_H_WARNING_EX24V]  = DEFAULT_TRIP_EX24V;
        mbHoldingReg[MB_H_TRIP_AMB_TEMP]  = DEFAULT_TRIP_AMB_TEMP;
        mbHoldingReg[MB_H_TRIP_HS_TEMP]   = DEFAULT_TRIP_HS_TEMP;
        mbHoldingReg[MB_H_TRIP_IND_TEMP]  = DEFAULT_TRIP_IND_TEMP;
        mbHoldingReg[MB_H_DEAD_TIME]      = DEAD_TIME_DEFAULT;
        mbHoldingReg[MB_H_COEF_IDC]       = COEF_IDC_DEFAULT;
        mbHoldingReg[MB_H_COEF_AMB]       = COEF_AMB_DEFAULT;
        mbHoldingReg[MB_H_COEF_HS]        = COEF_HS_DEFAULT;
        mbHoldingReg[MB_H_COEF_IND]       = COEF_IND_DEFAULT;
        mbHoldingReg[MB_H_OFFSET_IDC]     = OFFSET_IDC_DEFAULT;
        mbHoldingReg[MB_H_OFFSET_AMB]     = OFFSET_AMB_DEFAULT;
        mbHoldingReg[MB_H_OFFSET_HS]      = OFFSET_HS_DEFAULT;
        mbHoldingReg[MB_H_OFFSET_IND]     = OFFSET_IND_DEFAULT;
        InitFlashBlockData();
    }
    else
    {
        mbHoldingReg[MB_H_TRIP_DC_AMPERE] = Get_rdBlockData( FLASH_TRIP_DC_AMPERE );
        mbHoldingReg[MB_H_WARNING_EX24V]  = Get_rdBlockData( FLASH_WARNING_EX24V  );
        mbHoldingReg[MB_H_TRIP_AMB_TEMP]  = Get_rdBlockData( FLASH_TRIP_AMB_TEMP  );
        mbHoldingReg[MB_H_TRIP_HS_TEMP]   = Get_rdBlockData( FLASH_TRIP_HS_TEMP   );
        mbHoldingReg[MB_H_TRIP_IND_TEMP]  = Get_rdBlockData( FLASH_TRIP_IND_TEMP  );
        mbHoldingReg[MB_H_DEAD_TIME]      = Get_rdBlockData( FLASH_DEAD_TIME      );
        mbHoldingReg[MB_H_COEF_IDC]       = Get_rdBlockData( FLASH_COEF_IDC       );
        mbHoldingReg[MB_H_COEF_AMB]       = Get_rdBlockData( FLASH_COEF_AMB       );
        mbHoldingReg[MB_H_COEF_HS]        = Get_rdBlockData( FLASH_COEF_HS        );
        mbHoldingReg[MB_H_COEF_IND]       = Get_rdBlockData( FLASH_COEF_IND       );
        mbHoldingReg[MB_H_OFFSET_IDC]     = Get_rdBlockData( FLASH_OFFSET_IDC     );
        mbHoldingReg[MB_H_OFFSET_AMB]     = Get_rdBlockData( FLASH_OFFSET_AMB     );
        mbHoldingReg[MB_H_OFFSET_HS]      = Get_rdBlockData( FLASH_OFFSET_HS      );
        mbHoldingReg[MB_H_OFFSET_IND]     = Get_rdBlockData( FLASH_OFFSET_IND     );
    }
    
    mbHoldingReg[MB_H_START]          = 0x0000;  // stop
    mbHoldingReg[MB_H_FLASH_STORE]    = 0x0000;  // No calibrate

//    controlValue       = mbHoldingReg[MB_H_START];
    controlValue       = CONTROL_START;

    storeFlashValue    = mbHoldingReg[MB_H_FLASH_STORE];
    deadTimeValue      = (uint8_t) (mbHoldingReg[MB_H_DEAD_TIME] / 5);
    
    tripValues[TRIP_IDC_P_POS] = (int16_t)mbHoldingReg[MB_H_TRIP_DC_AMPERE];
    tripValues[TRIP_IDC_N_POS] = 0 - tripValues[TRIP_IDC_P_POS];
    tripValues[TRIP_EX24V_P_POS]    = (int16_t)mbHoldingReg[MB_H_WARNING_EX24V];
    tripValues[TRIP_AMB_P_POS] = (int16_t)mbHoldingReg[MB_H_TRIP_AMB_TEMP];
    tripValues[TRIP_HS_P_POS]  = (int16_t)mbHoldingReg[MB_H_TRIP_HS_TEMP];
    tripValues[TRIP_IND_P_POS] = (int16_t)mbHoldingReg[MB_H_TRIP_IND_TEMP];
    
    Set_ntcCoef( ADC_POS_IDC, mbHoldingReg[MB_H_COEF_IDC] );
    Set_ntcCoef( ADC_POS_AMB, mbHoldingReg[MB_H_COEF_AMB] );
    Set_ntcCoef( ADC_POS_HS,  mbHoldingReg[MB_H_COEF_HS]  );
    Set_ntcCoef( ADC_POS_IND, mbHoldingReg[MB_H_COEF_IND] );
    
    // Don't know when the current is ZERO !!!
//    int16_t tmpOffset = GetIDCoffset();
//    mbInputReg[MB_I_DT1R] = (uint16_t)tmpOffset;
    
    Set_ntcOffset( ADC_POS_IDC, (int16_t)mbHoldingReg[MB_H_OFFSET_IDC] );
    Set_ntcOffset( ADC_POS_AMB, (int16_t)mbHoldingReg[MB_H_OFFSET_AMB] );
    Set_ntcOffset( ADC_POS_HS,  (int16_t)mbHoldingReg[MB_H_OFFSET_HS]  );
    Set_ntcOffset( ADC_POS_IND, (int16_t)mbHoldingReg[MB_H_OFFSET_IND] );
}


uint16_t GenerateCRC( uint8_t messageLength )
{
//    T2measHigh();
    uint16_t crc = 0xFFFF;
    uint16_t crcHigh = 0;
    uint16_t crcLow = 0;
    uint8_t k, n;

    for ( k = 0; k < messageLength - 2; k++ )
    {
        crc ^= uartToSend[k];
        for ( n = 8; n != 0; n-- )
        {
            if ( (crc & 0x0001) != 0 )
            {
                crc >>= 1;
                crc ^= 0xA001;
            }
            else
            {
                crc >>= 1;
            }
        }
    }
    //bytes are wrong way round so doing a swap here..
    crcHigh = (crc & 0x00FF) << 8;
    crcLow = (crc & 0xFF00) >> 8;
    crcHigh |= crcLow;
    crc = crcHigh;
//    T2measLow();  //94us
    
    return crc;
}

uint8_t CheckCRC( void )
{
//    T1measHigh();
    uint16_t crc = 0xFFFF;
    uint16_t crcHigh = 0;
    uint16_t crcLow  = 0;
    int k, n;

    for( k = 0; k < (MB_COMMAND_LEN - 2); k++ )
    {
        crc ^= uartReceived[k];
        for ( n = MB_COMMAND_LEN; n != 0; n-- )
        {
            if ( (crc & 0x0001) != 0 )
            {
                crc >>= 1;
                crc ^= 0xA001;
            }
            else
            {
                crc >>= 1;
            }
        }
    }
    //bytes are wrong way round so doing a swap here..
    crcHigh = (crc & 0x00FF);
    crcLow  = (crc & 0xFF00) >> 8;
//    T1measLow();  //184us
    
    if( (crcHigh == uartReceived[k]) && (crcLow == uartReceived[k + 1]) )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


void ReadInputRegister( void )
{
//    T1measHigh();  T2measHigh();
    uint8_t  rr_Address8 = 0;
    uint8_t  rr_numRegs8 = 0;
    uint16_t crc = 0;
    uint16_t k = 0;
    uint8_t  n = 3;

    //Get 8-bit address instead 16-bit
    rr_Address8 = uartReceived[3];
    //Get 8-bit number of registers instead 16-bit
    rr_numRegs8 = uartReceived[5];
    
    uartToSend[0] = SlaveAddress;
    if ( (rr_Address8 <= MB_INPUT_REG_COUNT) && (rr_numRegs8 <= (MB_INPUT_REG_COUNT - rr_Address8)) )
    {
        uartToSend[1] = READ_IN_REG;
        uartToSend[2] = (uint8_t) (rr_numRegs8 * 2); //2 bytes per register

        for ( k = rr_Address8; k < (rr_Address8 + rr_numRegs8); k++ )
        {
            if ( mbInputReg[k] > 255 )
            {
                //Need to split it up into 2 bytes
                uartToSend[n] = mbInputReg[k] >> 8;
                n++;
                uartToSend[n] = (uint8_t) mbInputReg[k];
                n++;
            }
            else
            {
                uartToSend[n] = 0x00;
                n++;
                uartToSend[n] = (uint8_t) mbInputReg[k];
                n++;
            }
        }
    }
    else
    {
        uartToSend[1] = READ_IN_REG | 0x80;
        uartToSend[2] = 0x02;  //object address is not valid for the Slave.
        n = 3;
    }
//    T2measLow();  //28uS for one register

    crc = GenerateCRC( n + 2 );
    uartToSend[n] = crc >> 8;
    n++;
    uartToSend[n] = (uint8_t) crc;
    n += 2;
    
    nResponseBytes = n;
//    T1measLow();  //170uS for one register
}


void ReadHoldingRegister( void )
{
//    T1measHigh();  T2measHigh();
    
    uint8_t  rr_Address8 = 0;
    uint8_t  rr_numRegs8 = 0;
    uint16_t crc = 0;
    uint16_t k = 0;
    uint8_t  n = 3;

    //Get 8-bit address instead 16-bit
    rr_Address8 = uartReceived[3];
    //Get 8-bit number of registers instead 16-bit
    rr_numRegs8 = uartReceived[5];
    
    uartToSend[0] = SlaveAddress;
    if ( (rr_Address8 <= MB_HOLDING_REG_COUNT) && rr_numRegs8 <= (MB_HOLDING_REG_COUNT - rr_Address8) )
    {
        uartToSend[1] = READ_HOLDING_REG;
        uartToSend[2] = (uint8_t) (rr_numRegs8 * 2); //2 bytes per register

        mbHoldingReg[MB_H_START] = controlState;
        
        for ( k = rr_Address8; k < (rr_Address8 + rr_numRegs8); k++ )
        {
            if ( mbHoldingReg[k] > 255 )
            {
                //Need to split it up into 2 bytes
                uartToSend[n] = mbHoldingReg[k] >> 8;
                n++;
                uartToSend[n] = (uint8_t) mbHoldingReg[k];
                n++;
            }
            else
            {
                uartToSend[n] = 0x00;
                n++;
                uartToSend[n] = (uint8_t) mbHoldingReg[k];
                n++;
            }
        }
    }
    else
    {
        uartToSend[1] = READ_HOLDING_REG | 0x80;
        uartToSend[2] = 0x02;  //object address is not valid for the Slave.
        n = 3;
    }
//    T2measLow();  //28uS for one register
    
    crc = GenerateCRC( n + 2 );
    uartToSend[n] = crc >> 8;
    n++;
    uartToSend[n] = (uint8_t) crc;
    n += 2;
    
    nResponseBytes = n;
//    T1measLow();  //174uS for one register
}


bool CheckHoldingRegValue( uint8_t wr_Addr, uint16_t wr_Value )
{
    bool check = OK;
    
    if ( MB_H_TRIP_DC_AMPERE == wr_Addr )
    {
        if( (wr_Value > TRIP_DC_AMPERE_MAX) | (wr_Value < TRIP_DC_AMPERE_MIN) )
        {
            check = NOK;
        }
    }
    if ( MB_H_TRIP_AMB_TEMP == wr_Addr )
    {
        if( (wr_Value > TRIP_AMB_TEMP_MAX) | (wr_Value < TRIP_AMB_TEMP_MIN) )
        {
            check = NOK;
        }
    }
    if ( MB_H_TRIP_HS_TEMP == wr_Addr )
    {
        if( (wr_Value > TRIP_HS_TEMP_MAX) | (wr_Value < TRIP_HS_TEMP_MIN) )
        {
            check = NOK;
        }
    }
    if ( MB_H_TRIP_IND_TEMP == wr_Addr )
    {
        if( (wr_Value > TRIP_IND_TEMP_MAX) | (wr_Value < TRIP_IND_TEMP_MIN) )
        {
            check = NOK;
        }
    }
    /////////////////////////////////////////////
    if ( MB_H_DEAD_TIME == wr_Addr )
    {
        if( (wr_Value > DEAD_TIME_MAX) )
        {
            check = NOK;
        }
    }
    if ( MB_H_WARNING_EX24V == wr_Addr )
    {
        if( (wr_Value > TRIP_EX24V_MAX) | (wr_Value < TRIP_EX24V_MIN) )
        {
            check = NOK;
        }
    }
    if(  MB_H_START == wr_Addr )
    {
        if( (wr_Value > CONTROL_START) )
        {
            check = NOK;
        }
    }
    if(  MB_H_FLASH_STORE == wr_Addr )
    {
//        if( (wr_Value > STORE_IN_FLASH) )
        if( wr_Value > ERASE_FLASH )
        {
            check = NOK;
        }
    }
    /////////////////////////////////////////////
    if ( MB_H_COEF_IDC == wr_Addr )
    {
        if( (wr_Value > COEF_IDC_MAX) | (wr_Value < COEF_IDC_MIN) )
        {
            check = NOK;
        }
    }
    if ( MB_H_COEF_AMB == wr_Addr )
    {
        if( (wr_Value > COEF_AMB_MAX) | (wr_Value < COEF_AMB_MIN) )
        {
            check = NOK;
        }
    }
    if ( MB_H_COEF_HS == wr_Addr )
    {
        if( (wr_Value > COEF_HS_MAX) | (wr_Value < COEF_HS_MIN) )
        {
            check = NOK;
        }
    }
    if ( MB_H_COEF_IND == wr_Addr )
    {
        if( (wr_Value > COEF_IND_MAX) | (wr_Value < COEF_IND_MIN) )
        {
            check = NOK;
        }
    }
    /////////////////////////////////////////////
    if ( MB_H_OFFSET_IDC == wr_Addr )
    {
        if( ((int16_t)wr_Value > OFFSET_IDC_MAX) | ((int16_t)wr_Value < OFFSET_IDC_MIN) )
        {
            check = NOK;
        }
    }
    if ( MB_H_OFFSET_AMB == wr_Addr )
    {
        if( ((int16_t)wr_Value > OFFSET_AMB_MAX) | ((int16_t)wr_Value < OFFSET_AMB_MIN) )
        {
            check = NOK;
        }
    }
    if ( MB_H_OFFSET_HS == wr_Addr )
    {
        if( ((int16_t)wr_Value > OFFSET_HS_MAX) | ((int16_t)wr_Value < OFFSET_HS_MIN) )
        {
            check = NOK;
        }
    }
    if ( MB_H_OFFSET_IND == wr_Addr )
    {
        if( ((int16_t)wr_Value > OFFSET_IND_MAX) | ((int16_t)wr_Value < OFFSET_IND_MIN) )
        {
            check = NOK;
        }
    }
    
    return check;
}



void WriteHoldingRegister( void )
{
//    T1measHigh();  T2measHigh();
    uint8_t  wr_Address8 = 0;
    uint16_t wr_ValueToWrite    = 0;
    uint8_t  wr_ValueToWriteLow  = 0;
    uint8_t  wr_ValueToWriteHigh = 0;
    uint16_t crc = 0;
    uint8_t  n = 3;

    //Get 8-bit address instead 16-bit
    wr_Address8 = uartReceived[3];
    
    uartToSend[0] = SlaveAddress;
    if ( wr_Address8 > MB_HOLDING_REG_COUNT )
    {
        uartToSend[1] = WRITE_HOLDING_REG | 0x80;
        uartToSend[2] = 0x02;  //object address is not valid for the Slave.
        n = 3;
    }
    else
    {
        uartToSend[1] = WRITE_HOLDING_REG;
        
        wr_ValueToWriteLow  = uartReceived[5];
        wr_ValueToWriteHigh = uartReceived[4];
        //Combine value to write register
        wr_ValueToWrite = wr_ValueToWriteHigh;
        wr_ValueToWrite <<= 8;
        wr_ValueToWrite |= wr_ValueToWriteLow;

        if ( NOK == CheckHoldingRegValue( wr_Address8, wr_ValueToWrite ) )
        {
            uartToSend[1] = WRITE_HOLDING_REG | 0x80;
            uartToSend[2] = 0x03;  //Writing value is not valid for the addressed object.
            n = 3;
        }
        else
        {
            mbHoldingReg[wr_Address8] = wr_ValueToWrite;

            uartToSend[2] = 0x00;
            uartToSend[3] = wr_Address8;
            uartToSend[4] = wr_ValueToWriteHigh;
            uartToSend[5] = wr_ValueToWriteLow;
            n = 6;
            bHoldingRegNewValue = true;
        }
    }
//    T2measLow();  //28us for one register

    crc = GenerateCRC( n + 2 );
    uartToSend[n] = crc >> 8;
    n++;
    uartToSend[n] = (uint8_t) crc;
    n += 2;

    nResponseBytes = n;
//    T1measLow();  //170us for one register
}


void ModBusSend( void )
{
//    T1measHigh();
    Mb1High();
    int k;
    
//    UART_SEND;
    if ( nResponseBytes > 0 )
    {
        Mb2High();
        UART_SEND;
        
        for (k = 0; k < (nResponseBytes - 1); k++)
        {
            EUSART_Write( uartToSend[k] );
        }

        while (!(TX1STAbits.TRMT));
        UART_RECEIVE;
        nResponseBytes = 0;

//        PIE1bits.RCIE = 0;
////        Reset_eusartRxCount();
//        ModbusRXPos   = 0;
//        PIE1bits.RCIE = 1;
    }
    
    
    
//    UART_RECEIVE;
    Mb1Low(); Mb2Low();
//    T1measLow();  //1400us
}

void CheckUARTbuf( void )
{
    if( (Get_delayFromPrevRxByteMs() >= FRAME_TOUT_MS) && (true == Get_bCheckUART()) )
    {
        Set_bCheckUART( false );
        //    T1measHigh();
        while ( Get_eusartRxCount() )
        {
            uartReceived[ModbusRXPos] = EUSART_Read( );
            ModbusRXPos++;
        }
        bCheckRxBuff = true;
    }
    //    T1measLow();  //89us
}



void DecodeMBmessage( void )
{
    uint8_t  addr;
    
//    GreenHigh();
    if ( uartReceived[0] == SlaveAddress )
    {
        if ( 0 == CheckCRC() )  //184us
        {
//            PIE1bits.RCIE = 0;
//            Reset_eusartRxCount();
//            PIE1bits.RCIE = 1;            
        }
        else
        {
            switch( uartReceived[1] )
            {
                case READ_HOLDING_REG:
                    ReadHoldingRegister( );
                    break;

                case READ_IN_REG:
                    CheckRotaryValue();
                    mbInputReg[MB_I_ADDR_SWITCH] = (uint16_t) Get_RotaryValue();
                    ReadInputRegister( );
                    break;

                case WRITE_HOLDING_REG:
                    WriteHoldingRegister( );
                    break;

                default:
                    uartToSend[0] = SlaveAddress;
                    uartToSend[1] = uartReceived[1] | 0x80;  //the function code of request
                    uartToSend[2] = 0x01; //function code is not valid or implemented.
                    break;
            }
        }
    }
//    GreenLow();
}
    

void vModBusProcess( void )
{
    switch( mbState )
    {
        case MB_STA_IDLE:
            if( true == bCheckRxBuff )
            {
                bCheckRxBuff = false;
                Clear_delayResponseTimeMs();
                mbState = MB_STA_VERIFY_RECEIVED;
            }
            else
            {

                if ( (Get_currentTimeMs() - adcReadLastTimeMs) > NTC_SAMPLE_TIME )
                {
                    adcReadLastTimeMs = Get_currentTimeMs();
                    ReadADCchannels();
                }

                if ( STORE_IN_FLASH == Get_storeFlashValue() ) 
                {
//                    Flash1High();  //
                    WriteFlashBlock();  // 3300 uS
                    Clear_storeFlashValue();
//                    Flash1Low();  //
                }
                if ( ERASE_FLASH == Get_storeFlashValue() ) 
                {
//                    Flash1High();  //
                    EraseFlashBlock();  // 3300 uS
                    Clear_storeFlashValue();
//                    Flash1Low();  //
                }
            }
            break;

          
        case MB_STA_VERIFY_RECEIVED:
            
            if ( ModbusRXPos == MB_COMMAND_LEN )
            {
#ifdef DEBUG_MB_PROCESS
                BluePosTicks( ModbusRXPos );
#endif
                ModbusRXPos = 0;
                DecodeMBmessage( );
                mbState = MB_STA_SEND;
//                mbState = MB_RECEIVED;
            }
            else
            {
#ifdef DEBUG_MB_PROCESS
                GreenPosTicks( ModbusRXPos + 1 );
#endif
                ModbusRXPos = 0;
                mbState = MB_STA_IDLE;
            }
            break;


        case MB_STA_SEND:

            if( Get_delayResponseTimeMs() >= RESPONSE_DELAY )
            {
                ModBusSend();
                mbState = MB_STA_IDLE;
            }
            break;

        case MB_STA_CLEAR_RECEIVED:

            break;

        default:
            mbState = MB_STA_IDLE;
            break;
    }
}


void vUpdateMbRegsProcess( void )
{        
    if ( true == bHoldingRegNewValue )
    {
//        Flash1High();
        
//        dcAmpereTripValueP = (int16_t) mbHoldingReg[MB_H_TRIP_DC_AMPERE];
//        dcAmpereTripValueN = 0 - dcAmpereTripValueP;
//        ex24vWarnValue     = mbHoldingReg[MB_H_WARNING_EX24V];
//        tempTripAMBvalue   = mbHoldingReg[MB_H_TRIP_AMB_TEMP];
//        tempTripHSvalue    = mbHoldingReg[MB_H_TRIP_HS_TEMP];
//        tempTripINDvalue   = mbHoldingReg[MB_H_TRIP_IND_TEMP];
        
        tripValues[TRIP_IDC_P_POS] = (int16_t)mbHoldingReg[MB_H_TRIP_DC_AMPERE];
        tripValues[TRIP_IDC_N_POS] = 0 - tripValues[TRIP_IDC_P_POS];
        tripValues[TRIP_EX24V_P_POS]    = (int16_t)mbHoldingReg[MB_H_WARNING_EX24V];
        tripValues[TRIP_AMB_P_POS] = (int16_t)mbHoldingReg[MB_H_TRIP_AMB_TEMP];
        tripValues[TRIP_HS_P_POS]  = (int16_t)mbHoldingReg[MB_H_TRIP_HS_TEMP];
        tripValues[TRIP_IND_P_POS] = (int16_t)mbHoldingReg[MB_H_TRIP_IND_TEMP];
        

        deadTimeValue = (uint8_t) (mbHoldingReg[MB_H_DEAD_TIME] / 5);
        COG1_ChangeDeadTime( deadTimeValue );
        COG2_ChangeDeadTime( deadTimeValue );
        COG3_ChangeDeadTime( deadTimeValue );
        
//        controlValue    = mbHoldingReg[MB_H_START];
        controlValue    = CONTROL_START;
        storeFlashValue = mbHoldingReg[MB_H_FLASH_STORE];
        
        Set_ntcCoef( ADC_POS_IDC, mbHoldingReg[MB_H_COEF_IDC] );
        Set_ntcCoef( ADC_POS_AMB, mbHoldingReg[MB_H_COEF_AMB] );
        Set_ntcCoef( ADC_POS_HS,  mbHoldingReg[MB_H_COEF_HS]  );
        Set_ntcCoef( ADC_POS_IND, mbHoldingReg[MB_H_COEF_IND] );
        //
        Set_ntcOffset( ADC_POS_IDC, (int16_t)mbHoldingReg[MB_H_OFFSET_IDC] );
        Set_ntcOffset( ADC_POS_AMB, (int16_t)mbHoldingReg[MB_H_OFFSET_AMB] );
        Set_ntcOffset( ADC_POS_HS,  (int16_t)mbHoldingReg[MB_H_OFFSET_HS]  );
        Set_ntcOffset( ADC_POS_IND, (int16_t)mbHoldingReg[MB_H_OFFSET_IND] );
//    EX24V_POS,

        Update16_FlashBlock( FLASH_DEAD_TIME,      mbHoldingReg[MB_H_DEAD_TIME]  );
        
        Update16_FlashBlock( FLASH_TRIP_DC_AMPERE, (uint16_t)tripValues[TRIP_IDC_P_POS] );
        Update16_FlashBlock( FLASH_WARNING_EX24V,  (uint16_t)tripValues[TRIP_EX24V_P_POS]    );
        Update16_FlashBlock( FLASH_TRIP_AMB_TEMP,  (uint16_t)tripValues[TRIP_AMB_P_POS] );
        Update16_FlashBlock( FLASH_TRIP_HS_TEMP,   (uint16_t)tripValues[TRIP_HS_P_POS]  );
        Update16_FlashBlock( FLASH_TRIP_IND_TEMP,  (uint16_t)tripValues[TRIP_IND_P_POS] );
        //
        Update16_FlashBlock( FLASH_COEF_IDC,       mbHoldingReg[MB_H_COEF_IDC]   );
        Update16_FlashBlock( FLASH_COEF_AMB,       mbHoldingReg[MB_H_COEF_AMB]   );
        Update16_FlashBlock( FLASH_COEF_HS,        mbHoldingReg[MB_H_COEF_HS]    );
        Update16_FlashBlock( FLASH_COEF_IND,       mbHoldingReg[MB_H_COEF_IND]   );
        Update16_FlashBlock( FLASH_OFFSET_IDC,     mbHoldingReg[MB_H_OFFSET_IDC] );
        Update16_FlashBlock( FLASH_OFFSET_AMB,     mbHoldingReg[MB_H_OFFSET_AMB] );
        Update16_FlashBlock( FLASH_OFFSET_HS,      mbHoldingReg[MB_H_OFFSET_HS]  );
        Update16_FlashBlock( FLASH_OFFSET_IND,     mbHoldingReg[MB_H_OFFSET_IND] );
        
        bHoldingRegNewValue = false;
        
//        Flash1Low();  // 170 us 
    }
}
