#include "DB_Manager.h"
#include <Arduino.h>


#include "FileSystem.h"


//Codigo apoyado por herramienta https://arduinojson.org/v6/assistant

//TODO Ver MessagePack como alternativa para empaquetar los JSON: https://msgpack.org/index.html
// ArduinoJson es compatible con MessagePack

// TODO ver esta lib que permite trabajar con Streams sobre archivos https://github.com/bblanchon/ArduinoStreamUtils 



bool DB_Manager_::begin(const char* database_path){
  String readJSON = Files.readFile(LittleFS, database_path);
  // Serial.printf("contenido del archivo: %s\n", readJSON.c_str());
  
  DeserializationError error = deserializeJson(this->doc, readJSON);

  if (error) {
    Serial.print("[DB][E] deserializeJson() failed: ");
    Serial.println(error.c_str());
    return false; //error
  }
  return true; //success
}

void DB_Manager_::initDeviceFromDB(SmartDevice *sDevice){

  sDevice->set_ap_pass(doc["ap_pass"]);
  sDevice->set_ap_ssid(doc["ap_ssid"]);
  sDevice->set_connection_mode(doc["connection_mode"]);
  sDevice->set_mac(doc["mac"]);
  sDevice->set_sta_ssid(doc["sta_ssid"]);
  sDevice->set_sta_pass(doc["sta_pass"]);

  JsonObject ip_config = doc["ip_config"];
  IpConfig ipConfig;
  ipConfig.set_mode(ip_config["mode"]);
  ipConfig.set_ip_address(ip_config["ip_address"]);
  ipConfig.set_subred_mask_address(ip_config["subred_mask_address"]);
  ipConfig.set_gateway_address(ip_config["gateway_address"]);
  
  sDevice->set_ip_config(ipConfig);

  JsonArray used_gpios_from_doc = doc["used_gpios"].as<JsonArray>();
  size_t size_used_gpios = used_gpios_from_doc.size();
  this->set_size_used_gpios(size_used_gpios);  //TODO: probably have to set this in begin method
  UsedGpio usedGpios[size_used_gpios];

  Serial.printf("[DB][i]- Used GPIO(s): %d\n", size_used_gpios);

  uint8_t index = 0;
  for (JsonObject used_gpio : used_gpios_from_doc) {
    usedGpios[index].set_id(used_gpio["id"]);
    usedGpios[index].set_pin_number(used_gpio["pin_number"]);
    usedGpios[index].set_mode(used_gpio["mode"]);
    usedGpios[index].set_label(used_gpio["label"]);
    usedGpios[index].set_value(used_gpio["value"]);
    index++;
  }

  sDevice->set_used_gpios(usedGpios);


  UsedGpio *usedGpios2 = sDevice->get_used_gpios();

  for(int i = 0; i < size_used_gpios; i++){
    Serial.println("----------------------------------");
    Serial.printf("id: %d\n", usedGpios2[i].get_id());
    Serial.printf("pin: %d\n", usedGpios2[i].get_pin_number());
    Serial.printf("mode: %s\n", usedGpios2[i].get_mode());
    Serial.printf("label: %s\n", usedGpios2[i].get_label());
    Serial.printf("value: %s\n", usedGpios2[i].get_value());
    Serial.println("----------------------------------");
    Serial.println();
  }

  JsonArray gpios_from_doc = doc["gpios"].as<JsonArray>();
  size_t size_gpios = gpios_from_doc.size();
  Serial.printf("gpio size: %d\n\n", size_gpios);
  this->set_size_gpios(size_gpios);  //TODO: probably have to set this in begin method
  Gpio gpios[size_gpios];

  index = 0;
  for (JsonObject gpio : gpios_from_doc) {
    gpios[index].set_id(gpio["id"]);
    gpios[index].set_pin_number(gpio["pin_number"]);
    gpios[index].set_used(gpio["used"]);
    index++;
  }
  sDevice->set_gpios(gpios);

}

DB_Manager_ &DB_Manager_::getInstance() {
  static DB_Manager_ instance;
  return instance;
}

DB_Manager_ &DB = DB.getInstance();