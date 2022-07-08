#include "DB_Manager.h"
#include <Arduino.h>

#include<ArduinoJson.h>
#include "FileSystem.h"

//TODO OJO ver herramienta para trabajar con arduinojson https://arduinojson.org/v6/assistant

//TODO Ver MessagePack como alternativa para empaquetar los JSON: https://msgpack.org/index.html
// ArduinoJson es compatible con MessagePack



void DB_Manager_::getUsedGPIOS(){
  String readJSON = Files.readFile(LittleFS, "/database/esp_soc.json");
  // char * readJSON = Files.readFile(LittleFS, "/test.txt");
  Serial.printf("Valor leido: %s\n", readJSON.c_str());
  
  StaticJsonDocument<2048> doc;

  DeserializationError error = deserializeJson(doc, readJSON);

  if (error) {
    Serial.print("[DB][E] deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }

  const char* mac = doc["mac"]; // "00:00:5e:00:53:af"
  const char* ap_ssid = doc["ap_ssid"]; // "admin"
  const char* ap_pass = doc["ap_pass"]; // "admin"
  const char* sta_ssid = doc["sta_ssid"]; // nullptr
  const char* sta_pass = doc["sta_pass"]; // nullptr
  const char* connection_mode = doc["connection_mode"]; // "AP"

  Serial.printf("mac: %s\n", mac);

  JsonObject ip_config = doc["ip_config"];
  const char* ip_config_mode = ip_config["mode"]; // "Dynamic"
  const char* ip_config_ip_address = ip_config["ip_address"]; // "192.168.1.234"
  const char* ip_config_subred_mask_address = ip_config["subred_mask_address"]; // "255.255.255.0"
  const char* ip_config_gateway_address = ip_config["gateway_address"]; // "192.168.1.1"

  for (JsonObject used_gpio : doc["used_gpios"].as<JsonArray>()) {
    int used_gpio_id = used_gpio["id"]; // 0, 1
    int used_gpio_pin_number = used_gpio["pin_number"]; // 0, 25
    const char* used_gpio_mode = used_gpio["mode"]; // "INPUT", "OUTPUT"
    const char* used_gpio_label = used_gpio["label"]; // "Button on board", "LED on board"
    const char* used_gpio_value = used_gpio["value"]; // "LOW", "LOW"
  }

  for (JsonObject gpio : doc["gpios"].as<JsonArray>()) {
    int gpio_id = gpio["id"]; // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20
    int gpio_pin_number = gpio["pin_number"]; // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, ...
    bool gpio_used = gpio["used"]; // true, false, false, false, false, false, false, false, false, false, ...
  }
}

DB_Manager_ &DB_Manager_::getInstance() {
  static DB_Manager_ instance;
  return instance;
}

DB_Manager_ &DB = DB.getInstance();