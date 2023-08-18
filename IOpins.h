/* *****************************************************************************
 * File:   IOpins.h
 * Author: Damyan Neev
 * Created on 2023 02 17
 *
 * Description: header file for GPIO pins.
 *      Device:  CS-1301_00  PIC16F1773
 *    Compiler:  XC8 v2.40   MPLAB X v6.00
 **************************************************************************** */


#ifndef IO_PINS_H
#define	IO_PINS_H


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
    P_LOW,
    P_HIGH,
        
    PORT_COUNT_STATES
}PORT_State_t;


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
bool Get_iPwmEN_Stable( void );
uint8_t Get_RotaryValue( void );

void CheckRotaryValue( void );
void InitRotary( void );

void PWM_STOP( void );
void PWM_Enable( void );



#ifdef	__cplusplus
extern "C" {
#endif // __cplusplus
    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 
#ifdef	__cplusplus
}
#endif // __cplusplus

#endif  // IO_PINS_H