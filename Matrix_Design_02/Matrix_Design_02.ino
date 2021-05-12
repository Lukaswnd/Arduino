#include <PxMatrix.h>


#include <Ticker.h>
Ticker display_ticker;
#define P_LAT 16
#define P_A 5
#define P_B 4
#define P_C 15
#define P_D 12
#define P_E 0
#define P_OE 2

PxMATRIX display(64,32,P_LAT, P_OE,P_A,P_B,P_C,P_D,P_E);

void display_updater()
{
  display.display(); //uint16_t show_time
}

uint16_t myBlue = display.color565(0, 0, 255);
uint16_t myRed = display.color565(255, 0, 0);
uint16_t myGreen = display.color565(0, 255, 0);
uint16_t myWhite = display.color565(255, 255, 255);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  display.begin(16);
  display.flushDisplay();
  display.setTextColor(myBlue);
  display.setCursor(2,0);
  display.print("Hello World");
  display_ticker.attach(0.004, display_updater); //
  delay(1000);
  display.clearDisplay();
}

int8_t x = 0;
int8_t y = 0;
uint8_t r = 0;
uint8_t g = 0;
uint8_t b = 255;

uint8_t step_num = 0;

void loop() {
  if(x == 64){
    x = 0;
    y++;
  }
  if(y == 32)
    y = 0;
  switch(step_num){
    case 0:
      if(g == 255)
        step_num++;
      else
        g++;
      break;
    case 1:
      if(b == 0)
        step_num++;
      else
        b--;
      break;
    case 2:
      if(r == 255)
        step_num++;
      else
        r++;
      break;
    case 3:
      if(g == 0)
        step_num++;
      else
        g--;
      break;
    case 4:
      if(b == 255)
        step_num++;
      else
        b++;
      break;
    case 5:
      if(g == 255)
        step_num++;
      else
        g++;
      break;
    case 6:
      if(g == 128){
        g = 0;
        step_num++;
      }else
        g--;
      break;
    case 7:
      if(r == 0)
        step_num = 0;
      else
        r--;
      break;
  }
  display.drawPixelRGB888(x, y, r, g, b);
  delay(5);
  ++x;
}
