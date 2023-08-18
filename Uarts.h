/* *****************************************************************************
 * File:   Uarts.h
 * Author: Damyan Neev
 * Created on 2023 02 27
 *
 * Description: header file for uarts.
 *      Device:  CS-1301_01  PIC16F1773
 *    Compiler:  XC8 v2.40   MPLAB X v6.00
 **************************************************************************** */


#ifndef UARTS_H
#define	UARTS_H


#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

    
//===================================
// Header Includes
//===================================
#include <stdbool.h>        /* For true/false definition */

//===================================   
// Configuration Definitions
//===================================
#define EUSART_TX_BUFFER_SIZE  RESPONCE_REG_COUNT*2
#define EUSART_RX_BUFFER_SIZE  RECEIVE_REG_COUNT

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
// Function-Like Macro
//===================================


//===================================
// Variables External Usage
//===================================


//===================================
// Function Prototypes
//===================================







#ifdef	__cplusplus
}
#endif // __cplusplus

#endif // UARTS_H