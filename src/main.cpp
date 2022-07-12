

#include <Arduino.h>

#include <WiFi.h>
#include <ESPAsyncWebServer.h>

#include "FileSystem.h"
#include "DB_Manager.h"
#include"SmartDevice_Model.hpp"

#include "config.h"  // Sustituir con datos de la red 
#include "API.hpp"
#include "WebSockets.hpp"
#include "Server.hpp"
#include "ESP32_Utils.hpp"
#include "ESP32_Utils_AWS.hpp"


#define IO0 0

SmartDevice sdevice;


void setup(void)
{
  Serial.begin(115200);
  
  Files.begin();
  Files.listDir(LittleFS, "/", (uint8_t) 0);

  if(DB.begin("/database/esp_soc.json"))
    DB.initDeviceFromDB(sdevice);




/*
  ConnectWiFi_STA();

  InitServer();
  InitWebSockets();
*/
  pinMode(IO0, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
}

uint8_t actState = 0;
uint8_t prevState = 0;


void loop(void)
{ 
  /*
  actState = digitalRead(IO0);

  if(prevState != actState){
  updateGPIO("D0", actState);
  prevState = actState;
  }

  vTaskDelay(100);
  */
}

