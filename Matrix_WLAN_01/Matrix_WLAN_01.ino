#include <PxMatrix.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Ticker.h>

Ticker display_ticker;

PxMATRIX display(64, 32, 16, 2, 5, 4, 15, 12, 0);
//Matrix
uint16_t myBlue = display.color565(0, 0, 255);
uint16_t myRed = display.color565(255, 0, 0);
uint16_t myGreen = display.color565(0, 255, 0);
uint16_t myWhite = display.color565(255, 255, 255);
uint8_t myR = 0;
uint8_t myG = 0;
uint8_t myB = 0;
void setTextColor(){
  display.setTextColor(display.color565(myR, myG, myB));
}
void display_updater()
{
  display.display(); //uint16_t show_time //standart 30[µs]
}


//WebServer
const char* WIFI_SSID = "FRITZ!Box Fon WLAN 7360";
const char* WIFI_PWD = "80573167039145173181";
IPAddress ip(192,168,1,157); //Feste IP des neuen Servers, frei wählbar //54 demnächst
IPAddress gateway(192,168,1,5); //Gatway (IP Router eintragen)
IPAddress subnet(255,255,255,0); //Subnet Maske eintragen
ESP8266WebServer server(80);

void handleRoot(){
  server.send(200, "text/plain", "Hello World!\n");
  Serial.println("HandleRoot");
}
void handleHelp(){
  printUrlArg();
  server.send(200, "text/plain", "Hello I will Help!\n");
  Serial.println("HandleHelp");
}
void printUrlArg() {
 //Alle Parameter seriell ausgeben
 String message="";
 for (uint8_t i=0; i<server.args(); i++){
 message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
 }
 server.send(200, "text/plain", message);
 Serial.println(message);
}
void handleText(){
  display.setCursor(0,0);
  display.clearDisplay();
 for (uint8_t i=0; i<server.args(); i++){
  if(server.argName(i) == "r"){
    int red = atoi(server.arg(i).c_str());
    if(red >= 0 && red <= 255){
      myR = red;
      setTextColor();
    }
  }else if(server.argName(i) == "g"){
    int green = atoi(server.arg(i).c_str());
    if(green >= 0 && green <= 255){
      myG = green;
      setTextColor();
    }
  }else if(server.argName(i) == "b"){
    int blue = atoi(server.arg(i).c_str());
    if(blue >= 0 && blue <= 255){
      myB = blue;
      setTextColor();
    }
  }else{
    display.println(server.argName(i));
    server.send(200, "text/plain", server.argName(i));
    Serial.println(server.argName(i));
  }
 }
}



void setup() {
  Serial.begin(115200);
  //Matrix
  display.begin(16);
  display.flushDisplay();
  display.clearDisplay();
  display_ticker.attach(0.004, display_updater); 
  myB = 255;
  setTextColor();

  //WebServer
  Serial.println(WiFi.macAddress()); //50:02:91:D6:11:57
  WiFi.begin(WIFI_SSID, WIFI_PWD);
  WiFi.config(ip, gateway, subnet);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());
  //WiFi.config(IPAddress(WiFi.localIP()), gateway, subnet);
  server.on("/", handleRoot);
  server.on("/help/", handleHelp);
  server.on("/text/", handleText);
  server.begin();
  
}

void loop() {
  // put your main code here, to run repeatedly:
server.handleClient();
 
 delay(500);
}
