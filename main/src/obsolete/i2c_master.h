#ifndef _I2C_MASTER_H_
#define _I2C_MASTER_H_

#include <plib.h>
#include <p32xxxx.h>
#include "HardwareProfile.h"
#include <stdio.h>
#ifdef PIC32_STARTER_KIT
#include <stdio.h>
#endif

#define TRANSFER_COMMAND 0x80
#define TRANSFER_DATA 0xC0

// Configuration Bit settings
//
// SYSCLK = 80 MHz (8MHz Crystal/ FPLLIDIV * FPLLMUL / FPLLODIV)
// PBCLK = 80 MHz
// WDT OFF
#ifndef OVERRIDE_CONFIG_BITS

#pragma config FPLLMUL = MUL_20  // PLL Multiplier
#pragma config FPLLIDIV = DIV_2  // PLL Input Divider
#pragma config FPLLODIV = DIV_1  // PLL Output Divider
#pragma config FPBDIV = DIV_1    // Peripheral Clock divisor
#pragma config FWDTEN = OFF      // Watchdog Timer
#pragma config WDTPS = PS1       // Watchdog Timer Postscale
#pragma config FCKSM = CSDCMD    // Clock Switching & Fail Safe Clock Monitor
#pragma config OSCIOFNC = OFF    // CLKO Enable
#pragma config POSCMOD = HS      // Primary Oscillator
#pragma config IESO = OFF        // Internal/External Switch-over
#pragma config FSOSCEN = OFF     // Secondary Oscillator Enable
#pragma config FNOSC = PRIPLL    // Oscillator Selection
#pragma config CP = OFF          // Code Protect
#pragma config BWP = OFF         // Boot Flash Write Protect
#pragma config PWP = OFF         // Program Flash Write Protect
#pragma config ICESEL = ICS_PGx2 // ICE/ICD Comm Channel Select
#pragma config DEBUG = OFF       // Debugger Disabled for Starter Kit

#endif // OVERRIDE_CONFIG_BITS

int InitI2C(void)
{
    I2C1CONbits.SIDL = 0;   // Stop in Idle Mode bit                        -> Continue module operation when the device enters Idle mode
    I2C1CONbits.A10M = 0;   // 10-bit Slave Address Flag bit                -> I2CxADD register is a 7-bit slave address
    I2C1CONbits.DISSLW = 1; // Slew Rate Control Disable bit                -> Slew rate control disabled for Standard Speed mode (100 kHz)
    I2C1CONbits.ACKDT = 0;  // Acknowledge Data bit                         -> ~ACK is sent
    I2C1BRG = 0x0F3;        // Baud Rate Generator set to provide 100KHz for SCL with 50 MHz xtal.
}

void StartTransfer()
{
    // 1. Turn on the I2C module by setting the ON bit (I2CxCON<15>) to ‘1’.
    I2C1CONbits.ON = 1; // I2C Enable bit                               -> Enables the I2C module and configures the SDAx and SCLx pins as serial port pins

    //------------- WRITE begins here ------------
    // 2. Assert a Start condition on SDAx and SCLx.
    I2C1CONbits.PEN = 0; // Stop Condition Enable Bit                    -> Stop Condition Idle
    I2C1CONbits.SEN = 1; // Start Condition Enable bit                   -> Initiate Start condition on SDAx and SCLx pins; cleared by module
    while (I2C1CONbits.SEN == 1)
        ; // SEN is to be cleared when I2C Start procedure has been completed

    // 3. Load the Data on the bus
    I2C1TRN = 0b01111000; // Write the slave address to the transmit register for I2C WRITE
    while (I2C1STATbits.TRSTAT == 1)
        ; // MASTER Transmit still in progress
    while (I2C1STATbits.ACKSTAT == 1)
        ; // Master should receive the ACK from Slave, which will clear the I2C1STAT<ACKSTAT> bit.
}

void Transfer(UINT8 data)
{
    I2C1TRN = data; // Register Address
    while (I2C1STATbits.TRSTAT == 1)
        ;
    while (I2C1STATbits.ACKSTAT == 1)
        ;
}

void StopTransfer()
{
    I2C1CONbits.PEN = 1; // Stop Condition Enable Bit
}

void TransferCommand(UINT8 data)
{
    StartTransfer();
    Transfer(0x00);
    Transfer(data);
    StopTransfer();
}

void TransferArg(UINT8 data)
{
    StartTransfer();
    Transfer(0x40);
    Transfer(data);
    StopTransfer();
}

void TransferDataHelper(UINT8 *data, int num)
{
    int i;
    StartTransfer();
    Transfer(0x40);
    for (i = 0; i < num; i++)
        Transfer(data[i]);
    StopTransfer();
}

void TransferData(UINT8 *data, int num)
{
    while (num > 24)
    {
        TransferDataHelper(data, 24);
        data += 24;
        num -= 24;
    }
    TransferDataHelper(data, num);
}

#endif
