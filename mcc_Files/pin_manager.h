/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC16F1779
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above
        MPLAB 	          :  MPLAB X 6.00	
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set TP4 aliases
#define TP4_TRIS                 TRISAbits.TRISA0
#define TP4_LAT                  LATAbits.LATA0
#define TP4_PORT                 PORTAbits.RA0
#define TP4_WPU                  WPUAbits.WPUA0
#define TP4_OD                   ODCONAbits.ODA0
#define TP4_ANS                  ANSELAbits.ANSA0
#define TP4_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define TP4_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define TP4_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define TP4_GetValue()           PORTAbits.RA0
#define TP4_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define TP4_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define TP4_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define TP4_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define TP4_SetPushPull()        do { ODCONAbits.ODA0 = 0; } while(0)
#define TP4_SetOpenDrain()       do { ODCONAbits.ODA0 = 1; } while(0)
#define TP4_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define TP4_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set ex24V aliases
#define ex24V_TRIS                 TRISAbits.TRISA1
#define ex24V_LAT                  LATAbits.LATA1
#define ex24V_PORT                 PORTAbits.RA1
#define ex24V_WPU                  WPUAbits.WPUA1
#define ex24V_OD                   ODCONAbits.ODA1
#define ex24V_ANS                  ANSELAbits.ANSA1
#define ex24V_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define ex24V_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define ex24V_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define ex24V_GetValue()           PORTAbits.RA1
#define ex24V_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define ex24V_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define ex24V_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define ex24V_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define ex24V_SetPushPull()        do { ODCONAbits.ODA1 = 0; } while(0)
#define ex24V_SetOpenDrain()       do { ODCONAbits.ODA1 = 1; } while(0)
#define ex24V_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define ex24V_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set NTCInd aliases
#define NTCInd_TRIS                 TRISAbits.TRISA2
#define NTCInd_LAT                  LATAbits.LATA2
#define NTCInd_PORT                 PORTAbits.RA2
#define NTCInd_WPU                  WPUAbits.WPUA2
#define NTCInd_OD                   ODCONAbits.ODA2
#define NTCInd_ANS                  ANSELAbits.ANSA2
#define NTCInd_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define NTCInd_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define NTCInd_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define NTCInd_GetValue()           PORTAbits.RA2
#define NTCInd_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define NTCInd_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define NTCInd_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define NTCInd_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define NTCInd_SetPushPull()        do { ODCONAbits.ODA2 = 0; } while(0)
#define NTCInd_SetOpenDrain()       do { ODCONAbits.ODA2 = 1; } while(0)
#define NTCInd_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define NTCInd_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set NTCAmb aliases
#define NTCAmb_TRIS                 TRISAbits.TRISA3
#define NTCAmb_LAT                  LATAbits.LATA3
#define NTCAmb_PORT                 PORTAbits.RA3
#define NTCAmb_WPU                  WPUAbits.WPUA3
#define NTCAmb_OD                   ODCONAbits.ODA3
#define NTCAmb_ANS                  ANSELAbits.ANSA3
#define NTCAmb_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define NTCAmb_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define NTCAmb_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define NTCAmb_GetValue()           PORTAbits.RA3
#define NTCAmb_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define NTCAmb_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define NTCAmb_SetPullup()          do { WPUAbits.WPUA3 = 1; } while(0)
#define NTCAmb_ResetPullup()        do { WPUAbits.WPUA3 = 0; } while(0)
#define NTCAmb_SetPushPull()        do { ODCONAbits.ODA3 = 0; } while(0)
#define NTCAmb_SetOpenDrain()       do { ODCONAbits.ODA3 = 1; } while(0)
#define NTCAmb_SetAnalogMode()      do { ANSELAbits.ANSA3 = 1; } while(0)
#define NTCAmb_SetDigitalMode()     do { ANSELAbits.ANSA3 = 0; } while(0)

// get/set RA4 procedures
#define RA4_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define RA4_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define RA4_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define RA4_GetValue()              PORTAbits.RA4
#define RA4_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define RA4_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define RA4_SetPullup()             do { WPUAbits.WPUA4 = 1; } while(0)
#define RA4_ResetPullup()           do { WPUAbits.WPUA4 = 0; } while(0)
#define RA4_SetAnalogMode()         do { ANSELAbits.ANSA4 = 1; } while(0)
#define RA4_SetDigitalMode()        do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set NTCHS aliases
#define NTCHS_TRIS                 TRISAbits.TRISA5
#define NTCHS_LAT                  LATAbits.LATA5
#define NTCHS_PORT                 PORTAbits.RA5
#define NTCHS_WPU                  WPUAbits.WPUA5
#define NTCHS_OD                   ODCONAbits.ODA5
#define NTCHS_ANS                  ANSELAbits.ANSA5
#define NTCHS_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define NTCHS_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define NTCHS_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define NTCHS_GetValue()           PORTAbits.RA5
#define NTCHS_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define NTCHS_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define NTCHS_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define NTCHS_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define NTCHS_SetPushPull()        do { ODCONAbits.ODA5 = 0; } while(0)
#define NTCHS_SetOpenDrain()       do { ODCONAbits.ODA5 = 1; } while(0)
#define NTCHS_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define NTCHS_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)

// get/set RB0 procedures
#define RB0_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define RB0_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define RB0_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define RB0_GetValue()              PORTBbits.RB0
#define RB0_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define RB0_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define RB0_SetPullup()             do { WPUBbits.WPUB0 = 1; } while(0)
#define RB0_ResetPullup()           do { WPUBbits.WPUB0 = 0; } while(0)
#define RB0_SetAnalogMode()         do { ANSELBbits.ANSB0 = 1; } while(0)
#define RB0_SetDigitalMode()        do { ANSELBbits.ANSB0 = 0; } while(0)

// get/set RB1 procedures
#define RB1_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define RB1_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define RB1_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define RB1_GetValue()              PORTBbits.RB1
#define RB1_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define RB1_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define RB1_SetPullup()             do { WPUBbits.WPUB1 = 1; } while(0)
#define RB1_ResetPullup()           do { WPUBbits.WPUB1 = 0; } while(0)
#define RB1_SetAnalogMode()         do { ANSELBbits.ANSB1 = 1; } while(0)
#define RB1_SetDigitalMode()        do { ANSELBbits.ANSB1 = 0; } while(0)

// get/set RB2 procedures
#define RB2_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define RB2_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define RB2_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define RB2_GetValue()              PORTBbits.RB2
#define RB2_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define RB2_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define RB2_SetPullup()             do { WPUBbits.WPUB2 = 1; } while(0)
#define RB2_ResetPullup()           do { WPUBbits.WPUB2 = 0; } while(0)
#define RB2_SetAnalogMode()         do { ANSELBbits.ANSB2 = 1; } while(0)
#define RB2_SetDigitalMode()        do { ANSELBbits.ANSB2 = 0; } while(0)

// get/set RB3 procedures
#define RB3_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define RB3_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define RB3_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define RB3_GetValue()              PORTBbits.RB3
#define RB3_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define RB3_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define RB3_SetPullup()             do { WPUBbits.WPUB3 = 1; } while(0)
#define RB3_ResetPullup()           do { WPUBbits.WPUB3 = 0; } while(0)
#define RB3_SetAnalogMode()         do { ANSELBbits.ANSB3 = 1; } while(0)
#define RB3_SetDigitalMode()        do { ANSELBbits.ANSB3 = 0; } while(0)

// get/set RB4 procedures
#define RB4_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define RB4_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define RB4_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define RB4_GetValue()              PORTBbits.RB4
#define RB4_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define RB4_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define RB4_SetPullup()             do { WPUBbits.WPUB4 = 1; } while(0)
#define RB4_ResetPullup()           do { WPUBbits.WPUB4 = 0; } while(0)
#define RB4_SetAnalogMode()         do { ANSELBbits.ANSB4 = 1; } while(0)
#define RB4_SetDigitalMode()        do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set DE aliases
#define DE_TRIS                 TRISBbits.TRISB5
#define DE_LAT                  LATBbits.LATB5
#define DE_PORT                 PORTBbits.RB5
#define DE_WPU                  WPUBbits.WPUB5
#define DE_OD                   ODCONBbits.ODB5
#define DE_ANS                  ANSELBbits.ANSB5
#define DE_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define DE_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define DE_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define DE_GetValue()           PORTBbits.RB5
#define DE_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define DE_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define DE_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define DE_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define DE_SetPushPull()        do { ODCONBbits.ODB5 = 0; } while(0)
#define DE_SetOpenDrain()       do { ODCONBbits.ODB5 = 1; } while(0)
#define DE_SetAnalogMode()      do { ANSELBbits.ANSB5 = 1; } while(0)
#define DE_SetDigitalMode()     do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set RB6 procedures
#define RB6_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define RB6_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define RB6_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define RB6_GetValue()              PORTBbits.RB6
#define RB6_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define RB6_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define RB6_SetPullup()             do { WPUBbits.WPUB6 = 1; } while(0)
#define RB6_ResetPullup()           do { WPUBbits.WPUB6 = 0; } while(0)

// get/set RB7 procedures
#define RB7_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define RB7_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define RB7_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define RB7_GetValue()              PORTBbits.RB7
#define RB7_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define RB7_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define RB7_SetPullup()             do { WPUBbits.WPUB7 = 1; } while(0)
#define RB7_ResetPullup()           do { WPUBbits.WPUB7 = 0; } while(0)

// get/set RC0 procedures
#define RC0_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define RC0_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define RC0_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define RC0_GetValue()              PORTCbits.RC0
#define RC0_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define RC0_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define RC0_SetPullup()             do { WPUCbits.WPUC0 = 1; } while(0)
#define RC0_ResetPullup()           do { WPUCbits.WPUC0 = 0; } while(0)

// get/set RC1 procedures
#define RC1_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define RC1_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define RC1_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define RC1_GetValue()              PORTCbits.RC1
#define RC1_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define RC1_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define RC1_SetPullup()             do { WPUCbits.WPUC1 = 1; } while(0)
#define RC1_ResetPullup()           do { WPUCbits.WPUC1 = 0; } while(0)

// get/set RC2 procedures
#define RC2_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define RC2_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define RC2_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define RC2_GetValue()              PORTCbits.RC2
#define RC2_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define RC2_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define RC2_SetPullup()             do { WPUCbits.WPUC2 = 1; } while(0)
#define RC2_ResetPullup()           do { WPUCbits.WPUC2 = 0; } while(0)
#define RC2_SetAnalogMode()         do { ANSELCbits.ANSC2 = 1; } while(0)
#define RC2_SetDigitalMode()        do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set Sw18 aliases
#define Sw18_TRIS                 TRISCbits.TRISC4
#define Sw18_LAT                  LATCbits.LATC4
#define Sw18_PORT                 PORTCbits.RC4
#define Sw18_WPU                  WPUCbits.WPUC4
#define Sw18_OD                   ODCONCbits.ODC4
#define Sw18_ANS                  ANSELCbits.ANSC4
#define Sw18_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define Sw18_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define Sw18_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define Sw18_GetValue()           PORTCbits.RC4
#define Sw18_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define Sw18_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define Sw18_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define Sw18_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define Sw18_SetPushPull()        do { ODCONCbits.ODC4 = 0; } while(0)
#define Sw18_SetOpenDrain()       do { ODCONCbits.ODC4 = 1; } while(0)
#define Sw18_SetAnalogMode()      do { ANSELCbits.ANSC4 = 1; } while(0)
#define Sw18_SetDigitalMode()     do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set Sw14 aliases
#define Sw14_TRIS                 TRISCbits.TRISC5
#define Sw14_LAT                  LATCbits.LATC5
#define Sw14_PORT                 PORTCbits.RC5
#define Sw14_WPU                  WPUCbits.WPUC5
#define Sw14_OD                   ODCONCbits.ODC5
#define Sw14_ANS                  ANSELCbits.ANSC5
#define Sw14_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define Sw14_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define Sw14_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define Sw14_GetValue()           PORTCbits.RC5
#define Sw14_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define Sw14_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define Sw14_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define Sw14_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define Sw14_SetPushPull()        do { ODCONCbits.ODC5 = 0; } while(0)
#define Sw14_SetOpenDrain()       do { ODCONCbits.ODC5 = 1; } while(0)
#define Sw14_SetAnalogMode()      do { ANSELCbits.ANSC5 = 1; } while(0)
#define Sw14_SetDigitalMode()     do { ANSELCbits.ANSC5 = 0; } while(0)

// get/set Sw12 aliases
#define Sw12_TRIS                 TRISCbits.TRISC6
#define Sw12_LAT                  LATCbits.LATC6
#define Sw12_PORT                 PORTCbits.RC6
#define Sw12_WPU                  WPUCbits.WPUC6
#define Sw12_OD                   ODCONCbits.ODC6
#define Sw12_ANS                  ANSELCbits.ANSC6
#define Sw12_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define Sw12_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define Sw12_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define Sw12_GetValue()           PORTCbits.RC6
#define Sw12_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define Sw12_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define Sw12_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define Sw12_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define Sw12_SetPushPull()        do { ODCONCbits.ODC6 = 0; } while(0)
#define Sw12_SetOpenDrain()       do { ODCONCbits.ODC6 = 1; } while(0)
#define Sw12_SetAnalogMode()      do { ANSELCbits.ANSC6 = 1; } while(0)
#define Sw12_SetDigitalMode()     do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set Sw11 aliases
#define Sw11_TRIS                 TRISCbits.TRISC7
#define Sw11_LAT                  LATCbits.LATC7
#define Sw11_PORT                 PORTCbits.RC7
#define Sw11_WPU                  WPUCbits.WPUC7
#define Sw11_OD                   ODCONCbits.ODC7
#define Sw11_ANS                  ANSELCbits.ANSC7
#define Sw11_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define Sw11_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define Sw11_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define Sw11_GetValue()           PORTCbits.RC7
#define Sw11_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define Sw11_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define Sw11_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define Sw11_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define Sw11_SetPushPull()        do { ODCONCbits.ODC7 = 0; } while(0)
#define Sw11_SetOpenDrain()       do { ODCONCbits.ODC7 = 1; } while(0)
#define Sw11_SetAnalogMode()      do { ANSELCbits.ANSC7 = 1; } while(0)
#define Sw11_SetDigitalMode()     do { ANSELCbits.ANSC7 = 0; } while(0)

// get/set RD0 procedures
#define RD0_SetHigh()            do { LATDbits.LATD0 = 1; } while(0)
#define RD0_SetLow()             do { LATDbits.LATD0 = 0; } while(0)
#define RD0_Toggle()             do { LATDbits.LATD0 = ~LATDbits.LATD0; } while(0)
#define RD0_GetValue()              PORTDbits.RD0
#define RD0_SetDigitalInput()    do { TRISDbits.TRISD0 = 1; } while(0)
#define RD0_SetDigitalOutput()   do { TRISDbits.TRISD0 = 0; } while(0)
#define RD0_SetPullup()             do { WPUDbits.WPUD0 = 1; } while(0)
#define RD0_ResetPullup()           do { WPUDbits.WPUD0 = 0; } while(0)
#define RD0_SetAnalogMode()         do { ANSELDbits.ANSD0 = 1; } while(0)
#define RD0_SetDigitalMode()        do { ANSELDbits.ANSD0 = 0; } while(0)

// get/set RD1 procedures
#define RD1_SetHigh()            do { LATDbits.LATD1 = 1; } while(0)
#define RD1_SetLow()             do { LATDbits.LATD1 = 0; } while(0)
#define RD1_Toggle()             do { LATDbits.LATD1 = ~LATDbits.LATD1; } while(0)
#define RD1_GetValue()              PORTDbits.RD1
#define RD1_SetDigitalInput()    do { TRISDbits.TRISD1 = 1; } while(0)
#define RD1_SetDigitalOutput()   do { TRISDbits.TRISD1 = 0; } while(0)
#define RD1_SetPullup()             do { WPUDbits.WPUD1 = 1; } while(0)
#define RD1_ResetPullup()           do { WPUDbits.WPUD1 = 0; } while(0)
#define RD1_SetAnalogMode()         do { ANSELDbits.ANSD1 = 1; } while(0)
#define RD1_SetDigitalMode()        do { ANSELDbits.ANSD1 = 0; } while(0)

// get/set RD2 procedures
#define RD2_SetHigh()            do { LATDbits.LATD2 = 1; } while(0)
#define RD2_SetLow()             do { LATDbits.LATD2 = 0; } while(0)
#define RD2_Toggle()             do { LATDbits.LATD2 = ~LATDbits.LATD2; } while(0)
#define RD2_GetValue()              PORTDbits.RD2
#define RD2_SetDigitalInput()    do { TRISDbits.TRISD2 = 1; } while(0)
#define RD2_SetDigitalOutput()   do { TRISDbits.TRISD2 = 0; } while(0)
#define RD2_SetPullup()             do { WPUDbits.WPUD2 = 1; } while(0)
#define RD2_ResetPullup()           do { WPUDbits.WPUD2 = 0; } while(0)
#define RD2_SetAnalogMode()         do { ANSELDbits.ANSD2 = 1; } while(0)
#define RD2_SetDigitalMode()        do { ANSELDbits.ANSD2 = 0; } while(0)

// get/set RD3 procedures
#define RD3_SetHigh()            do { LATDbits.LATD3 = 1; } while(0)
#define RD3_SetLow()             do { LATDbits.LATD3 = 0; } while(0)
#define RD3_Toggle()             do { LATDbits.LATD3 = ~LATDbits.LATD3; } while(0)
#define RD3_GetValue()              PORTDbits.RD3
#define RD3_SetDigitalInput()    do { TRISDbits.TRISD3 = 1; } while(0)
#define RD3_SetDigitalOutput()   do { TRISDbits.TRISD3 = 0; } while(0)
#define RD3_SetPullup()             do { WPUDbits.WPUD3 = 1; } while(0)
#define RD3_ResetPullup()           do { WPUDbits.WPUD3 = 0; } while(0)
#define RD3_SetAnalogMode()         do { ANSELDbits.ANSD3 = 1; } while(0)
#define RD3_SetDigitalMode()        do { ANSELDbits.ANSD3 = 0; } while(0)

// get/set TP5 aliases
#define TP5_TRIS                 TRISDbits.TRISD4
#define TP5_LAT                  LATDbits.LATD4
#define TP5_PORT                 PORTDbits.RD4
#define TP5_WPU                  WPUDbits.WPUD4
#define TP5_OD                   ODCONDbits.ODD4
#define TP5_ANS                  ANSELDbits.ANSD4
#define TP5_SetHigh()            do { LATDbits.LATD4 = 1; } while(0)
#define TP5_SetLow()             do { LATDbits.LATD4 = 0; } while(0)
#define TP5_Toggle()             do { LATDbits.LATD4 = ~LATDbits.LATD4; } while(0)
#define TP5_GetValue()           PORTDbits.RD4
#define TP5_SetDigitalInput()    do { TRISDbits.TRISD4 = 1; } while(0)
#define TP5_SetDigitalOutput()   do { TRISDbits.TRISD4 = 0; } while(0)
#define TP5_SetPullup()          do { WPUDbits.WPUD4 = 1; } while(0)
#define TP5_ResetPullup()        do { WPUDbits.WPUD4 = 0; } while(0)
#define TP5_SetPushPull()        do { ODCONDbits.ODD4 = 0; } while(0)
#define TP5_SetOpenDrain()       do { ODCONDbits.ODD4 = 1; } while(0)
#define TP5_SetAnalogMode()      do { ANSELDbits.ANSD4 = 1; } while(0)
#define TP5_SetDigitalMode()     do { ANSELDbits.ANSD4 = 0; } while(0)

// get/set TP6 aliases
#define TP6_TRIS                 TRISDbits.TRISD5
#define TP6_LAT                  LATDbits.LATD5
#define TP6_PORT                 PORTDbits.RD5
#define TP6_WPU                  WPUDbits.WPUD5
#define TP6_OD                   ODCONDbits.ODD5
#define TP6_ANS                  ANSELDbits.ANSD5
#define TP6_SetHigh()            do { LATDbits.LATD5 = 1; } while(0)
#define TP6_SetLow()             do { LATDbits.LATD5 = 0; } while(0)
#define TP6_Toggle()             do { LATDbits.LATD5 = ~LATDbits.LATD5; } while(0)
#define TP6_GetValue()           PORTDbits.RD5
#define TP6_SetDigitalInput()    do { TRISDbits.TRISD5 = 1; } while(0)
#define TP6_SetDigitalOutput()   do { TRISDbits.TRISD5 = 0; } while(0)
#define TP6_SetPullup()          do { WPUDbits.WPUD5 = 1; } while(0)
#define TP6_ResetPullup()        do { WPUDbits.WPUD5 = 0; } while(0)
#define TP6_SetPushPull()        do { ODCONDbits.ODD5 = 0; } while(0)
#define TP6_SetOpenDrain()       do { ODCONDbits.ODD5 = 1; } while(0)
#define TP6_SetAnalogMode()      do { ANSELDbits.ANSD5 = 1; } while(0)
#define TP6_SetDigitalMode()     do { ANSELDbits.ANSD5 = 0; } while(0)

// get/set nu1 aliases
#define nu1_TRIS                 TRISDbits.TRISD7
#define nu1_LAT                  LATDbits.LATD7
#define nu1_PORT                 PORTDbits.RD7
#define nu1_WPU                  WPUDbits.WPUD7
#define nu1_OD                   ODCONDbits.ODD7
#define nu1_ANS                  ANSELDbits.ANSD7
#define nu1_SetHigh()            do { LATDbits.LATD7 = 1; } while(0)
#define nu1_SetLow()             do { LATDbits.LATD7 = 0; } while(0)
#define nu1_Toggle()             do { LATDbits.LATD7 = ~LATDbits.LATD7; } while(0)
#define nu1_GetValue()           PORTDbits.RD7
#define nu1_SetDigitalInput()    do { TRISDbits.TRISD7 = 1; } while(0)
#define nu1_SetDigitalOutput()   do { TRISDbits.TRISD7 = 0; } while(0)
#define nu1_SetPullup()          do { WPUDbits.WPUD7 = 1; } while(0)
#define nu1_ResetPullup()        do { WPUDbits.WPUD7 = 0; } while(0)
#define nu1_SetPushPull()        do { ODCONDbits.ODD7 = 0; } while(0)
#define nu1_SetOpenDrain()       do { ODCONDbits.ODD7 = 1; } while(0)
#define nu1_SetAnalogMode()      do { ANSELDbits.ANSD7 = 1; } while(0)
#define nu1_SetDigitalMode()     do { ANSELDbits.ANSD7 = 0; } while(0)

// get/set RE0 procedures
#define RE0_SetHigh()            do { LATEbits.LATE0 = 1; } while(0)
#define RE0_SetLow()             do { LATEbits.LATE0 = 0; } while(0)
#define RE0_Toggle()             do { LATEbits.LATE0 = ~LATEbits.LATE0; } while(0)
#define RE0_GetValue()              PORTEbits.RE0
#define RE0_SetDigitalInput()    do { TRISEbits.TRISE0 = 1; } while(0)
#define RE0_SetDigitalOutput()   do { TRISEbits.TRISE0 = 0; } while(0)
#define RE0_SetPullup()             do { WPUEbits.WPUE0 = 1; } while(0)
#define RE0_ResetPullup()           do { WPUEbits.WPUE0 = 0; } while(0)
#define RE0_SetAnalogMode()         do { ANSELEbits.ANSE0 = 1; } while(0)
#define RE0_SetDigitalMode()        do { ANSELEbits.ANSE0 = 0; } while(0)

// get/set LED2 aliases
#define LED2_TRIS                 TRISEbits.TRISE1
#define LED2_LAT                  LATEbits.LATE1
#define LED2_PORT                 PORTEbits.RE1
#define LED2_WPU                  WPUEbits.WPUE1
#define LED2_OD                   ODCONEbits.ODE1
#define LED2_ANS                  ANSELEbits.ANSE1
#define LED2_SetHigh()            do { LATEbits.LATE1 = 1; } while(0)
#define LED2_SetLow()             do { LATEbits.LATE1 = 0; } while(0)
#define LED2_Toggle()             do { LATEbits.LATE1 = ~LATEbits.LATE1; } while(0)
#define LED2_GetValue()           PORTEbits.RE1
#define LED2_SetDigitalInput()    do { TRISEbits.TRISE1 = 1; } while(0)
#define LED2_SetDigitalOutput()   do { TRISEbits.TRISE1 = 0; } while(0)
#define LED2_SetPullup()          do { WPUEbits.WPUE1 = 1; } while(0)
#define LED2_ResetPullup()        do { WPUEbits.WPUE1 = 0; } while(0)
#define LED2_SetPushPull()        do { ODCONEbits.ODE1 = 0; } while(0)
#define LED2_SetOpenDrain()       do { ODCONEbits.ODE1 = 1; } while(0)
#define LED2_SetAnalogMode()      do { ANSELEbits.ANSE1 = 1; } while(0)
#define LED2_SetDigitalMode()     do { ANSELEbits.ANSE1 = 0; } while(0)

// get/set LED1 aliases
#define LED1_TRIS                 TRISEbits.TRISE2
#define LED1_LAT                  LATEbits.LATE2
#define LED1_PORT                 PORTEbits.RE2
#define LED1_WPU                  WPUEbits.WPUE2
#define LED1_OD                   ODCONEbits.ODE2
#define LED1_ANS                  ANSELEbits.ANSE2
#define LED1_SetHigh()            do { LATEbits.LATE2 = 1; } while(0)
#define LED1_SetLow()             do { LATEbits.LATE2 = 0; } while(0)
#define LED1_Toggle()             do { LATEbits.LATE2 = ~LATEbits.LATE2; } while(0)
#define LED1_GetValue()           PORTEbits.RE2
#define LED1_SetDigitalInput()    do { TRISEbits.TRISE2 = 1; } while(0)
#define LED1_SetDigitalOutput()   do { TRISEbits.TRISE2 = 0; } while(0)
#define LED1_SetPullup()          do { WPUEbits.WPUE2 = 1; } while(0)
#define LED1_ResetPullup()        do { WPUEbits.WPUE2 = 0; } while(0)
#define LED1_SetPushPull()        do { ODCONEbits.ODE2 = 0; } while(0)
#define LED1_SetOpenDrain()       do { ODCONEbits.ODE2 = 1; } while(0)
#define LED1_SetAnalogMode()      do { ANSELEbits.ANSE2 = 1; } while(0)
#define LED1_SetDigitalMode()     do { ANSELEbits.ANSE2 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/