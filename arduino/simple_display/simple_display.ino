#include <Arduino.h>
#include <SPI.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

 //U8G2_ST75256_JLX256160_1_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 52, /* data=*/ 51, /* cs=*/ 53, /* dc=*/ 9, /* reset=*/ 8);
/* https://www.mouser.com/catalog/specsheets/ArduinoBoardMega2560.pdf */
U8G2_ST75256_JLX256160_F_HW_I2C u8g2(U8G2_MIRROR, /*clock=*/21,  /*data = */ 20, /*reset=*/ 8);


#define mapElement_w 20
#define mapElement_h 20

static uint8_t tank1_left[] = {
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0xf0, 0xff, 0x0f,
  0xf0, 0xff, 0x0f,
  0xf0, 0xff, 0x0f,
  0xc0, 0xff, 0x03,
  0xc0, 0xff, 0x03,
  0xc0, 0xff, 0x03,
  0xff, 0xff, 0x03,
  
  0xff, 0xff, 0x03,
  0xc0, 0xff, 0x03,
  0xc0, 0xff, 0x03,
  0xc0, 0xff, 0x03,
  0xf0, 0xff, 0x0f,
  0xf0, 0xff, 0x0f,
  0xf0, 0xff, 0x0f,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
};

static uint8_t tank2_left[] = {
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0xf0, 0xff, 0x0f,
  0xf0, 0xff, 0x0f,
  0xf0, 0xff, 0x0f,
  0xc0, 0x00, 0x03,
  0xc0, 0x00, 0x03,
  0xc0, 0x00, 0x03,
  0xff, 0x00, 0x03,
  
  0xff, 0x00, 0x03,
  0xc0, 0x00, 0x03,
  0xc0, 0x00, 0x03,
  0xc0, 0x00, 0x03,
  0xf0, 0xff, 0x0f,
  0xf0, 0xff, 0x0f,
  0xf0, 0xff, 0x0f,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
};

static uint8_t tank1_right[] = {
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0xff, 0xff, 0x00,
  0xff, 0xff, 0x00,
  0xff, 0xff, 0x00,
  0xfc, 0x3f, 0x00,
  0xfc, 0x3f, 0x00,
  0xfc, 0x3f, 0x00,
  0xfc, 0xff, 0x0f,
  
  0xfc, 0xff, 0x0f,
  0xfc, 0x3f, 0x00,
  0xfc, 0x3f, 0x00,
  0xfc, 0x3f, 0x00,
  0xff, 0xff, 0x00,
  0xff, 0xff, 0x00,
  0xff, 0xff, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 
};

static uint8_t tank2_right[] = {
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0xff, 0xff, 0x00,
  0xff, 0xff, 0x00,
  0xff, 0xff, 0x00,
  0x0c, 0x30, 0x00,
  0x0c, 0x30, 0x00,
  0x0c, 0x30, 0x00,
  0x0c, 0xf0, 0x0f,
  
  0x0c, 0xf0, 0x0f,
  0x0c, 0x30, 0x00,
  0x0c, 0x30, 0x00,
  0x0c, 0x30, 0x00,
  0xff, 0xff, 0x00,
  0xff, 0xff, 0x00,
  0xff, 0xff, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
};

static uint8_t tank1_up[] = {
  0x00, 0x06, 0x00,
  0x00, 0x06, 0x00,
  0x00, 0x06, 0x00,
  0x00, 0x06, 0x00,
  
  0x38, 0xc6, 0x01,
  0x38, 0xc6, 0x01,
  0xf8, 0xff, 0x01,
  0xf8, 0xff, 0x01,
  
  0xf8, 0xff, 0x01,
  0xf8, 0xff, 0x01,
  0xf8, 0xff, 0x01,
  0xf8, 0xff, 0x01,
  
  0xf8, 0xff, 0x01,
  0xf8, 0xff, 0x01,
  0xf8, 0xff, 0x01,
  0xf8, 0xff, 0x01,
  
  0xf8, 0xff, 0x01,
  0xf8, 0xff, 0x01,
  0x38, 0xc0, 0x01,
  0x38, 0xc0, 0x01,
};

static uint8_t tank2_up[] = {
  0x00, 0x06, 0x00,
  0x00, 0x06, 0x00,
  0x00, 0x06, 0x00,
  0x00, 0x06, 0x00,
  
  0x38, 0xc6, 0x01,
  0x38, 0xc6, 0x01,
  0xf8, 0xff, 0x01,
  0xf8, 0xff, 0x01,
  
  0x38, 0xc0, 0x01,
  0x38, 0xc0, 0x01,
  0x38, 0xc0, 0x01,
  0x38, 0xc0, 0x01,
  
  0x38, 0xc0, 0x01,
  0x38, 0xc0, 0x01,
  0x38, 0xc0, 0x01,
  0x38, 0xc0, 0x01,
  
  0xf8, 0xff, 0x01,
  0xf8, 0xff, 0x01,
  0x38, 0xc0, 0x01,
  0x38, 0xc0, 0x01,
};

static uint8_t tank1_down[] = {
  0x38, 0xc0, 0x01,
  0x38, 0xc0, 0x01,
  0xf8, 0xff, 0x01,
  0xf8, 0xff, 0x01,
  
  0xf8, 0xff, 0x01,
  0xf8, 0xff, 0x01,
  0xf8, 0xff, 0x01,
  0xf8, 0xff, 0x01,
  
  0xf8, 0xff, 0x01,
  0xf8, 0xff, 0x01,
  0xf8, 0xff, 0x01,
  0xf8, 0xff, 0x01,
  
  0xf8, 0xff, 0x01,
  0xf8, 0xff, 0x01,
  0x38, 0xc6, 0x01,
  0x38, 0xc6, 0x01,
  
  0x00, 0x06, 0x00,
  0x00, 0x06, 0x00,
  0x00, 0x06, 0x00,
  0x00, 0x06, 0x00,
};

static uint8_t tank2_down[] = {
  0x38, 0xc0, 0x01,
  0x38, 0xc0, 0x01,
  0xf8, 0xff, 0x01,
  0xf8, 0xff, 0x01,
  
  0x38, 0xc0, 0x01,
  0x38, 0xc0, 0x01,
  0x38, 0xc0, 0x01,
  0x38, 0xc0, 0x01,
  
  0x38, 0xc0, 0x01,
  0x38, 0xc0, 0x01,
  0x38, 0xc0, 0x01,
  0x38, 0xc0, 0x01,
  
  0xf8, 0xff, 0x01,
  0xf8, 0xff, 0x01,
  0x38, 0xc6, 0x01,
  0x38, 0xc6, 0x01,
  
  0x00, 0x06, 0x00,
  0x00, 0x06, 0x00,
  0x00, 0x06, 0x00,
  0x00, 0x06, 0x00,
};

static uint8_t block[] = {
  0xff, 0xff, 0x0f,
  0xff, 0xff, 0x0f,
  0xff, 0xff, 0x0f,
  0xff, 0xff, 0x0f,
  0xff, 0xff, 0x0f,
  0xff, 0xff, 0x0f,
  0xff, 0xff, 0x0f,
  0xff, 0xff, 0x0f,
  0xff, 0xff, 0x0f,
  0xff, 0xff, 0x0f,
  0xff, 0xff, 0x0f,
  0xff, 0xff, 0x0f,
  0xff, 0xff, 0x0f,
  0xff, 0xff, 0x0f,
  0xff, 0xff, 0x0f,
  0xff, 0xff, 0x0f,
  0xff, 0xff, 0x0f,
  0xff, 0xff, 0x0f,
  0xff, 0xff, 0x0f,
  0xff, 0xff, 0x0f,
};


static uint8_t ball[] = {
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x06, 0x00,
  0x00, 0x0f, 0x00,
  0x00, 0x0f, 0x00,
  0x00, 0x06, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
};

static uint8_t empty[] = {
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
};


static uint8_t test_map1[] = {
  0x33, 0x33, 0x33, 0x33,
  0x33, 0x33, 0x33, 0x33,
  0x30, 0x31, 0x32, 0x33,
  0x34, 0x35, 0x36, 0x37,
  0x30, 0x31, 0x32, 0x33,
  0x34, 0x35, 0x36, 0x37,
  0x30, 0x31, 0x32, 0x33,
  0x34, 0x35, 0x36, 0x37,
  0x30, 0x31, 0x32, 0x33,
  0x34, 0x35, 0x36, 0x37,
  0x30, 0x31, 0x32, 0x33,
  0x34, 0x35, 0x36, 0x37,
  0x30, 0x31, 0x32, 0x33,
  0x34, 0x35, 0x36, 0x37,
  0x30, 0x31, 0x32, 0x33,
  0x34, 0x35, 0x36, 0x37,
  0x30, 0x31, 0x32, 0x33,
  0x34, 0x35, 0x36, 0x37,
  0x30, 0x31, 0x32, 0x33,
  0x34, 0x35, 0x36, 0x37,
  0x30, 0x31, 0x32, 0x33,
};


static uint8_t test_map[84];


void myMapDisplay(const uint8_t *my_map) {
  int i = 0;
  //for (i = 0; i < 84; i++){
  for (i = 83; i > -1; i--){
    int x = 0;
    int y = 0;
    x = 20 * (i % 12);
    y = 20 * (i / 12);
    if (my_map[i] == 0x30){  /*u8g2.drawXBM( x, y, mapElement_h, mapElement_w, empty);*/ }
    else if (my_map[i] == 0x31){ u8g2.drawXBM( x, y, mapElement_h, mapElement_w, ball); }
    else if (my_map[i] == 0x32){ u8g2.drawXBM( x, y, mapElement_h, mapElement_w, block); }
    else if (my_map[i] == 0x33){ u8g2.drawXBM( x, y, mapElement_h, mapElement_w, tank1_up); }
    else if (my_map[i] == 0x34){ u8g2.drawXBM( x, y, mapElement_h, mapElement_w, tank1_down); }
    else if (my_map[i] == 0x35){ u8g2.drawXBM( x, y, mapElement_h, mapElement_w, tank1_left); }
    else if (my_map[i] == 0x36){ u8g2.drawXBM( x, y, mapElement_h, mapElement_w, tank1_right); }
    else if (my_map[i] == 0x37){ u8g2.drawXBM( x, y, mapElement_h, mapElement_w, empty); }
    }
}

void displayResult(int i)
{
  if (i == 0) { u8g2.drawStr(0,0, "DRAW!");}
  else if (i == 1){ u8g2.drawStr(0,0, "Player 1 WINS!"); }
  else if (i == 2){ u8g2.drawStr(0,0, "Player 2 WINS!"); }
}




void setup(void) {
  u8g2.begin();
  //Serial.begin(9600);
  Serial.begin(1000000);
  
  //Serial.begin(57600);
  Serial.begin(2000000);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Goodnight moon!");
  // set the data rate for the SoftwareSerial port
  //mySerial.begin(9600);
  Serial.begin(1000000);
  Wire.setClock(1600000L);
}

void loop(void) {
  //u8g2.setFontDirection(0);
  //u8g2.clearDisplay();
  
  //u8g2.drawStr(0,0,mySerial.read());


  while (mySerial.available())
  {
    char startStat = mySerial.read();
    Serial.write(startStat);
    if (startStat == 0x38)  // map in
    {
      u8g2.drawStr(0, 0, "1");
      int j = 0;
      for (int j = 0; j < 84; j++)
      {
        test_map[j] = mySerial.read();
      }

      
    }
    else if (startStat == 0x37)  // game state
    {
      if (mySerial.read() == 0x3A) { displayResult(1); }  // play1 wins
      else if (mySerial.read() == 0x3B) { displayResult(2); }  // play2 wins
      else if (mySerial.read() == 0x3C) { displayResult(0); }  // draw
    
    }
  }
  
   /*
  u8g2.firstPage();
  do {
    u8g2.setDrawColor(1);
    u8g2.setBitmapMode(0);
    u8g2.setFont(u8g2_font_ncenB14_tr);
    u8g2.setFontDirection(0);
    myMapDisplay(test_map1);
  } while ( u8g2.nextPage() );
*/
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB14_tr);
  //u8g2.drawStr(0,20,"Hello World!");
  myMapDisplay(test_map1);
  u8g2.sendBuffer();
  
}







