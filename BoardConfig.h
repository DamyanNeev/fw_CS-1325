/* *****************************************************************************
 * File:   BoardConfig.h
 * Author: Damyan Neev
 * Created on 2022 11 01
 *
 * Description: header file for global device configuration.
 *      Device:  CS-1301_00  PIC16F1773
 *    Compiler:  XC8 v2.40   MPLAB X v6.00
 **************************************************************************** */


#ifndef BOARD_CONFIG_H
#define	BOARD_CONFIG_H


//===================================
// Header Includes
//===================================
#include <xc.h>
#include "mcc_Files/pin_manager.h"


//===================================   
// Configuration Definitions
//===================================


//===================================
// Constants and Macros Definitions
//===================================
#define  IDC_SAMPLE_TIME   10
//#define  IDC_SAMPLE_FILT   99
#define  IDC_SAMPLE_FILT    9

#define  NTC_SAMPLE_TIME   50
//#define  NTC_SAMPLE_FILT   40
#define  NTC_SAMPLE_FILT   20



#define NOK 0
#define OK  1


#define SLAVE_ADDR         1  // does't matter if rotary switch is assembled
#define DEVICE_ID       1301  //0x0515
//#define FW_VERSION_ID    001  // fault state is cleared when MB_H_START = 0x0000
//#define FW_VERSION_ID    002  // fault state is cleared when iPwmEN = P_LOW
//#define FW_VERSION_ID    003  // hold FltOut signal for 20mS after iPwmEN is stable low

//#define FW_VERSION_ID    203  // Dublicate error in MB_I_DT1R, and MB_I_DT1F is error counter
#define FW_VERSION_ID    204  // CLC test



//===================================
// Enumeration Definitions
//===================================



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



#ifdef	__cplusplus
extern "C" {
#endif // __cplusplus
    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 
#ifdef	__cplusplus
}
#endif // __cplusplus

#endif	/* BOARD_CONFIG_H */

