/**
   COG2 Generated Driver File
 
   @Company
     Microchip Technology Inc.
 
   @File Name
     cog2.c
 
   @Summary
     This is the generated driver implementation file for the COG2 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs
 
   @Description
     This source file provides implementations for driver APIs for COG2.
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
#include "cog2.h"

/**
  Section: COG2 APIs
*/

void COG2_Initialize(void)
{
    // Reset double buffered register COG2CON0
    COG2CON0 = 0x00;

    // Set the COG to the options selected in PIC10 / PIC12 / PIC16 / PIC18 MCUs
    // G2POLA Active high; G2POLB Active high; G2POLC Active high; G2POLD Active high; G2FDBS Delay chain and COGxDF; G2RDBS Delay chain and COGxDBR; 
    COG2CON1 = 0xC0;

    // G2RIS0 enabled; G2RIS1 disabled; G2RIS2 disabled; G2RIS3 disabled; G2RIS4 disabled; G2RIS5 disabled; G2RIS6 disabled; G2RIS7 disabled; 
    COG2RIS0 = 0x01;

    // G2RIS8 disabled; G2RIS9 disabled; G2RIS10 disabled; G2RIS11 disabled; G2RIS12 disabled; G2RIS13 disabled; G2RIS14 disabled; G2RIS15 disabled; 
    COG2RIS1 = 0x00;

    // G2RSIM0 Level Trigger; G2RSIM1 Level Trigger; G2RSIM2 Level Trigger; G2RSIM3 Level Trigger; G2RSIM4 Level Trigger; G2RSIM5 Level Trigger; G2RSIM6 Level Trigger; G2RSIM7 Level Trigger; 
    COG2RSIM0 = 0x00;

    // G2RSIM8 Level Trigger; G2RSIM9 Level Trigger; G2RSIM10 Level Trigger; G2RSIM11 Level Trigger; G2RSIM12 Level Trigger; G2RSIM13 Level Trigger; G2RSIM14 Level Trigger; G2RSIM15 Level Trigger; 
    COG2RSIM1 = 0x00;

    // G2FIS0 enabled; G2FIS1 disabled; G2FIS2 disabled; G2FIS3 disabled; G2FIS4 disabled; G2FIS5 disabled; G2FIS6 disabled; G2FIS7 disabled; 
    COG2FIS0 = 0x01;

    // G2FIS8 disabled; G2FIS9 disabled; G2FIS10 disabled; G2FIS11 disabled; G2FIS12 disabled; G2FIS13 disabled; G2FIS14 disabled; G2FIS15 disabled; 
    COG2FIS1 = 0x00;

    // G2FSIM0 Level Trigger; G2FSIM1 Level Trigger; G2FSIM2 Level Trigger; G2FSIM3 Level Trigger; G2FSIM4 Level Trigger; G2FSIM5 Level Trigger; G2FSIM6 Level Trigger; G2FSIM7 Level Trigger; 
    COG2FSIM0 = 0x00;

    // G2FSIM8 Level Trigger; G2FSIM9 Level Trigger; G2FSIM10 Level Trigger; G2FSIM11 Level Trigger; G2FSIM12 Level Trigger; G2FSIM13 Level Trigger; G2FSIM14 Level Trigger; G2FSIM15 Level Trigger; 
    COG2FSIM1 = 0x00;

    // G2ASDAC logic 0; G2ASDBD logic 0; G2ARSEN enabled; G2ASE shutdown; 
    COG2ASD0 = 0xE8;

    // G2AS0E disabled; G2AS1E disabled; G2AS2E disabled; G2AS3E disabled; G2AS4E disabled; G2AS5E enabled; G2AS6E disabled; G2AS7E disabled; 
    COG2ASD1 = 0x20;

    // G2STRA static level; G2STRB static level; G2STRC static level; G2STRD static level; G2SDATA static data low; G2SDATB static data low; G2SDATC static data low; G2SDATD static data low; 
    COG2STR = 0x00;

    // DBR 30; 
    COG2DBR = 0x1E;

    // G2DBF 30; 
    COG2DBF = 0x1E;

    // BLKR 0; 
    COG2BLKR = 0x00;

    // BLKF 3; 
    COG2BLKF = 0x03;

    // PHR 0; 
    COG2PHR = 0x00;

    // PHF 0; 
    COG2PHF = 0x00;

    // G2MD Half-Bridge mode; G2CS FOSC; G2LD transfer complete; G2EN enabled; 
    COG2CON0 = 0x8C;

}

//void COG2_AutoShutdownEventSet()
//{
//    // Setting the GxASDE bit of COGxASD register
//    COG2ASD0bits.G2ASE = 1;
//}

//void COG2_AutoShutdownEventClear()
//{
//    // Clearing the GxASDE bit of COGxASD register
//    COG2ASD0bits.G2ASE = 0;
//}

void COG2_ChangeDeadTime( uint8_t dTval )
{
    COG2CON0 = 0x00;

    COG2DBR = dTval;
    COG2DBF = dTval;

    COG2CON0 = 0x8C;
}


//void COG2_ReadDeadTime( uint8_t* dTvalR, uint8_t* dTvalF )
//{
//    *dTvalR = COG2DBR;
//    *dTvalF = COG2DBF;
//}


/**
 End of File
*/

