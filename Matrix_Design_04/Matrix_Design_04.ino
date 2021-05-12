#include <PxMatrix.h>
#include "PxMatrixUi.h"


PxMATRIX display(64,32, 16, 2, 5, 4, 15, 12, 0);
uint16_t myBlue = display.color565(0, 0, 255);
uint16_t myRed = display.color565(255, 0, 0);
uint16_t myGreen = display.color565(0, 255, 0);
uint16_t myWhite = display.color565(255, 255, 255);

PxMatrixUi ui(&display);
void drawBlue(PxMATRIX *display, PxMatrixUiState *state, int16_t x, int16_t y){
  display->drawRect(x, y, 63, 32, myBlue);
}
void drawBlue1(PxMATRIX *display, PxMatrixUiState *state, int16_t x, int16_t y){
  display->drawRect(x+1, y+1, 61, 30, display->color565(0, 127, 255));
}
void drawBlue2(PxMATRIX *display, PxMatrixUiState *state, int16_t x, int16_t y){
  display->drawRect(x+2, y+2, 59, 28, display->color565(0, 255, 255));
}
void drawBlue3(PxMATRIX *display, PxMatrixUiState *state, int16_t x, int16_t y){
  display->drawRect(x+3, y+3, 57, 26, display->color565(0, 255, 127));
}
void drawGreen(PxMATRIX *display, PxMatrixUiState *state, int16_t x, int16_t y){
  display->drawRect(x+4, y+4, 55, 24, myGreen);
}
void drawGreen1(PxMATRIX *display, PxMatrixUiState *state, int16_t x, int16_t y){
  display->drawRect(x+5, y+5, 53, 22, display->color565(127, 255, 0));
}
void drawGreen2(PxMATRIX *display, PxMatrixUiState *state, int16_t x, int16_t y){
  display->drawRect(x+6, y+6, 51, 20, display->color565(255, 255, 0));
}
void drawGreen3(PxMATRIX *display, PxMatrixUiState *state, int16_t x, int16_t y){
  display->drawRect(x+7, y+7, 49, 18, display->color565(255, 127, 0));
}
void drawRed(PxMATRIX *display, PxMatrixUiState *state, int16_t x, int16_t y){
  display->drawRect(x+8, y+8, 47, 16, myRed);
}
void drawRed1(PxMATRIX *display, PxMatrixUiState *state, int16_t x, int16_t y){
  display->drawRect(x+9, y+9, 45, 14, display->color565(255, 0, 127));
}
void drawRed2(PxMATRIX *display, PxMatrixUiState *state, int16_t x, int16_t y){
  display->drawRect(x+10, y+10, 43, 12, display->color565(255, 0, 255));
}
void drawRed3(PxMATRIX *display, PxMatrixUiState *state, int16_t x, int16_t y){
  display->drawRect(x+11, y+11, 41, 10, display->color565(127, 0, 255));
}
void drawBlue4(PxMATRIX *display, PxMatrixUiState *state, int16_t x, int16_t y){
  display->drawRect(x+12, y+12, 39, 8, myBlue);
}
void drawBlue5(PxMATRIX *display, PxMatrixUiState *state, int16_t x, int16_t y){
  display->drawRect(x+13, y+13, 37, 6, display->color565(0, 127, 255));
}
void drawBlue6(PxMATRIX *display, PxMatrixUiState *state, int16_t x, int16_t y){
  display->drawRect(x+14, y+14, 35, 4, display->color565(0, 255, 255));
}
void drawBlue7(PxMATRIX *display, PxMatrixUiState *state, int16_t x, int16_t y){
  display->drawRect(x+15, y+15, 33, 2, display->color565(0, 255, 127));
}
void drawOverlay(PxMATRIX *display, PxMatrixUiState *state){
  //display->drawRect(0, 0, 5, 32, myWhite);
}


FrameCallback frames[] = {drawBlue, drawBlue1, drawBlue2, drawBlue3, drawGreen, drawGreen1,
      drawGreen2, drawGreen3, drawRed, drawRed1, drawRed2, drawRed3, drawBlue4, drawBlue5, drawBlue6, drawBlue7};
int numberOfFrames = 16;

OverlayCallback overlays[] = {drawOverlay};
int numberOfOverlays = 1;

struct IndicatorSymbols dIS_1 = {
    {0x80},
    {0x80},
    1,
    1,
    PxMatrixUi::color565(75, 0, 130),
    PxMatrixUi::color565(255, 195, 203)
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  display.begin(16);
  display.setTextColor(myBlue);
  display.print("Hello Wrld"); 

  ui.setTargetFPS(200); //250 equals displayticker.attack(0.004, display_updater);
  ui.setIndicatorPosition(LEFT);
  ui.setIndicatorDirection(LEFT_RIGHT);
  ui.setFrameAnimation(SLIDE_UP);
  ui.setFrames(frames, numberOfFrames);
  ui.setOverlays(overlays, numberOfOverlays);
  ui.setIndicatorSymbols(&dIS_1);
  ui.loadDefaultOff();
  //ui.yOffIndicator--;
  ui.begin(16);

  ui.setTimePerFrame(500);
  ui.setTimePerTransition(0);
  delay(1000);
  display.clearDisplay();
}

void loop() {
   int remainingTimeBudget = ui.update();

  if (remainingTimeBudget > 0) {
    // You can do some work here
    // Don't do stuff if you are below your
    // time budget.
    delay(remainingTimeBudget);
  }
}
