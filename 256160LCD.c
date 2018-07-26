#include <p32xxxx.h>
#include "256160LCD.h"
#include <plib.h>

#define SYS_FREQ (80000000)
#define PBCLK (SYS_FREQ / 1)

//RST SDA SCK
#define SDA PORTDbits.RD9
#define SCK PORTDbits.RD10

#define VSS PORTDbits.RD0
#define VDD PORTDbits.RD1  //slave's address


/* initialize the PIC32 MCU */
void MCU_init(void)
{
    /* setup I/O ports to connect to the LCD module */
    TRISDCLR = 0x00FF;
    TRISECLR = 0x00FF;
}


/* configure timer SFRs to generate num us delay*/
void DelayUsec(unsigned int msec)
{
    unsigned int tWait, tStart;
    tWait = (SYS_FREQ / 2000000) * msec;
    tStart = ReadCoreTimer();
    while ((ReadCoreTimer() - tStart) < tWait)
        ; // wait for the time to pass
}

/*
void I2C_init(void)
{
	I2C1CONbits.SIDL = 0;       // Stop in Idle Mode bit                        -> Continue module operation when the device enters Idle mode
	I2C1CONbits.A10M = 1;       // 7-bit Slave Address Flag bit                 -> I2CxADD register is a 7-bit slave address
	I2C1CONbits.DISSLW = 1;     // Slew Rate Control Disable bit                -> Slew rate control disabled for Standard Speed mode (100 kHz)
	I2C1CONbits.ACKDT = 0;      // Acknowledge Data bit                         -> ~ACK is sent
	I2C1BRG = 0x0F3;            // Baud Rate Generator set to provide 100KHz for SCL with 50 MHz xtal. 
}
*/

/*
void Send_Data(unsigned int message)
{
	I2C1CONbits.ON = 1;     //enable I2C module
	
	// Assert a start condition on SDAx and SCLx
	I2C1CONbits.PEN = 0;   // stop condition enable bit
	I2C1CONbits.SEN = 1;   // start condition enable bit
	while(I2C1CONbits.SEN == 1);  // SEN is to be cleared when I2C Start procedure has been completed
	
	// load data on the bus
	I2C1TRN = 0b0111100;     // write slave's address (P37)
	while(I2X1STATbits.TRSTAT == 1);   //MASTER Transmit still in progress
	while(I2C1STATbits.ACKSTAT == 1);  // Master should receive the ACK from Slave, which will clear the I2C1STAT<ACKSTAT> bit. 
	
	start_flag();
	
	I2C1TRN = message;
	while(I2C1STATbits.TRSTAT == 1);
	while(I2C1STATbits.ACKSTAT == 1);
	
	stop_flag();
	
	I2C1CONbits.PEN = 1;  //stop condition enable bit
	
	DelayUsec(120);
}
*/

void start_flag(void)
{
	SCK = 1;
	SDA = 1;
	SDA = 0;	
}

void stop_flag(void)
{
	SCK = 1;
	SDA = 0;
	SDA = 1;
}

void transfer(UINT8 data1)
{
	int i;
	for(i = 0; i < 8; i++)
	{
		SCK = 0;
		if (data1&0x80) SDA = 1;
		else SDA = 0;
		SCK = 1;
		SCK = 0;
		data1 = data1 << 1;
	}
	SDA = 0;
	SCK = 1;
	SCK = 0;
}

void LCD_putcmd(UINT8 com) //write command to address
{
	start_flag();
	transfer(0x78);
	transfer(0x80);
	transfer(com);
	stop_flag();
}

void LCD_putchar(UINT8 data)  //write data to LCD
{
	start_flag();
	transfer(0x78);
	transfer(0xC0);
	transfer(data);
	stop_flag();
}

void LCD_graylevel(void)
{
    LCD_putcmd(LCD_GRAY_SET); // Gray Level
    LCD_putchar(0x01);
    LCD_putchar(0x03);
    LCD_putchar(0x05);
    LCD_putchar(0x07);
    LCD_putchar(0x09);
    LCD_putchar(0x0b);
    LCD_putchar(0x0d);
    LCD_putchar(0x10);
    LCD_putchar(0x11);
    LCD_putchar(0x13);
    LCD_putchar(0x15);
    LCD_putchar(0x17);
    LCD_putchar(0x19);
    LCD_putchar(0x1b);
    LCD_putchar(0x1d);
    LCD_putchar(0x1f);
}

void LCD_init(void)
{
    // LCD_reset();
    LCD_putcmd(LCD_EXT_CMD1);
    LCD_putcmd(LCD_STOP_IDLE);
    LCD_putcmd(LCD_EXT_CMD2);
    LCD_putcmd(LCD_AUTOREAD_SET); //Autoread control
    LCD_putchar(0X9F);            //Autoread disable
    //LCD_putcmd(LCD_ANA_SET);      //Analog SET
    LCD_putchar(0x00);            //OSC Frequency adjustment
    LCD_putchar(0x01);            //Frequency on booster capacitors->6KHz
    LCD_putchar(0x03);            //Bias=1/11
    LCD_graylevel();
    LCD_putcmd(LCD_EXT_CMD1);      //EXT=0
    LCD_putcmd(LCD_PAGE_ADDR_SET); //Page Address setting
    LCD_putchar(0X00);             // XS=0
    LCD_putchar(0X28);             // XE=159
    LCD_putcmd(LCD_COLM_ADDR_SET); //Clumn Address setting
    LCD_putchar(0X00);             // XS=0
    LCD_putchar(0Xff);             // XE=256 ff
    LCD_putcmd(LCD_SCAN_SET);      //Data scan direction
    LCD_putchar(0x00);             //MX.MY=Normal

    //LCD_putcmd(LCD_HIGH_FIST); //0x0C low first D0-D7
	
    LCD_putcmd(LCD_DSP_CON);  //Display Control
    LCD_putchar(0X00);         //
    LCD_putchar(0X9F);         //Duty=160
    LCD_putchar(0X20);         //Nline=off
    LCD_putcmd(LCD_DSP_MODE); //Display Mode
    LCD_putchar(0X10);         //10=Monochrome Mode,11=4Gray
    LCD_putcmd(LCD_EV_CON);    //EV control
    LCD_putchar(0x08);         //VPR[5-0]
    LCD_putchar(0x04);         //VPR[8-6]
    LCD_putcmd(LCD_POW_CON);   //Power control
    LCD_putchar(0x0B);         //D0=regulator ; D1=follower ; D3=booste, on:1 off:0
    DelayUsec(100);
    //LCD_putcmd(LCD_PIXEL_ON); // All pixel on
    LCD_putcmd(LCD_ICON_ON); // Enable ICON RAM
    LCD_putcmd(LCD_DSP_ON); //Display o
	
}

void clear_screen(int x, int y)
{
    int i, j;
    //LCD_address(x, y, LCD_DISP_WITH, LCD_DISP_HEIGHT);
    LCD_putcmd(LCD_EXT_CMD1);
    LCD_putcmd(LCD_DSP_ON); //Display on
    for (i = 0; i < LCD_DSP_HEIGHT; i++)
    {
        for (j = 0; j < LCD_DSP_WITH; j++)
        {
            LCD_putchar(0x00);
        }
    }
}

void LCD_disp(int x, int y, char *dp)
{
    int i, j;
    //LCD_address(x, y, LCD_DISP_WITH, LCD_DISP_HEIGHT);
    LCD_putcmd(LCD_EXT_CMD1);
    LCD_putcmd(LCD_DSP_ON); //Display on
    for (i = 0; i < LCD_DSP_HEIGHT; i++)
    {
        for (j = 0; j < LCD_DSP_WITH; j++)
        {
            LCD_putchar(*dp);
            dp++;
        }
    }
    LCD_putcmd(LCD_EXT_CMD1);
    LCD_putcmd(LCD_DSP_ON); //Display on
    //LCD_putcmd(0xD6);
    //LCD_putcmd(0xD7);
}








int main(void)
{
	// Set all analog pins to be digital I/O
   	AD1PCFG = 0xFFFF;

	//Setup TRIS bits for switches and I2C pins
	TRISAbits.TRISA14=0;
	TRISAbits.TRISA15=0;
	
	//I2C_init();
	LCD_init();
	
	/*
	Send_Data(0x75); // set page address
	DelayUsec(120);
	Send_Data(0x00); // start page address
	DelayUsec(120);
	Send_Data(0x15); // set column address
	DelayUsec(120);
	Send_Data(0x00); // start column address
	DelayUsec(120);
	Send_Data(0x5C); // write
	DelayUsec(120);
	Send_Data();  // address of the character
	*/
	
	clear_screen(1, 1);
    LCD_disp(1, 1, bmp1);
	
	while (1);
}










