#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <DateTime.h>


//#define double_buffer
#include "PxMatrix.h"
#include <PxMatrix_UiDisplay.h>
#include "PxMatrixUi.h"
#include <Ticker.h>

//Matrix
//* 
Ticker display_ticker;
PxMatrix_UiDisplay my_Display{ 64,32, 16, 2, 5, 4, 15, 12, 0 };
PxMATRIX* display = &my_Display;

void display_updater() {
    my_Display.MatrixDisplay();
}
/**/
//PxMATRIX* display = new PxMATRIX{64, 32, 16, 2, 5, 4, 15, 12, 0};

const uint16_t myBlue = display->color565(0, 0, 255);
const uint16_t myRed = display->color565(255, 0, 0);
const uint16_t myGreen = display->color565(0, 255, 0);
const uint16_t myWhite = display->color565(255, 255, 255);
const uint16_t myBlack = display->color565(0, 0, 0);
uint8_t brightness = 31;//31

//NetzWerk
const char* WIFI_SSID = "FRITZ!Box Fon WLAN 7360";
const char* WIFI_PWD = "80573167039145173181";

//Variablen
uint16_t counter = 0;

const uint8_t num_0[5] = { 0xe0, 0xa0, 0xa0, 0xa0, 0xe0 };
const uint8_t num_1[5] = { 0x20, 0x20, 0x20, 0x20, 0x20 };
const uint8_t num_2[5] = { 0xe0, 0x20, 0xe0, 0x80, 0xe0 };
const uint8_t num_3[5] = { 0xe0, 0x20, 0xe0, 0x20, 0xe0 };
const uint8_t num_4[5] = { 0xa0, 0xa0, 0xe0, 0x20, 0x20 };
const uint8_t num_5[5] = { 0xe0, 0x80, 0xe0, 0x20, 0xe0 };
const uint8_t num_6[5] = { 0xe0, 0x80, 0xe0, 0xa0, 0xe0 };
const uint8_t num_7[5] = { 0xe0, 0x20, 0x20, 0x20, 0x20 };
const uint8_t num_8[5] = { 0xe0, 0xa0, 0xe0, 0xa0, 0xe0 };
const uint8_t num_9[5] = { 0xe0, 0xa0, 0xe0, 0x20, 0xe0 };
const int16_t num_width = 3;
const int16_t num_height = 5;
const uint8_t punkt[5] = { 0x00, 0x00, 0x00, 0x00, 0x80 };
const uint8_t doppel_punkt[5] = { 0x00, 0x80, 0x00, 0x80, 0x00 };
const uint8_t* num_n[10] = { num_0, num_1, num_2, num_3, num_4, num_5, num_6, num_7, num_8, num_9 };
//time
unsigned long prev_time; //seconds since 1.1.1970 00:00:00
const unsigned long utcOffSec = 2 * 60 * 60;
uint8_t minutes = 0, hours = 0, day = 0, month = 0;

void syncTime() {
    minutes = DateTime.getParts().getMinutes();
    hours = DateTime.getParts().getHours();
    day = DateTime.getParts().getMonthDay();
    month = DateTime.getParts().getMonth() + 1;
}

//UI
PxMatrixUi ui(display);
#define rect_height 27
uint16_t farbBlock[48] = { 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,
                            0xFFE0, 0xFFE0, 0xFFE0, 0xFFE0, 0xFFE0, 0xFFE0, 0xFFE0, 0xFFE0,
                            0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0, 0x07E0,
                            0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF,
                            0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F,
                            0xF81F, 0xF81F, 0xF81F, 0xF81F, 0xF81F, 0xF81F, 0xF81F, 0xF81F };

uint8_t farbEcke[75] = { 255, 255, 0, 191, 255, 0, 127, 255, 0, 63, 255, 0, 0, 255, 0,
                          255, 191, 0, 191, 191, 0, 127, 191, 0, 63, 191, 0, 0, 191, 0,
                          255, 127, 0, 191, 127, 0, 127, 127, 0, 63, 127, 0, 0, 127, 0,
                          255, 63, 0, 191, 63, 0, 127, 63, 0, 63, 63, 0, 0, 63, 0,
                          255, 0, 0, 191, 0, 0, 127, 0, 0, 63, 0, 0, 0, 0, 16 }; //15 //16


uint16_t liste16[1728];
uint8_t liste8[5184];

void fillListe16() {
    uint8_t step_t = 33;
    uint16_t color = 0;
    for (int i = 0; i < 1728; ++i) {
        liste16[i] = color;
        color += step_t;
    }
}
void fillListe8() {
    float step_t = 9709;
    long color = 0;
    for (int i = 0; i < 5184; i += 3) {
        liste8[i] = (color >> 16) & 0xFF;
        liste8[i + 1] = (color >> 8) & 0xFF;
        liste8[i + 2] = color & 0xFF;
        color += step_t;
    }
}

void drawList8(PxMatrixUi* ui, int16_t x, int16_t y) {
    ui->drawColoredMatrix888(liste8, x, y, 64, 27);
}

void drawListe16(PxMatrixUi* ui, int16_t x, int16_t y) {
    ui->drawColoredMatrix565(liste16, x, y, 64, 27);
}

void drawEmpty(PxMatrixUi* ui, int16_t x, int16_t y) {
    Serial.printf("AAA x: %d, y: %d\n", x, y);
    ui->display->drawRect(x, y, 64, 27, myRed);
    Serial.println("BBB");
}

bool draw_time_dot = false;
void TimeOverlay(PxMatrixUi* ui) {
    ui->display->drawBitmap(0, 0, num_n[hours / 10], num_width, num_height, myWhite);
    ui->display->drawBitmap(4, 0, num_n[hours % 10], num_width, num_height, myWhite);
    if (draw_time_dot)
        ui->display->drawBitmap(8, 0, doppel_punkt, 1, num_height, myWhite);
    ui->display->drawBitmap(10, 0, num_n[minutes / 10], num_width, num_height, myWhite);
    ui->display->drawBitmap(14, 0, num_n[minutes % 10], num_width, num_height, myWhite);
}
void DateOverlay(PxMatrixUi* ui) {
    uint8_t add = 0;
    if (month > 9)
        add = 2;
    ui->display->drawBitmap(47 + add, 0, num_n[day / 10], num_width, num_height, myWhite);
    ui->display->drawBitmap(51 + add, 0, num_n[day % 10], num_width, num_height, myWhite);
    ui->display->drawBitmap(55 + add, 0, punkt, 1, num_height, myWhite);
    ui->display->drawBitmap(57, 0, num_n[month / 10], num_width, num_height, myWhite);
    ui->display->drawBitmap(61, 0, num_n[month % 10], num_width, num_height, myWhite);
}
void BlackOverlay(PxMatrixUi* ui) {
    ui->display->fillRect(0, 0, 64, 5, myBlack);
}

FrameCallback frames[] = { drawListe16, drawList8, drawEmpty};
uint8_t numberOfFrames = 3;
OverlayCallback overlays[] = { PxMatrixUi::drawIndicatorO, TimeOverlay, DateOverlay };
uint8_t numberOfOverlays = 3;

void startMsg(const char* s) {
    display->clearDisplay();
    display->setCursor(0, 0);
    display->println(s);
    delay(1000);
}

int8_t setupMatrix() {
    Serial.begin(115200);
    //Matrix
    display_ticker.attach(0.004, display_updater);//004
    display->begin();
    display->flush();
    display->setTextSize(1);
    display->setTextColor(myBlue);
    return 0;
}
int8_t setupUI() {
    //UI
    ui.setTargetFPS(30); //250 equals displayticker.attack(0.004, display_updater);
    ui.setIndicatorPosition(TOP);
    ui.setIndicatorDirection(LEFT_RIGHT);
    ui.setFrameAnimation(SLIDE_LEFT);
    ui.setFrames(frames, numberOfFrames);
    ui.setOverlays(overlays, numberOfOverlays);
    ui.disableAllIndicators();
    //ui.set_show_time(1);
    ui.setTimePerFrame(3000);
    ui.setTimePerTransition(1000);
    ui.loadDefaultOff();
    ui.begin(16);
    return 0;
}

int8_t setupWIFI() {
    display->print("Connecting");
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PWD);
    Serial.println();
    Serial.print("Connecting Wifi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        display->print(".");
    }
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("Wifi Connected");
        display->println("connected");
        return 1;
    }
    return -1;
}

int8_t setupVars() {
    fillListe16();
    fillListe8();
    return 0;
}

int8_t setupTime() {
    uint8_t i = 0;
    do {
        if (i > 4)
            return -1;
        //Time
        WiFiUDP ntpUDP;
        //europe.pool.ntp.org //europe
        //pool.ntp.org        //world wide
        //60000 update intervall in ms nichts für nie
        NTPClient timeClient(ntpUDP, "de.pool.ntp.org", utcOffSec);
        timeClient.begin();
        timeClient.forceUpdate();
        DateTime.setTime(timeClient.getEpochTime(), true);
        timeClient.end();
        display->print(".");
        Serial.println(DateTime.toString());
        ++i;
    } while (!DateTime.isTimeValid());

    //Doesn´t work on esp8266
    DateTime.setTimeZone(2);
    syncTime();
    return 0;
}

void setup() {
    uint8_t time_retry = 0;
    for (uint8_t j = 0; j < 6; ++j) {
        switch (j) {
        case 0:
            uint8_t i;
            uint8_t result;
            for (i = 0; i < 10; ++i) {
                if (result = setupMatrix() >= 0) {
                    break;
                }
            }
            if (result < 0) {
                Serial.println("Unable to setup Matrix");
                Serial.println("Check Software");
            }
            break;
        case 1:
            startMsg("UI:");
            result = 0;
            for (i = 0; i < 10; ++i) {
                if (result = setupUI() >= 0) {
                    break;
                }
            }
            if (result < 0) {
                Serial.println("Unable to setup UI");
                Serial.println("Check Software");
            }
            break;
        case 2:
            startMsg("WIFI:");
            result = setupWIFI();
            if (result < 0) {
                Serial.println("Unable to Connect WIFI");
                Serial.println("Check Connection settings and WLAN");
            }
            break;
        case 3:
            startMsg("Time:");
            result = setupTime();
            if (result < 0 && time_retry < 10) {
                j -= 2;
                Serial.println("Failed Time: " + String{ time_retry });
                startMsg("Failed Time");
                ++time_retry;
            }
            else if (result < 0) {
                Serial.println("Unable to Find Time");
                Serial.println("Check WIFI and retry");
            }
            else {
                Serial.println("Time: " + DateTime.toString());
            }
            break;
        case 4:
            startMsg("Vars");
            result = setupVars();
            if (result < 0) {
                Serial.println("Unable to setup Vars");
                Serial.println("Check Code");
            }
            break;
        case 5:
            startMsg("ready");
            my_Display.wait_time = 10;
            display->clearDisplay();
            display->flush();
            display->setBrightness(brightness);
            display->setFastUpdate(true);
            break;
        }
    }
}

void loop() {
    // put your main code here, to run repeatedly
    int16_t rTB = ui.update();
    switch (rTB) {
    case 25 ... 34:

    case 15 ... 24:
        syncTime();
    case 5 ... 14:

    case 1 ... 4:
        delay(rTB);
        break;
    default:
        Serial.println("Ran out of Time" + String(rTB));
        break;
    }
    if (counter % 30 == 0) {
        draw_time_dot = !draw_time_dot;
        Serial.println("Remaining Time: " + String(rTB));
    }
    ++counter;
}
