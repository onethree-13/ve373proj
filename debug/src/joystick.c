#include <p32xxxx.h>
#include <plib.h>
#include "E:\ve373proj\main\src\joystick.h"
#define SYS_FREQ 80000000

int main() {
    OSCSetPBDIV (OSC_PB_DIV_1); //configure PBDIV so PBCLK = SYSCLK
    SYSTEMConfig(SYS_FREQ, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);
    ADC_config(); // config the ADC
	//asm("ei");
	INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR); 
	INTEnableInterrupts();
    while(1){ 
	}
}




