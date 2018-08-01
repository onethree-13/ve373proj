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

#pragma interrupt U1RX_ISR ipl6 vector 24
void U1RX_ISR()
{
    IEC0CLR = 0x08000000; // Disable U1RX interrupt
    UINT8 c = U1RXREG;
    IFS0CLR = 0x08000000; // Clear interrupt flag
    IEC0SET = 0x08000000; // Enable U1RX interrupt
}

void CN_init(void)
{
    /* Disable vector interrupts prior to configuration */
    asm("di");
    /* Configure CN module */
    CNCON = 0x8000;     //Enable Change Notice module
    CNEN = 0x00008000;  //Enable individual CN pins
    CNPUE = 0x00008000; //Enable weak pull ups for pins CN15(RD6)
    /* Configure CN interrupt */
    IPC6SET = 0x001C0000; //Set priority level = 7
    IPC6SET = 0x00030000; //Set subpriority level = 3
    IFS1CLR = 0x0001;     //Clear interrupt flag
    IEC1SET = 0x0001;     //Enable Change Notice interrupts
    /* Re-enable all interrupt */
    asm("ei");
}

#pragma interrupt CN_ISR ipl7 vector 26
void CN_ISR(void)
{
    IEC1CLR = 0x0001; //disable interrupt
    U1_TX(0x41);
    DelayMsec(1000);
    //clear mismatch conditions
    IFS1CLR = 0x0001; //clear interrupt flag
    IEC1SET = 0x0001; //re-enable interrupt
}

void UART_init()
{
    U1BRG = 2082;    // Set Baud rate 9600
    U1MODE = 0x8008; // Enable UART, 8-bit data
                     // No Parity, 1 Stop bit
                     // high speed mode
    U1STA = 0x1400;  // Enable Transmit and Recieve
    // TRISDCLR = 0x8000; // set U1RTS as output
    // TRISDSET = 0x4000; // set U1CTS as input

    // U1RX_ISR
    asm("di");
    IFS0CLR = 0x08000000; // Clear interrupt flag
    IEC0SET = 0x08000000; // Enable U1RX interrupt
    IPC6SET = 0x00000018; // Set priority level = 6
    IPC6SET = 0x00000003; // Set subpriority level = 3
    asm("ei");
}

int main(void)
{
    initIntGlobal();
    UART_init();
    CN_init();
    while (1)
        ;
}
