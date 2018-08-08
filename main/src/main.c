#include "uart.h"
#include "joystick.h"
#include "motor.h"

#include "map.h"
#include "bullet.h"
#include "tank.h"
#include "game.h"
#include "CN.h"

#include <stdlib.h>
#include <stdio.h>
// Configuration Bits
#pragma config FNOSC = PRIPLL    // Oscillator Selection
#pragma config FPLLIDIV = DIV_2  // PLL Input Divider
#pragma config FPLLMUL = MUL_20  // PLL Multiplier
#pragma config FPLLODIV = DIV_1  // PLL Output Divider
#pragma config FPBDIV = DIV_1    // Peripheral Clock divisor
#pragma config FWDTEN = OFF      // Watchdog Timer
#pragma config WDTPS = PS1       // Watchdog Timer Postscale
#pragma config FCKSM = CSDCMD    // Clock Switching & Fail Safe Clock Monitor
#pragma config OSCIOFNC = OFF    // CLKO Enable
#pragma config POSCMOD = XT      // Primary Oscillator
#pragma config IESO = OFF        // Internal/External Switch-over
#pragma config FSOSCEN = OFF     // Secondary Oscillator Enable
#pragma config CP = OFF          // Code Protect
#pragma config BWP = OFF         // Boot Flash Write Protect
#pragma config PWP = OFF         // Program Flash Write Protect
#pragma config ICESEL = ICS_PGx2 // ICE/ICD Comm Channel Select
#pragma config DEBUG = OFF       // Debugger Disabled for Starter Kit
void InitHareware();

void CN_ISR()
{
	DelayMsec(1000);
    GameStart();
    while (!CheckGameStat())
    {
        GameRound();
        SendMap();
        DelayMsec(5000);
    }
    SendGameStat(CheckGameStat());
}

int main()
{
	
    InitHareware();
    while (1);
}
void InitHareware()
{
    // Initial joystick
	ADC_config();
    // Initial motor
	PWM_config();
	CN_config();
    // Initial Change Notice
	UART_init();
	INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
	asm("ei");
	//asm("nop");
}
