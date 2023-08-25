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

/**
  Section: Included Files
*/

#include <xc.h>
#include "cog3.h"

/**
  Section: COG3 APIs
*/

void COG3_Initialize(void)
{
    // Reset double buffered register COG3CON0
    COG3CON0 = 0x00;

    // Set the COG to the options selected in PIC10 / PIC12 / PIC16 / PIC18 MCUs
    // G3POLA Active high; G3POLB Active high; G3POLC Active high; G3POLD Active high; G3FDBS Delay chain and COGxDF; G3RDBS Delay chain and COGxDBR; 
    COG3CON1 = 0xC0;

    // G3RIS0 enabled; G3RIS1 disabled; G3RIS2 disabled; G3RIS3 disabled; G3RIS4 disabled; G3RIS5 disabled; G3RIS6 disabled; G3RIS7 disabled; 
    COG3RIS0 = 0x01;

    // G3RIS8 disabled; G3RIS9 disabled; G3RIS10 disabled; G3RIS11 disabled; G3RIS12 disabled; G3RIS13 disabled; G3RIS14 disabled; G3RIS15 disabled; 
    COG3RIS1 = 0x00;

    // G3RSIM0 Level Trigger; G3RSIM1 Level Trigger; G3RSIM2 Level Trigger; G3RSIM3 Level Trigger; G3RSIM4 Level Trigger; G3RSIM5 Level Trigger; G3RSIM6 Level Trigger; G3RSIM7 Level Trigger; 
    COG3RSIM0 = 0x00;

    // G3RSIM8 Level Trigger; G3RSIM9 Level Trigger; G3RSIM10 Level Trigger; G3RSIM11 Level Trigger; G3RSIM12 Level Trigger; G3RSIM13 Level Trigger; G3RSIM14 Level Trigger; G3RSIM15 Level Trigger; 
    COG3RSIM1 = 0x00;

    // G3FIS0 enabled; G3FIS1 disabled; G3FIS2 disabled; G3FIS3 disabled; G3FIS4 disabled; G3FIS5 disabled; G3FIS6 disabled; G3FIS7 disabled; 
    COG3FIS0 = 0x01;

    // G3FIS8 disabled; G3FIS9 disabled; G3FIS10 disabled; G3FIS11 disabled; G3FIS12 disabled; G3FIS13 disabled; G3FIS14 disabled; G3FIS15 disabled; 
    COG3FIS1 = 0x00;

    // G3FSIM0 Level Trigger; G3FSIM1 Level Trigger; G3FSIM2 Level Trigger; G3FSIM3 Level Trigger; G3FSIM4 Level Trigger; G3FSIM5 Level Trigger; G3FSIM6 Level Trigger; G3FSIM7 Level Trigger; 
    COG3FSIM0 = 0x00;

    // G3FSIM8 Level Trigger; G3FSIM9 Level Trigger; G3FSIM10 Level Trigger; G3FSIM11 Level Trigger; G3FSIM12 Level Trigger; G3FSIM13 Level Trigger; G3FSIM14 Level Trigger; G3FSIM15 Level Trigger; 
    COG3FSIM1 = 0x00;

    // G3ASDAC logic 0; G3ASDBD logic 0; G3ARSEN enabled; G3ASE shutdown; 
    COG3ASD0 = 0xE8;

    // G3AS0E disabled; G3AS1E disabled; G3AS2E disabled; G3AS3E disabled; G3AS4E disabled; G3AS5E enabled; G3AS6E disabled; G3AS7E disabled; 
    COG3ASD1 = 0x20;

    // G3STRA static level; G3STRB static level; G3STRC static level; G3STRD static level; G3SDATA static data low; G3SDATB static data low; G3SDATC static data low; G3SDATD static data low; 
    COG3STR = 0x00;

    // DBR 30; 
    COG3DBR = 0x1E;

    // G3DBF 30; 
    COG3DBF = 0x1E;

    // BLKR 0; 
    COG3BLKR = 0x00;

    // BLKF 3; 
    COG3BLKF = 0x03;

    // PHR 0; 
    COG3PHR = 0x00;

    // PHF 0; 
    COG3PHF = 0x00;

    // G3MD Half-Bridge mode; G3CS FOSC; G3LD transfer complete; G3EN enabled; 
    COG3CON0 = 0x8C;

}

void COG3_AutoShutdownEventSet()
{
    // Setting the GxASDE bit of COGxASD register
    COG3ASD0bits.G3ASE = 1;
}

void COG3_AutoShutdownEventClear()
{
    // Clearing the GxASDE bit of COGxASD register
    COG3ASD0bits.G3ASE = 0;
}

void COG3_ChangeDeadTime( uint8_t dTval )
{
    COG3CON0 = 0x00;

    COG3DBR = dTval;
    COG3DBF = dTval;

    COG3CON0 = 0x8C;
}


//void COG3_ReadDeadTime( uint8_t* dTvalR, uint8_t* dTvalF )
//{
//    *dTvalR = COG3DBR;
//    *dTvalF = COG3DBF;
//}


/**
 End of File
*/

