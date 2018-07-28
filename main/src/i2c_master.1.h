#ifndef _I2C_MASTER_H_
#define _I2C_MASTER_H_

#include <plib.h>
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

BOOL StartTransfer(BOOL restart)
{
    I2C_STATUS status;

    if (restart)
    {
        I2CRepeatStart(EEPROM_I2C_BUS);
    }
    else
    {
        // Wait for the bus to be idle, then start the transfer
        while (!I2CBusIsIdle(EEPROM_I2C_BUS))
            ;

        if (I2CStart(EEPROM_I2C_BUS) != I2C_SUCCESS)
        {
            DBPRINTF("Error: Bus collision during transfer Start\n");
            return FALSE;
        }
    }

    // Wait for the signal to complete
    do
    {
        status = I2CGetStatus(EEPROM_I2C_BUS);

    } while (!(status & I2C_START));

    return TRUE;
}

BOOL TransmitOneByte(UINT8 data)
{
    // Wait for the transmitter to be ready
    while (!I2CTransmitterIsReady(EEPROM_I2C_BUS))
        ;

    // Transmit the byte
    if (I2CSendByte(EEPROM_I2C_BUS, data) == I2C_MASTER_BUS_COLLISION)
    {
        DBPRINTF("Error: I2C Master Bus Collision\n");
        return FALSE;
    }

    // Wait for the transmission to finish
    while (!I2CTransmissionHasCompleted(EEPROM_I2C_BUS))
        ;

    return TRUE;
}

void StopTransfer(void)
{
    I2C_STATUS status;

    // Send the Stop signal
    I2CStop(EEPROM_I2C_BUS);

    // Wait for the signal to complete
    do
    {
        status = I2CGetStatus(EEPROM_I2C_BUS);

    } while (!(status & I2C_STOP));
}

int InitI2C(void)
{
    UINT32 actualClock;

    // Initialize debug messages (when supported)
    DBINIT();

    // Set the I2C baudrate
    actualClock = I2CSetFrequency(EEPROM_I2C_BUS, GetPeripheralClock(), I2C_CLOCK_FREQ);
    if (abs(actualClock - I2C_CLOCK_FREQ) > I2C_CLOCK_FREQ / 10)
    {
        DBPRINTF("Error: I2C1 clock frequency (%u) error exceeds 10%%.\n", (unsigned)actualClock);
    }

    // Enable the I2C bus
    I2CEnable(EEPROM_I2C_BUS, TRUE);
}
void Transfer(UINT8 ctrl, UINT8 data)
{
    UINT8 i2cData[10];
    I2C_7_BIT_ADDRESS SlaveAddress;
    int Index;
    int DataSz = 4;
    BOOL Acknowledged;
    BOOL Success = TRUE;

    // Initialize the data buffer
    I2C_FORMAT_7_BIT_ADDRESS(SlaveAddress, EEPROM_ADDRESS, I2C_WRITE);
    i2cData[0] = SlaveAddress.byte;
    i2cData[1] = 0x78; // EEPROM location to program (high address byte)
    i2cData[2] = ctrl; // EEPROM location to program (low address byte)
    i2cData[3] = data; // Data to write

    // Start the transfer to write data to the EEPROM
    StartTransfer(FALSE);

    Index = 0;
    while (Success && (Index < DataSz))
    {
        if (TransmitOneByte(i2cData[Index]))
        {
            Index++;
            if (!I2CByteWasAcknowledged(EEPROM_I2C_BUS))
            {
                DBPRINTF("Error: Sent byte was not acknowledged\n");
                Success = FALSE;
            }
        }
        else
        {
            Success = FALSE;
        }
    }

    StopTransfer();
}

void transfer_data_lcd(UINT8 data)
{
    Transfer(TRANSFER_DATA, data);
}
void transfer_command_lcd(UINT8 data)
{
    Transfer(TRANSFER_COMMAND, data);
}

#endif
