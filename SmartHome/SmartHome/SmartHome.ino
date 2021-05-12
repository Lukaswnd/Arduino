#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif

#include "MY_WIFI.h"

#define ESPALEXA_DEBUG 1
#include "Espalexa.h"

Espalexa espalexa;

void Lamp1callback(uint8_t b) {
	Serial.printf("Callback 1 b: %d\n", b);
}
void Lamp2callback(uint8_t b, uint32_t c) {
	Serial.printf("Callback 2 b: %d, c: %d\n", b, c);
}
void Lamp3callback(EspalexaDevice* d) {
	Serial.printf("Callback 3 name: %s, val: %d, perc: %d, rgb: %d\n", d->getName().c_str(), d->getValue(), d->getPercent(), d->getRGB());
}

void setup() {
	Serial.begin(115200);

	connect_WIFI();

	espalexa.addDevice("Lampe 1", Lamp1callback, 255);
	espalexa.addDevice("Lampe 2", Lamp2callback, 255);
	espalexa.addDevice("Lampe 3", Lamp3callback, EspalexaDeviceType::color, 255);

	espalexa.begin();



}


void loop() {

	espalexa.loop();
	delay(1);
}
