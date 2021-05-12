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
  display.setTextColor(myBlue);
  display.print("Hello World");
  display_ticker.attach(0.004, display_updater); //
  delay(1000);
  display.clearDisplay();
}
int8_t step_size = 16;

int8_t x = 0;
uint8_t r = 0;
uint8_t g = 0;
uint8_t b = 255;

uint8_t step_num = 0;

void loop() {
  if(x == 64)
    x = 0;
  switch(step_num){
    case 0:
      if(g > 255-step_size){
        step_num++;
        g = 255;
      }else
        g+=step_size;
      break;
    case 1:
      if(b < step_size){
        step_num++;
        b = 0;
      }else
        b-=step_size;
      break;
    case 2:
      if(r > 255-step_size){
        step_num++;
        r = 255;
      }else
        r+=step_size;
      break;
    case 3:
      if(g < step_size){
        step_num++;
        g = 0;
      }else
        g-=step_size;
      break;
    case 4:
      if(b > 255-step_size){
        step_num++;
        b = 255;
      }else
        b+=step_size;
      break;
    case 5:
      if(r < step_size){
        step_num = 0;
        r = 0;
      }else
        r-=step_size;
      break;
  }
  display.drawLine(x, 0, x, 64, display.color565(r, g, b));
  delay(25);
  ++x;
}
