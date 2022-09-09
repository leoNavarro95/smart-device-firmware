#include "SmartDevice_Model.hpp"

void setGPIO(String id, bool state)
{
   Serial.print("Set GPIO ");
   Serial.print(id);
   Serial.print(": ");
   Serial.println(state);
   digitalWrite(LED_BUILTIN, state);
}

void setPWM(String id, int pwm)
{
   Serial.print("Set PWM ");
   Serial.print(id);
   Serial.print(": ");
   Serial.println(pwm);
}

void doAction(String actionId)
{
   Serial.print("Doing action: ");
   Serial.println(actionId);
}

void setWifi( SmartDevice &sDevice, const char * mode, const char * ssid, const char * pass ){
   
   sDevice.set_connection_mode( mode );

   if( strcmp(mode, "STA" ) == 0 ){
      sDevice.set_sta_ssid( ssid );
      sDevice.set_sta_pass( pass );
   } else if( strcmp(mode, "AP" ) == 0  ) { 
      sDevice.set_ap_ssid( ssid );
      sDevice.set_ap_pass( pass );
   } else {
      log_e("Incorrect Wifi mode");
   }

   log_d("Wifi mode: %s", sDevice.get_connection_mode() );
   log_d("Wifi ssid: %s", sDevice.get_wifi_ssid() );
   log_d("Wifi pass: %s", sDevice.get_wifi_pass() );
}