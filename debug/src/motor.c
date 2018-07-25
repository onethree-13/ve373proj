#include "E:\ve373proj\main\src\motor.h"
int main() {
OSCSetPBDIV (OSC_PB_DIV_1);
INTCONbits.MVEC = 1; // Enable multiple vector interrupt
asm("ei"); // Enable all interrupts
PWM_config();
TMR2=0;
while (1);
}
