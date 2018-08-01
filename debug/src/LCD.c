#include <plib.h>
#include <p32xxxx.h>
#include "../../main/src/HardwareProfile.h"
#include "../../main/src/i2c_master.h"
#include "../../main/src/LCD.h"

int main()
{
    InitI2C();
    InitLCD();
    while (1)
    {
        TransferCommand(0x23);

        DelayMsec(100);
        TransferCommand(0x30);
        TransferCommand(0xAF); //Display on
        DelayMsec(100);
    }
}
