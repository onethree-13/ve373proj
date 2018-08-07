#ifndef _HARDWAREPROFILE_H_
#define _HARDWAREPROFILE_H_

#define SYS_CLOCK (80000000)
#define GetSystemClock() (SYS_CLOCK)
#define GetPeripheralClock() (SYS_CLOCK) // FPBDIV = DIV_1
#define GetInstructionClock() (SYS_CLOCK)
#define I2C_CLOCK_FREQ 100000 // MAX 400 kHz

// EEPROM Constants
#define EEPROM_I2C_BUS I2C1
#define EEPROM_ADDRESS 0b0111100

void DelayUsec(unsigned int usec)
{
    unsigned int tWait, tStart;
    tWait = (SYS_CLOCK / 2000000) * usec;
    tStart = ReadCoreTimer();
    while ((ReadCoreTimer() - tStart) < tWait)
        ; // wait for the time to pass
}

void DelayMsec(unsigned int msec)
{
    unsigned int tWait, tStart;
    tWait = (SYS_CLOCK / 2000) * msec;
    tStart = ReadCoreTimer();
    while ((ReadCoreTimer() - tStart) < tWait)
        ; // wait for the time to pass
}

#endif
