/**
   COG1 Generated Driver File
 
   @Company
     Microchip Technology Inc.
 
   @File Name
     cog1.c
 
   @Summary
     This is the generated driver implementation file for the COG1 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs
 
   @Description
     This source file provides implementations for driver APIs for COG1.
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
#include "cog1.h"

/**
  Section: COG1 APIs
*/

void COG1_Initialize(void)
{
    // Reset double buffered register COG1CON0
    COG1CON0 = 0x00;

    // Set the COG to the options selected in PIC10 / PIC12 / PIC16 / PIC18 MCUs
    // G1POLA Active high; G1POLB Active high; G1POLC Active high; G1POLD Active high; G1FDBS Delay chain and COGxDF; G1RDBS Delay chain and COGxDBR; 
    COG1CON1 = 0xC0;

    // G1RIS0 enabled; G1RIS1 disabled; G1RIS2 disabled; G1RIS3 disabled; G1RIS4 disabled; G1RIS5 disabled; G1RIS6 disabled; G1RIS7 disabled; 
    COG1RIS0 = 0x01;

    // G1RIS8 disabled; G1RIS9 disabled; G1RIS10 disabled; G1RIS11 disabled; G1RIS12 disabled; G1RIS13 disabled; G1RIS14 disabled; G1RIS15 disabled; 
    COG1RIS1 = 0x00;

    // G1RSIM0 Level Trigger; G1RSIM1 Level Trigger; G1RSIM2 Level Trigger; G1RSIM3 Level Trigger; G1RSIM4 Level Trigger; G1RSIM5 Level Trigger; G1RSIM6 Level Trigger; G1RSIM7 Level Trigger; 
    COG1RSIM0 = 0x00;

    // G1RSIM8 Level Trigger; G1RSIM9 Level Trigger; G1RSIM10 Level Trigger; G1RSIM11 Level Trigger; G1RSIM12 Level Trigger; G1RSIM13 Level Trigger; G1RSIM14 Level Trigger; G1RSIM15 Level Trigger; 
    COG1RSIM1 = 0x00;

    // G1FIS0 enabled; G1FIS1 disabled; G1FIS2 disabled; G1FIS3 disabled; G1FIS4 disabled; G1FIS5 disabled; G1FIS6 disabled; G1FIS7 disabled; 
    COG1FIS0 = 0x01;

    // G1FIS8 disabled; G1FIS9 disabled; G1FIS10 disabled; G1FIS11 disabled; G1FIS12 disabled; G1FIS13 disabled; G1FIS14 disabled; G1FIS15 disabled; 
    COG1FIS1 = 0x00;

    // G1FSIM0 Level Trigger; G1FSIM1 Level Trigger; G1FSIM2 Level Trigger; G1FSIM3 Level Trigger; G1FSIM4 Level Trigger; G1FSIM5 Level Trigger; G1FSIM6 Level Trigger; G1FSIM7 Level Trigger; 
    COG1FSIM0 = 0x00;

    // G1FSIM8 Level Trigger; G1FSIM9 Level Trigger; G1FSIM10 Level Trigger; G1FSIM11 Level Trigger; G1FSIM12 Level Trigger; G1FSIM13 Level Trigger; G1FSIM14 Level Trigger; G1FSIM15 Level Trigger; 
    COG1FSIM1 = 0x00;

    // G1ASDAC logic 0; G1ASDBD logic 0; G1ARSEN enabled; G1ASE shutdown; 
    COG1ASD0 = 0xE8;

    // G1AS0E disabled; G1AS1E disabled; G1AS2E disabled; G1AS3E disabled; G1AS4E disabled; G1AS5E enabled; G1AS6E disabled; G1AS7E disabled; 
    COG1ASD1 = 0x20;

    // G1STRA static level; G1STRB static level; G1STRC static level; G1STRD static level; G1SDATA static data low; G1SDATB static data low; G1SDATC static data low; G1SDATD static data low; 
    COG1STR = 0x00;

    // DBR 30; 
    COG1DBR = 0x1E;

    // G1DBF 30; 
    COG1DBF = 0x1E;

    // BLKR 0; 
    COG1BLKR = 0x00;

    // BLKF 3; 
    COG1BLKF = 0x03;

    // PHR 0; 
    COG1PHR = 0x00;

    // PHF 0; 
    COG1PHF = 0x00;

    // G1MD Half-Bridge mode; G1CS FOSC; G1LD transfer complete; G1EN enabled; 
    COG1CON0 = 0x8C;

}

//void COG1_AutoShutdownEventSet()
//{
//    // Setting the GxASDE bit of COGxASD register
//    COG1ASD0bits.G1ASE = 1;
//}
//
//void COG1_AutoShutdownEventClear()
//{
//    // Clearing the GxASDE bit of COGxASD register
//    COG1ASD0bits.G1ASE = 0;
//}


void COG1_ChangeDeadTime( uint8_t dTval )
{
    COG1CON0 = 0x00;

    COG1DBR = dTval;
    COG1DBF = dTval;

    COG1CON0 = 0x8C;
}


//void COG1_ReadDeadTime( uint8_t* dTvalR, uint8_t* dTvalF )
//{
//    *dTvalR = COG1DBR;
//    *dTvalF = COG1DBF;
//}


/**
 End of File
*/

