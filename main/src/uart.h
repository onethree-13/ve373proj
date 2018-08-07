#ifndef _ARDUINO_UART_H_
#define _ARDUINO_UART_H_
#include <p32xxxx.h>
#include <plib.h>

#define U1TX PORTFbits.RF3
// J11 43
#define U1RX PORTFbits.RF2
// J11 41

#define SYS_CLOCK (80000000)

void DelayUsec(unsigned int usec)
{
    unsigned int tWait, tStart;
    tWait = (SYS_CLOCK / 2000000) * usec;
    tStart = ReadCoreTimer();
    while ((ReadCoreTimer() - tStart) < tWait)
        ; // wait for the time to pass
}

void DelayMsec(unsigned int msec)
{
    unsigned int tWait, tStart;
    tWait = (SYS_CLOCK / 2000) * msec;
    tStart = ReadCoreTimer();
    while ((ReadCoreTimer() - tStart) < tWait)
        ; // wait for the time to pass
}

void initIntGlobal()
{
    INTCONbits.MVEC = 1; // Enable multiple vector interrupt
    asm("ei");           // Enable all interrupts
}

void U1_TX(char c)
{
    while (!U1STAbits.TRMT)
        ;
    U1TXREG = c;
}

void UART_init()
{
    U1BRG = 2082;    // Set Baud rate 9600
    U1MODE = 0x8008; // Enable UART, 8-bit data
                     // No Parity, 1 Stop bit
                     // high speed mode
    U1STA = 0x0400;  // Enable Transmit
    // U1RX_ISR
    asm("di");
    IFS0CLR = 0x08000000; // Clear interrupt flag
    IEC0SET = 0x08000000; // Enable U1RX interrupt
    IPC6SET = 0x00000018; // Set priority level = 6
    IPC6SET = 0x00000003; // Set subpriority level = 3
    asm("ei");
}

/*
int main(void)
{
    initIntGlobal();
    UART_init();
    while (1)
        ;
}
*/

#endif
