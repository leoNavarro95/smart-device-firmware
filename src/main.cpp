

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
    DB.initDeviceFromDB(&sdevice);

  Serial.printf("ap pass: %s\n", sdevice.get_ap_pass());
  Serial.printf("ap ssid: %s\n", sdevice.get_ap_ssid());
  Serial.printf("conncetion mode: %s\n", sdevice.get_connection_mode());
  Serial.printf("mac: %s\n", sdevice.get_mac());
  Serial.printf("sta pass: %s\n", sdevice.get_sta_pass());
  Serial.printf("sta ssid: %s\n", sdevice.get_sta_ssid());

  // UsedGpio *usedGpios = sdevice.get_used_gpios();
  // uint8_t size_used_gpios = DB.get_size_used_gpios();

  // Serial.printf("\nSize used gpios: %d\n", size_used_gpios);

  UsedGpio *used_gpios = sdevice.get_used_gpios();
  uint8_t size_u_gpios = DB.get_size_used_gpios();

  for(int i = 0; i < size_u_gpios; i++){
    Serial.println("++++++++++++++++++++++++++++++++++");
    Serial.printf("id: %d\n", used_gpios[i].get_id());
    Serial.printf("pin: %d\n", used_gpios[i].get_pin_number());
    Serial.printf("mode: %s\n", used_gpios[i].get_mode());
    Serial.printf("label: %s\n", used_gpios[i].get_label());
    Serial.printf("value: %s\n", used_gpios[i].get_value());
    Serial.println("++++++++++++++++++++++++++++++++++");
    Serial.println();
  }


  
/*
  for(int i = 0; i < size_used_gpios; i++){
    Serial.printf("id: %d\n", usedGpios[i].get_id());
    Serial.printf("pin: %d\n", usedGpios[i].get_pin_number());
    Serial.printf("mode: %s\n", usedGpios[i].get_mode());
    Serial.printf("label: %s\n", usedGpios[i].get_label());
    Serial.printf("value: %s\n", usedGpios[i].get_value());
    Serial.println();
  }

  Gpio *gpios = sdevice.get_gpios();
  uint8_t size_gpios = DB.get_size_gpios();

  Serial.printf("size gpios: %d\n", size_gpios);
  
  for(int i = 0; i < size_gpios; i++){
    Serial.printf("id: %d\n", gpios[i].get_id());
    Serial.printf("mode: %d\n", gpios[i].get_pin_number());
    Serial.printf("label: %d\n", gpios[i].get_used());
  }

*/

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

