#ifndef _CN_H_
#define _CN_H_
#include <p32xxxx.h>
#include <plib.h>
#include <stdio.h> 
#include <stdlib.h>

//#pragma interrupt CN_ISR ipl7 vector 26
// void CN_ISR (void);

void CN_config(){
CNCONbits.ON = 1;
CNEN = 0x10000;    //Enable RD7 change notice
CNPUE = 0x000010000; //Enable weak pull ups for pins CN16(RD7)

//readD=PORTDbits.RD6;
IPC6SET = 0x001C0000; //priority level 7, subpriority level 3
IPC6SET = 0x00030000;
IFS1CLR = 0x0001; //Clear interrupt flag
IEC1SET = 0x0001; //Enable Change Notice interrupts
}

#endif
