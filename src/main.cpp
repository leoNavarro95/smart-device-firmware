#include <Arduino.h>

#include "FS.h"
#include <LittleFS.h>

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

/* You only need to format LittleFS the first time you run a
   test or else use the LittleFS plugin to create a partition
   https://github.com/lorol/arduino-esp32littlefs-plugin */
#define FORMAT_LITTLEFS_IF_FAILED false
#include "FileSystem.hpp"

// TODO: Encontrar forma que no sea harcodeando los password e ssid
#include "config.h"  // Sustituir con datos de la red 
#include "API.hpp"
#include "WebSockets.hpp"
#include "Server.hpp"
#include "ESP32_Utils.hpp"
#include "ESP32_Utils_AWS.hpp"


#define IO0 0

void setup(void)
{
  Serial.begin(115200);
  if(!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED)){
        Serial.println("LittleFS Mount Failed");
        return;
    }

  listDir(LittleFS, "/", 0);

  ConnectWiFi_STA();

  InitServer();
  InitWebSockets();

  pinMode(IO0, INPUT_PULLUP);
}

uint8_t actState = 0;
uint8_t prevState = 0;


void loop(void)
{ 
  actState = digitalRead(IO0);

  if(prevState != actState){
  updateGPIO("D0", actState);
  prevState = actState;
  }

  vTaskDelay(100);
}

