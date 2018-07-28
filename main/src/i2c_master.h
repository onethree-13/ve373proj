#ifndef _I2C_MASTER_H_
#define _I2C_MASTER_H_

#include <plib.h>
#include <p32xxxx.h>
#include "HardwareProfile.h"
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
    // UINT32 actualClock;
    // TRISDbits.TRISD9 = 0;
    // TRISDbits.TRISD10 = 0;

    I2CSetFrequency(EEPROM_I2C_BUS, GetPeripheralClock(), I2C_CLOCK_FREQ);
    I2CEnable(EEPROM_I2C_BUS, TRUE);
}

void StartTransfer()
{
    while (!I2CBusIsIdle(EEPROM_I2C_BUS))
        ;
    I2CStart(EEPROM_I2C_BUS);

    I2CSendByte(EEPROM_I2C_BUS, 0x78);
    while (!I2CByteWasAcknowledged(EEPROM_I2C_BUS))
        ;
}

void Transfer(UINT8 data)
{
    I2CSendByte(EEPROM_I2C_BUS, data);
    while (!I2CByteWasAcknowledged(EEPROM_I2C_BUS))
        ;
}

void StopTransfer()
{
    I2CStop(EEPROM_I2C_BUS);
}

#define TransferCommand(data) \
    Transfer(0x80);           \
    Transfer(data)
#define TransferData(data) \
    Transfer(0xC0);        \
    Transfer(data)

//FIXME: experimental
void TransferDataList(UINT8 *data)
{
    Transfer(0x40);
    while (*data)
    {
        Transfer(*data);
        data++;
    }
}

#endif
