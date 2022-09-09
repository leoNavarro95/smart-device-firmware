#include <Arduino.h>

#include "DB_Manager.h"
#include "SmartDevice_Model.hpp"
#include "Wifi_Manager.hpp"

SmartDevice sdevice;
WifiManager myWifi;

void setup(void)
{
  Serial.begin(115200);

  DB.begin("/database/esp_soc.json", sdevice);
/*
  UsedGpio newUG1, newUG2;
  newUG1.set_label("RELE");
  newUG1.set_pin_number(10);
  newUG1.set_mode("OUTPUT");
  newUG1.set_value("LOW");
  DB.setUsedGpio(sdevice, newUG1);

  newUG2.set_label("LED dimmer");
  newUG2.set_pin_number(8);
  newUG2.set_mode("PWM");
  newUG2.set_value("255");
  DB.setUsedGpio(sdevice, newUG2);
*/
  // DB.removeUsedGpio(sdevice, 0);
  sdevice.set_sta_pass("123456789");
  myWifi.begin( sdevice );

  websocket.updateGPIO("mi id", true);
}


void loop(void)
{ 

}

