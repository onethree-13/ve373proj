//	up	^				  3.3V
//		|		 |  |  |   |   |
//		|		------------------
//		|		|sw Vy Vx 5V GND |				Vy		movement of joystick		Vx		movement of joystick
//		|		|		  		 |				3.3V	<----						0V	       up
//		|		|		  		 |				1.65V   hold						1.65V     hold
//		|		|		  		 |				0V      ---->						3.3V      down
//		|		|	  -----	  	 |
//		|		|	  |	  |		 |
//		|		|	  -----	  	 |
//		|		|		  		 |
//		|		------------------
//	  --|--------------------------------> right





#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_
#include <p32xxxx.h>
#include <plib.h>
void ADC_config(void);
float tank1_dir_x=0;
float tank1_dir_y=0;
float tank1_shoot_x=0;
float tank1_shoot_y=0;
float tank2_dir_x=0;
float tank2_dir_y=0;
float tank2_shoot_x=0;
float tank2_shoot_y=0;

#pragma interrupt AN_ISR ipl6 vector 27
void AN_ISR(void){
tank1_dir_y=( (float)( (int)( (ADC1BUF0/1024.00*3.3+0.005)*100 ) ) )/100;
tank1_dir_x=( (float)( (int)( (ADC1BUF1/1024.00*3.3+0.005)*100 ) ) )/100;
tank1_shoot_y=( (float)( (int)( (ADC1BUF2/1024.00*3.3+0.005)*100 ) ) )/100;
tank1_shoot_x=( (float)( (int)( (ADC1BUF3/1024.00*3.3+0.005)*100 ) ) )/100;
tank2_dir_y=( (float)( (int)( (ADC1BUF4/1024.00*3.3+0.005)*100 ) ) )/100;
tank2_dir_x=( (float)( (int)( (ADC1BUF5/1024.00*3.3+0.005)*100 ) ) )/100;
tank2_shoot_y=( (float)( (int)( (ADC1BUF6/1024.00*3.3+0.005)*100 ) ) )/100;
tank2_shoot_x=( (float)( (int)( (ADC1BUF7/1024.00*3.3+0.005)*100 ) ) )/100;
IFS1bits.AD1IF = 0; 
}

//void __ISR(_ADC_VECTOR, ipl6) ADC10InterruptHandler(void){	
//y=ADC1BUF0/1024.00*3.3;
//y=( (float)( (int)( (y+0.005)*100 ) ) )/100;
//x=ADC1BUF1/1024.00*3.3;
//x=( (float)( (int)( (x+0.005)*100 ) ) )/100;
//mAD1ClearIntFlag();
//}

void ADC_config(void){
//DDPCONbits.JTAGEN = 0;
//TRISB=0x0;
//CM1CONbits.COE=0;
//CM2CONbits.COE=0;
AD1PCFG=0xC0;//AN0 ~ AN5 & AN8 & AN9 analog
AD1CSSL=0x33F;//scan AN0 ~ AN5 & AN8 & AN9
AD1CON2bits.VCFG=0b000;// Voltage refernces from AVdd and AVss (power rails)
AD1CON2bits.OFFCAL=0;// turn off calibration mode
AD1CON2bits.CSCNA=1;// turn on auto-scanning of inputs
AD1CON2bits.SMPI=0b0111;//interrupt every 8 sample conversion
AD1CON2bits.BUFM=0;// one 16-word buffer (not using interrupts)
AD1CON2bits.ALTS=0;// Use Mux A only

AD1CON3bits.ADRC=0;//PBCLK
AD1CON3bits.SAMC=0x5;//5TAD=auto sample bits
AD1CON3bits.ADCS=0x0;//TAD=2TPB

AD1CON1bits.SSRC=0b0111;//auto convert at end of Tsample
AD1CON1bits.ASAM=1;//auto sample at end of Tconvert
AD1CON1bits.CLRASAM=0;//overwrite buffer on each interrupt
AD1CON1bits.FORM=0b000;//16 bit integer

//IFS1CLR=0x2;//clear interrupt flag
//IEC1SET=0x2;//enable AD1 interrupt
//IPC6SET=0xC000000;//priority level 3
ConfigIntADC10(ADC_INT_PRI_6 | ADC_INT_SUB_PRI_3 | ADC_INT_ON);
mAD1ClearIntFlag();

AD1CON1bits.ON=1;//turn on ADC moodule

}
#endif