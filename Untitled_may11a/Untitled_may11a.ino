#include "arduino_secrets.h"
#include "thingProperties.h"

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#include <ArduinoSpotify.h>
#include <ArduinoJson.h>



char clientId[] = "97f19e65a98047f1b62bdf493b8cebf6"; // Your client ID of your spotify APP
char clientSecret[] = "aef1dd4f33c1411083e3375cde82a024"; // Your client Secret of your spotify APP (Do Not share this!)

// Country code, including this is advisable
#define SPOTIFY_MARKET "GR"

#define SPOTIFY_REFRESH_TOKEN "AQD-sOPKfjraCpxmkdLBqSaVWwPK9uxwRWjuHBiHkNAs2Kme6ILagRbFbLlUm1hqy8MuhsItnOffbl7KGX70VfAyhqp05JytRmCGypHtR7_oe8Yf_9xh3xrccDH4aJX6wVg"
#define SPOTIFY_FINGERPRINT "B9:79:6B:CE:FD:61:21:97:A7:02:90:EE:DA:CD:F0:A0:44:13:0E:EB"//"B9 79 6B CE FD 61 21 97 A7 02 90 EE DA CD F0 A0 44 13 0E EB"

//------- ---------------------- ------

WiFiClientSecure client;
ArduinoSpotify *spotify;

unsigned long delayBetweenRequests = 6000; // Time between requests (1 minute)
unsigned long requestDueTime;               //time when request due


void onSpotifyanzeigeChange() {
  // Do something
}


void setup() {

    Serial.begin(115200);
    
      delay(1000);

  initProperties();

  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

    
    // Set WiFi to station mode and disconnect from an AP if it was Previously
    // connected
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    // Attempt to connect to Wifi network:
    Serial.print("Connecting Wifi: ");
    Serial.println(SSID);
    WiFi.begin(SSID, PASS);
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    IPAddress ip = WiFi.localIP();
    Serial.println(ip);

    // Only avaible in ESP8266 V2.5 RC1 and above
    spotify = new ArduinoSpotify(client, clientId, clientSecret, SPOTIFY_REFRESH_TOKEN);
    client.setFingerprint(SPOTIFY_FINGERPRINT);

    // If you want to enable some extra debugging
    // uncomment the "#define SPOTIFY_DEBUG" in ArduinoSpotify.h

    Serial.println("Refreshing Access Tokens");
    if(!spotify->refreshAccessToken()){
        Serial.println("Failed to get access tokens");
    }
}

void printCurrentlyPlayingToSerial(CurrentlyPlaying currentlyPlaying)
{
    if (!currentlyPlaying.error)
    {
        Serial.println("--------- Currently Playing ---------");

    
        Serial.print("Is Playing: ");
        if (currentlyPlaying.isPlaying)
        {
            Serial.println("Yes");
        } else {
            Serial.println("No");
        }

        Serial.print("Track: ");
        Serial.println(currentlyPlaying.trackName);
        Serial.print("Track URI: ");
        Serial.println(currentlyPlaying.trackUri);
        Serial.println();

        Serial.print("Artist: ");
        Serial.println(currentlyPlaying.firstArtistName);
        Serial.print("Artist URI: ");
        Serial.println(currentlyPlaying.firstArtistUri);
        Serial.println();

        Serial.print("Album: ");
        Serial.println(currentlyPlaying.albumName);
        Serial.print("Album URI: ");
        Serial.println(currentlyPlaying.albumUri);
        Serial.println();

        long progress = currentlyPlaying.progressMs; // duration passed in the song
        long duration = currentlyPlaying.duraitonMs; // Length of Song
        Serial.print("Elapsed time of song (ms): ");
        Serial.print(progress);
        Serial.print(" of ");
        Serial.println(duration);
        Serial.println();

        float precentage = ((float) progress / (float) duration) * 100;
        int clampedPrecentage = (int)precentage;
        Serial.print("<");
        for (int j = 0; j < 50; j++){
        if(clampedPrecentage >= (j*2)){
            Serial.print("=");
        } else {
            Serial.print("-");
        }
        }
        Serial.println(">");
        Serial.println();

        // will be in order of widest to narrowest
        // currentlyPlaying.numImages is the number of images that
        // are stored 
        for (int i = 0; i < currentlyPlaying.numImages; i++) {
            Serial.println("------------------------");
            Serial.print("Album Image: ");
            Serial.println(currentlyPlaying.albumImages[i].url);
            Serial.print("Dimensions: ");
            Serial.print(currentlyPlaying.albumImages[i].width);
            Serial.print(" x ");
            Serial.print(currentlyPlaying.albumImages[i].height);
            Serial.println();
        }

        Serial.println("------------------------");
    }
}

void loop() {
  ArduinoCloud.update();
  if (millis() > requestDueTime)
    {
        Serial.print("Free Heap: ");
        Serial.println(ESP.getFreeHeap());

        Serial.println("getting currently playing song:");
        // Market can be excluded if you want e.g. spotify->getCurrentlyPlaying()
        CurrentlyPlaying currentlyPlaying = spotify->getCurrentlyPlaying(SPOTIFY_MARKET);

        printCurrentlyPlayingToSerial(currentlyPlaying);

        requestDueTime = millis() + delayBetweenRequests;
    }

}
