// 
// js1_move_pwm is for left hand joystick which controls move_dir
// js1_shoot_pwm is for right hand joystick which controls shoot_dir
// ...
// range for each joystick pwm is 0~FULL_PWM

#ifndef _MOTOR_H_
#define _MOTOR_H_
#include <p32xxxx.h>
#include <plib.h>
#include <stdio.h>
#define SYS_FREQ (80000000)
#define FULL_PWM PR2

void PWM_config(void);

int js1_move_pwm=0;
int js2_move_pwm=0;
int js1_shoot_pwm=0;
int js2_shoot_pwm=0;
//unsigned int acc = 30;

#pragma interrupt PWM_ISR ipl5 vector 8
void PWM_ISR (void) {
//OC1RS = js1_move_pwm; //update duty cycle register
//js1_move_pwm = js1_move_pwm + acc;
//if (js1_move_pwm<0) {js1_move_pwm = 0;acc=-acc;}
//else if (js1_move_pwm>FULL_PWM/20) {js1_move_pwm = FULL_PWM/20;acc=-acc;}

js1_move_pwm=FULL_PWM/20;
OC1RS = js1_move_pwm; //update duty cycle register
OC2RS = js1_shoot_pwm; //update duty cycle register
OC3RS = js2_move_pwm; //update duty cycle register
OC4RS = js2_shoot_pwm; //update duty cycle register
IFS0CLR = 0x0100; //clear Timer 2 interrupt flag
}

void PWM_config(){
TRISDbits.TRISD0=0;//RD0->OC1 is output
TRISDbits.TRISD1=0;//RD1->OC2 is output
TRISDbits.TRISD2=0;//RD2->OC3 is output
TRISDbits.TRISD3=0;//RD3->OC4 is output

OC1CON = 0; //stop OC1 module
OC1RS = 0; //initialize duty cycle register
OC1R = 0; //initialize OC1R register for the first time
OC1CONbits.OCM=0b110;//PWM mode on OC1;16-bit TMR 2

OC2CON = 0; //stop OC2 module
OC2RS = 0; //initialize duty cycle register
OC2R = 0; //initialize OC2R register for the first time
OC2CONbits.OCM=0b110;//PWM mode on OC2;16-bit TMR 2

OC3CON = 0; //stop OC3 module
OC3RS = 0; //initialize duty cycle register
OC3R = 0; //initialize OC3R register for the first time
OC3CONbits.OCM=0b110;//PWM mode on OC3;16-bit TMR 2

OC4CON = 0; //stop OC4 module
OC4RS = 0; //initialize duty cycle register
OC4R = 0; //initialize OC4R register for the first time
OC4CONbits.OCM=0b110;//PWM mode on OC4;16-bit TMR 2

//TMR2 config
PR2 = 0xFFFF; //PWM signal period = 65536*1/PBCLK = 0.8192ms
IFS0CLR = 0x100; //clear Timer 2 interrupt
IEC0SET = 0x100; //enable Timer 2 interrupt
IPC2SET = 0x14; //Timer 2 interrupt priority 5
T2CONSET = 0x8000; //start Timer 2

OC1CONSET = 0x8000; //enable OC1 module for PWM generation
OC2CONSET = 0x8000; //enable OC2 module for PWM generation
OC3CONSET = 0x8000; //enable OC3 module for PWM generation
OC4CONSET = 0x8000; //enable OC4 module for PWM generation
}
#endif
