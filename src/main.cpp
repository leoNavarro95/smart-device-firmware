#include <Arduino.h>


#include <WiFi.h>
#include <ESPAsyncWebServer.h>
// #include <ArduinoJson.h>

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
  
  DB.begin();

  sdevice.set_mac("00:00:5e:00:53:af");
  sdevice.set_ap_ssid("mySSID");
  sdevice.set_ap_pass("1234");
  sdevice.set_connection_mode("STA");

  Gpio gpioArr[10];
  uint8_t i = 0;
  std::vector<Gpio> gpiosVector;

  for (Gpio gpio : gpioArr)
  {
    gpio.set_id(i++);
    gpio.set_pin_number(i);
    gpio.set_used(false);

    gpiosVector.push_back(gpio);
  }

  sdevice.set_gpios(gpiosVector);
      

  Serial.println("================");
  Serial.println(sdevice.get_mac().c_str());
  Serial.println(sdevice.get_ap_ssid().c_str());
  Serial.println(sdevice.get_ap_pass().c_str());
  Serial.println(sdevice.get_connection_mode().c_str());
  
  Serial.println("GPIOS: ");
  for (Gpio myGpio : sdevice.get_gpios())
  {
    Serial.println("ID: " + String(myGpio.get_id()));
    Serial.println("PIN: " + String(myGpio.get_pin_number()));
    Serial.println("USED: " + String(myGpio.get_used()));
    Serial.println("================");
  }
  


  Files.listDir(LittleFS, "/", (uint8_t) 0);


  ConnectWiFi_STA();

  InitServer();
  InitWebSockets();

  pinMode(IO0, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
}

uint8_t actState = 0;
uint8_t prevState = 0;


void loop(void)
{ 
  DB.doStuff();
  /*
  actState = digitalRead(IO0);

  if(prevState != actState){
  updateGPIO("D0", actState);
  prevState = actState;
  }

  vTaskDelay(100);
  */
}

