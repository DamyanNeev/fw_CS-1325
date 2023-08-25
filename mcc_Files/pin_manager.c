/**
  Generated Pin Manager File

  Company:
    Microchip Technology Inc.

  File Name:
    pin_manager.c

  Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC16F1779
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above
        MPLAB             :  MPLAB X 6.00

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.
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

#include "pin_manager.h"





void PIN_MANAGER_Initialize(void)
{
    /**
    LATx registers
    */
    LATE = 0x00;
    LATD = 0x00;
    LATA = 0x00;
    LATB = 0x80;
    LATC = 0x00;

    /**
    TRISx registers
    */
    TRISE = 0x00;
    TRISA = 0xFE;
    TRISB = 0x40;
    TRISC = 0xFE;
    TRISD = 0xD7;

    /**
    ANSELx registers
    */
    ANSELD = 0x40;
    ANSELC = 0x00;
    ANSELB = 0x29;
    ANSELE = 0x00;
    ANSELA = 0x2E;

    /**
    WPUx registers
    */
    WPUD = 0xF0;
    WPUE = 0x00;
    WPUB = 0x00;
    WPUA = 0x00;
    WPUC = 0xF0;
    OPTION_REGbits.nWPUEN = 0;

    /**
    ODx registers
    */
    ODCONE = 0x00;
    ODCONA = 0x00;
    ODCONB = 0x00;
    ODCONC = 0x00;
    ODCOND = 0x00;

    /**
    SLRCONx registers
    */
    SLRCONA = 0xFF;
    SLRCONB = 0xF7;
    SLRCONC = 0xFF;
    SLRCOND = 0xF9;
    SLRCONE = 0x07;

    /**
    INLVLx registers
    */
    INLVLA = 0x3F;
    INLVLB = 0xF0;
    INLVLC = 0xFF;
    INLVLD = 0xF9;





   
    
	
    RC0PPS = 0x01;   //RC0->CLC1:CLC1OUT;    
    RXPPS = 0x0E;   //RB6->EUSART:RX;    
    RB7PPS = 0x24;   //RB7->EUSART:TX;    
    COG3INPPS = 0x1A;   //RD2->COG3:COG3IN;    
    CLCIN3PPS = 0x1C;   //RD4->CLC4:CLCIN3;    
    RE0PPS = 0x0E;   //RE0->COG3:COG3B;    
    RB4PPS = 0x0D;   //RB4->COG3:COG3A;    
    COG2INPPS = 0x19;   //RD1->COG2:COG2IN;    
    RB1PPS = 0x06;   //RB1->COG1:COG1B;    
    //ADCACTPPS = 0x0A;   //RB2->ADC:ADCACT;    
    CLCIN0PPS = 0x12;   //RC2->CLC3:CLCIN0;    
    RB0PPS = 0x05;   //RB0->COG1:COG1A;    
    RB2PPS = 0x09;   //RB2->COG2:COG2A;    
    RD3PPS = 0x04;   //RD3->CLC4:CLC4OUT;    
    RB3PPS = 0x0A;   //RB3->COG2:COG2B;    
    CLCIN1PPS = 0x04;   //RA4->CLC3:CLCIN1;    
    COG1INPPS = 0x18;   //RD0->COG1:COG1IN;    
}
  
//void PIN_MANAGER_IOC(void)
//{   
//}

/**
 End of File
*/