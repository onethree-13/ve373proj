#include <plib.h>
#include <p32xxxx.h>
#include "../../main/src/HardwareProfile.h"
#include "../../main/src/i2c_master.h"
#include "../../main/src/LCD.h"

int main()
{
    InitI2C();
    InitLCD();
    clear_screen(1, 1);
    LCD_disp(1, 1, bmp1);

    StartTransfer();
    TransferCommand(0x30);
    // Extension Command 1
    TransferCommand(0xAF);
    // Display OFF
    StopTransfer();
    LCD_OTP_Write();
    while (1)
        ;
}
