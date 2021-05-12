#include <PxMatrix.h>
#include "PxMatrixUi.h"

#include <Ticker.h>
Ticker display_ticker;


PxMATRIX display(64,32, 16, 2, 5, 4, 15, 12, 0);
void display_updater()
{
  display.display(); //uint16_t show_time
}
uint16_t myBlue = display.color565(0, 0, 255);
uint16_t myRed = display.color565(255, 0, 0);
uint16_t myGreen = display.color565(0, 255, 0);
uint16_t myWhite = display.color565(255, 255, 255);

uint16_t colors[36];// = uint16_t[32];
uint8_t num_colors = 36;

//PxMatrixUi ui(&display);
void drawRainbow(PxMATRIX *display, PxMatrixUiState *state, int16_t x, int16_t y){
  for(uint8_t i = 0; i < 32; ++i){
    display->drawLine(x, y+i, x+64, y+i, colors[i]);
  }
}

FrameCallback frames[] = {drawRainbow, drawRainbow};
int numberOfFrames = 2;

OverlayCallback overlays[] = {};
int numberOfOverlays = 0;

struct IndicatorSymbols dIS_1 = {
    {0x80},
    {0x80},
    1,
    1,
    PxMatrixUi::color565(75, 0, 130),
    PxMatrixUi::color565(255, 195, 203)
};
uint8_t x, y;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  display.begin(16);
  display.setTextColor(myBlue);
  display.print("Hello Wrld"); 
  
  colors[0] = display.color565(255, 0, 0);
  colors[1] = display.color565(255, 42, 0);
  colors[2] = display.color565(255, 85, 0);
  colors[3] = display.color565(255, 127, 0);
  colors[4] = display.color565(255, 170, 0);
  colors[5] = display.color565(255, 212, 0);
  colors[6] = display.color565(255, 255, 0);
  colors[7] = display.color565(212, 255, 0);
  colors[8] = display.color565(170, 255, 0);
  colors[9] = display.color565(127, 255, 0);
  colors[10] = display.color565(85, 255, 0);
  colors[11] = display.color565(42, 255, 0);
  colors[12] = display.color565(0, 255, 0);
  colors[13] = display.color565(0, 255, 42);
  colors[14] = display.color565(0, 255, 85);
  colors[15] = display.color565(0, 255, 127);
  colors[16] = display.color565(0, 255, 170);
  colors[17] = display.color565(0, 255, 212);
  colors[18] = display.color565(0, 255, 255);
  colors[19] = display.color565(0, 212, 255);
  colors[20] = display.color565(0, 170, 255);
  colors[21] = display.color565(0, 127, 255);
  colors[22] = display.color565(0, 85, 255);
  colors[23] = display.color565(0, 42, 255);
  colors[24] = display.color565(0, 0, 255);
  colors[25] = display.color565(42, 0, 255);
  colors[26] = display.color565(85, 0, 255);
  colors[27] = display.color565(127, 0, 255);
  colors[28] = display.color565(170, 0, 255);
  colors[29] = display.color565(212, 0, 255);
  colors[30] = display.color565(255, 0, 255);
  colors[31] = display.color565(255, 0, 212);
  colors[32] = display.color565(255, 0, 170);
  colors[33] = display.color565(255, 0, 127);
  colors[34] = display.color565(255, 0, 85);
  colors[35] = display.color565(255, 0, 45);

  x = 0;
  y = 0;
  display_ticker.attach(0.004, display_updater);
  
  //ui.setTargetFPS(30); //250 equals displayticker.attack(0.004, display_updater);
  //ui.setIndicatorPosition(LEFT);
  //ui.setIndicatorDirection(LEFT_RIGHT);
  //ui.setFrameAnimation(SLIDE_UP);
  //ui.setFrames(frames, numberOfFrames);
  //ui.setOverlays(overlays, numberOfOverlays);
  //ui.setIndicatorSymbols(&dIS_1);
  //ui.loadDefaultOff();
  //ui.yOffIndicator--;
  //ui.begin(16);

  //ui.setTimePerFrame(1000);
  //ui.setTimePerTransition(0);
  delay(1000);
  display.clearDisplay();
}

void loop() {
   //int remainingTimeBudget = ui.update();

  for(uint8_t i = 0; i < num_colors; ++i){
    display.drawLine(x, i, x+64, i, colors[(y+i)%num_colors]);
  }
  ++y;
  if(y >= num_colors)
    y = 0;
  delay(30);
  //if (remainingTimeBudget > 0) {
    // You can do some work here
    // Don't do stuff if you are below your
    // time budget.
    //delay(remainingTimeBudget);
  //}
}
