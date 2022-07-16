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

  if(DB.begin("/database/test.json")){
    DB.initDeviceFromDB(sdevice);
  } 
  else{
    DB.createDefault(sdevice);
    log_w("Creating default database file");
    DB.initDeviceFromDB(sdevice);
  }

  UsedGpio newUG1, newUG2;
  newUG1.set_label("Otra cosa rara");
  newUG1.set_pin_number(10);
  newUG1.set_mode("OUTPUT");
  newUG1.set_value("LOW");

  DB.setUsedGpio(sdevice, newUG1);

  newUG2.set_label("LED dimmer");
  newUG2.set_pin_number(8);
  newUG2.set_mode("PWM");
  newUG2.set_value("255");
  DB.setUsedGpio(sdevice, newUG2);

  // DB.printGpioArr(sdevice.get_gpios_status());
  // DB.printGpioArr(sdevice.get_used_gpios());

  ConnectWiFi_STA();

  InitServer();
  InitWebSockets();

  pinMode(IO0, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
}


void loop(void)
{ 

}

