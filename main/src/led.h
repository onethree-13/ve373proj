#ifndef _LED_H_
#define _LED_H_
#include <p32xxxx.h>
#include <plib.h>
#include "tank.h"
void LED_config(void){
	TRISE = 0xC0;
}

void UpdateHPStat()
{
	PORTEbits.RE0 = (tank1.HP >=1)?1:0;
	PORTEbits.RE1 = (tank1.HP >=2)?1:0;
	PORTEbits.RE2 = (tank1.HP >=3)?1:0;
	PORTEbits.RE3 = (tank2.HP >=1)?1:0;
	PORTEbits.RE4 = (tank2.HP >=2)?1:0;
	PORTEbits.RE5 = (tank2.HP >=3)?1:0;
}

#endif
