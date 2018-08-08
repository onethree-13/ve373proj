#ifndef _CN_H_
#define _CN_H_
#include <p32xxxx.h>
#include <plib.h>
#include <stdio.h> 
#include <stdlib.h>

#pragma interrupt CN_ISR ipl7 vector 26
void CN_ISR (void);

void CN_config(){
CNCONbits.ON = 1;
CNEN = 0x8000;    //Enable RD6 change notice
//readD=PORTDbits.RD6;
IPC6SET = 0x001C0000; //priority level 7, subpriority level 3
IPC6SET = 0x00030000;
IFS1CLR = 0x0001; //Clear interrupt flag
IEC1SET = 0x0001; //Enable Change Notice interrupts
}

#endif
