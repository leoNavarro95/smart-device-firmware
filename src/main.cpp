

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
  
  DB.printGpioArr(sdevice.get_gpios_status());
  DB.printGpioArr(sdevice.get_used_gpios());

  UsedGpio newUG1, newUG2;
  newUG1.set_label("un led ahi");
  newUG1.set_pin_number(10);
  newUG1.set_mode("OUTPUT");
  newUG1.set_value("LOW");

  DB.setUsedGpio(sdevice, newUG1);

  newUG2.set_label("Motor PWM");
  newUG2.set_pin_number(5);
  newUG2.set_mode("PWM");
  newUG2.set_value("0");
  DB.setUsedGpio(sdevice, newUG2);

  DB.printGpioArr(sdevice.get_gpios_status());
  DB.printGpioArr(sdevice.get_used_gpios());

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

