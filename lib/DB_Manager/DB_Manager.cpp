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

void DB_Manager_::initDeviceFromDB( SmartDevice &sDevice ){

  sDevice.set_ap_pass(this->doc["ap_pass"]);
  sDevice.set_ap_ssid(this->doc["ap_ssid"]);
  sDevice.set_connection_mode(this->doc["connection_mode"]);
  sDevice.set_mac(this->doc["mac"]);
  sDevice.set_sta_ssid(this->doc["sta_ssid"]);
  sDevice.set_sta_pass(this->doc["sta_pass"]);

  JsonObject ip_config = this->doc["ip_config"];
  IpConfig ipConfig;
  ipConfig.set_mode(ip_config["mode"]);
  ipConfig.set_ip_address(ip_config["ip_address"]);
  ipConfig.set_subred_mask_address(ip_config["subred_mask_address"]);
  ipConfig.set_gateway_address(ip_config["gateway_address"]);
  
  sDevice.set_ip_config(ipConfig);

  JsonArray used_gpios_from_doc = this->doc["used_gpios"].as<JsonArray>();
  size_t size_used_gpios = used_gpios_from_doc.size();
  this->set_num_of_used_gpios(size_used_gpios);  //TODO: probably have to set this in begin method
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

  sDevice.set_used_gpios(usedGpios, size_used_gpios);

  JsonArray gpios_from_doc = this->doc["gpios"].as<JsonArray>();
  size_t size_gpios = gpios_from_doc.size();
  
  Serial.printf("gpio size: %d\n\n", size_gpios);
  this->set_size_gpios(size_gpios);  //TODO: probably have to set this in begin method
  GpioStatus gpios[size_gpios];

  index = 0;
  for (JsonObject gpio : gpios_from_doc) {
    gpios[index].set_id(gpio["id"]);
    gpios[index].set_pin_number(gpio["pin_number"]);
    gpios[index].set_used(gpio["used"]);
    index++;
  }
  sDevice.set_gpios_status(gpios, size_gpios);

}

void DB_Manager_::printGpioArr(UsedGpio * used_gpios){
  uint8_t size_u_gpios = this->get_num_of_used_gpios();

  for(int i = 0; i < size_u_gpios; i++){
    log_d("++++++++++++++++++++++++++++++++++");
    log_d("id: %d", used_gpios[i].get_id());
    log_d("pin: %d", used_gpios[i].get_pin_number());
    log_d("mode: %s", used_gpios[i].get_mode());
    log_d("label: %s", used_gpios[i].get_label());
    log_d("value: %s", used_gpios[i].get_value());
    log_d("\n");
  }
}

void DB_Manager_::printGpioArr(GpioStatus * gpios){
  uint8_t size_gpios = DB.get_size_gpios();
  
  for(int i = 0; i < size_gpios; i++){
    log_d("====================================");
    log_d("id: %d", gpios[i].get_id());
    log_d("pin: %d", gpios[i].get_pin_number());
    log_d("used: %s", (gpios[i].get_used() ? "yes" : "no"));
    log_d("\n");
  }
}

//TODO: poner privado una funcion que escriba en la base de datos el nuevo gpio

esp_err_t DB_Manager_::setUsedGpio( SmartDevice &sDevice, UsedGpio newUsedGpio ){

  GpioStatus * gpios = sDevice.get_gpios_status();
  const uint8_t size_gpios = this->get_size_gpios();
  uint8_t gpio_index = newUsedGpio.get_pin_number();  // the key to access the gpio array it's the pin number of the attemped to use gpio

  //check if size of gpio is in range
  if(gpio_index > size_gpios){
    log_w("Trying to use new gpio out of range");
    return ESP_FAIL;
  }

  // see if gpio it is available 
  if(gpios[gpio_index].get_used()){
    log_w("The gpio is already in use");
    return ESP_FAIL;
  }

  // gpio is available to use
  UsedGpio * usedGpios = sDevice.get_used_gpios();
  const uint8_t num_used_gpios = this->get_num_of_used_gpios();

  // set id equal to the index in used gpio array
  newUsedGpio.set_id( num_used_gpios );
  //write object in next position of array of usedGpios
  usedGpios[num_used_gpios] = newUsedGpio;

  sDevice.set_used_gpios(usedGpios, num_used_gpios + 1);
  this->set_num_of_used_gpios(num_used_gpios + 1);
  
  //set used status to true
  gpios[gpio_index].set_used(true);

  log_d("Inserted new gpio successfuly");
  return ESP_OK;
}


DB_Manager_ &DB_Manager_::getInstance() {
  static DB_Manager_ instance;
  return instance;
}

DB_Manager_ &DB = DB.getInstance();