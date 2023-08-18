/**
   COG3 Generated Driver File
 
   @Company
     Microchip Technology Inc.
 
   @File Name
     cog3.c
 
   @Summary
     This is the generated driver implementation file for the COG3 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs
 
   @Description
     This source file provides implementations for driver APIs for COG3.
     Generation Information :
         Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
         Device            :  PIC16F1779
         Driver Version    :  2.01
     The generated drivers are tested against the following:
         Compiler          :  XC8 2.36 and above
         MPLAB             :  MPLAB X 6.00
 */ 

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef COG3_H
#define COG3_H

/**
  Section: Included Files
*/

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**
  Section: COG3 APIs
*/

        
//void COG3_ReadDeadTime( uint8_t* dTvalR, uint8_t* dTvalF );
        
void COG3_ChangeDeadTime( uint8_t dTval );


/**
  @Summary
    Initializes the COG3

  @Description
    This routine configures the COG3 specific control registers and input clock

  @Preconditions
    None

  @Returns
    None

  @Param
    None

  @Comment

  @Example
    <code>
    COG3_Initialize();
    </code>
*/
void COG3_Initialize(void);

/**
  @Summary
    Software generated Shutdown

  @Description
    This function forces the COG into Shutdown state.

  @Preconditions
    COG3_Initialize() function should have been called before calling this function

  @Returns
    None

  @Param
    None

  @Example
    <code>
    COG3_initialize();

    // Do something

    COG3_AutoShutdownEventSet();
    </code>
*/
void COG3_AutoShutdownEventSet();

/**
  @Summary
    This function makes the COG to resume its operations from the software
    generated shutdown state.

  @Description
    When auto-restart is disabled, the shutdown state will persist as long as the
    GxASE bit is set and hence to resume operations, this function should be used.

    However when auto-restart is enabled, the GxASE bit will clear automatically
    and resume operation on the next rising edge event. In that case, there is no
    need to call this function.

  @Preconditions
    COG3_Initialize() and COG3_AutoShutdownEventSet() functions should have been called before calling this function

  @Returns
    None

  @Param
    None

  @Example
    <code>
    COG3_initialize();

    // Do something

    COG3_AutoShutdownEventSet();

    // Do something

    COG3_AutoShutdownEventClear();
    </code>
*/
void COG3_AutoShutdownEventClear();


#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif  //COG3_H
/**
 End of File
*/
