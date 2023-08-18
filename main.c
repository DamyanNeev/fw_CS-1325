/* *****************************************************************************
 * File:   main.c
 * Author: Damyan Neev
 * Created on 2023 02 14
 *
 * Description: main source file for CS-1301.
 *      Device:  CS-1301_01  PIC16F1779
 *    Compiler:  XC8 v2.40  pack 1.3.90  MPLAB X v6.00
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
#include "IGBTdriver.h"
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

typedef enum {
    MAIN_STA_IDLE,
    MAIN_STA_CHECK_UART,
    MAIN_STA_MODBUS_PROC,
    MAIN_STA_ADC_PROC,
    MAIN_STA_UPDATE_MB_REG,
    MAIN_STA_IGBT_CONTROL,

    MAIN_STA_COUNT
} MAIN_LoopState_t;


//===================================
// Type Definitions
//===================================


//===================================
// Function-Like Macros
//===================================


//===================================
// Variables Definitions
//===================================
MAIN_LoopState_t MAIN_LoopState = MAIN_STA_IDLE;

//===================================
// Prototype of functions definitions
//===================================


//===================================
// Functions
//===================================

bool iPwmEN_current;
bool iPwmEN_prev;

void main (void)
{
    // initialize the device
    SYSTEM_Initialize();

    INTERRUPT_GlobalInterruptDisable();
    INTERRUPT_PeripheralInterruptDisable();
    WDT_SoftDisable();

    __delay_ms(10);


    InitRotary();
    InitNTC_Order();
    InitModbusRegisters();


    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    WDT_SoftEnable();
    InitTimers();

    UART_RECEIVE;

    iPwmEN_current = Get_iPwmEN_Stable();
    iPwmEN_prev = iPwmEN_current;

    //PORTDbits.RD5 = 0;

    while (1) {
        CLRWDT();

        //        pwmEN_ScanNoIOC();

        vCheckTrips();


        iPwmEN_current = Get_iPwmEN_Stable();
        if (P_HIGH == iPwmEN_current) {
            if (P_LOW == iPwmEN_prev) {
                iPwmEN_prev = P_HIGH;
                SetValue_mbInputReg(MB_I_DT2R, 0x0000);
            }
        } else {
            iPwmEN_prev = iPwmEN_current;
        }


        //        if (MAIN_u16TimeLoop >= MAIN_LOOP_TIME_DELAY_PMP)
        //        {
        //            MAIN_u16TimeLoop -= MAIN_LOOP_TIME_DELAY_PMP;

        //DEBUG_SET_MAIN();

        switch (MAIN_LoopState++) {

            case MAIN_STA_IDLE:
                break;

            case MAIN_STA_CHECK_UART:
                CheckUARTbuf();
                break;

            case MAIN_STA_MODBUS_PROC:
                vModBusProcess();
                break;

            case MAIN_STA_ADC_PROC:
                vADCprocess();
                break;

            case MAIN_STA_UPDATE_MB_REG:
                vUpdateMbRegsProcess();
                break;

            case MAIN_STA_IGBT_CONTROL:
                vIGBTcontrol();
                break;

            default:
                MAIN_LoopState = MAIN_STA_IDLE;
                break;
        }
        //        }

    }
}
