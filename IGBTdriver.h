/* *****************************************************************************
 * File:   IGBTdriver.h
 * Author: Damyan Neev
 * Created on 2023 03 24
 *
 * Description: source file for control of IGBT driver
 *      Device:  CS-1301_00  PIC16F1773
 *    Compiler:  XC8 v2.40   MPLAB X v6.00
 **************************************************************************** */


#ifndef IGBT_DRIVER_H
#define	IGBT_DRIVER_H


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
    IGBT_STA_IDLE,
    IGBT_STA_READY,
    IGBT_STA_DRIVE,
    IGBT_STA_FAULT,
    IGBT_STA_RESET,
    
    IGBT_STATES_COUNT
}IGBT_DRV_State_t;


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

void vCheckTrips( void );
void vIGBTcontrol( void );



#ifdef	__cplusplus
extern "C" {
#endif // __cplusplus
    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 
#ifdef	__cplusplus
}
#endif // __cplusplus

#endif  // IGBT_DRIVER_H