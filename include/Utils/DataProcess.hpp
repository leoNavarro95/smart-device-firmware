#include<Arduino.h>
#include<WiFi.h>
#include<ArduinoJson.h>

#include "../SmartDevice_Model.hpp"
#include "DB_Manager.h"

/* Usage
  StaticJsonDocument<3072> doc_to_save; // DocSize obtained from arduinoJson assistant web
  setJsonFromSDevice( doc_to_save, sDevice, newFileNeeded ); 

  int length = measureJson(doc_to_save);
  char outputData[length + 1];
  serializeJson(doc_to_save, outputData, sizeof(outputData));
*/
// TODO: Esta funcion no trabaja correctamente, corrompe el contenido de la flash. Quisiera implementarla en el metodo DB.refresh() para obtener un json serializado con los datos del sistema
void setJsonFromSDevice( JsonDocument &doc_to_write, SmartDevice &sDevice, bool default_template)
{
    const char *mac = WiFi.macAddress().c_str();

    doc_to_write["mac"]              = default_template ? mac         : sDevice.get_mac();
    doc_to_write["ap_ssid"]          = default_template ? "Admin"     : sDevice.get_ap_ssid();
    doc_to_write["ap_pass"]          = default_template ? ""          : sDevice.get_ap_pass();
    doc_to_write["sta_ssid"]         = default_template ? "Anonymous" : sDevice.get_sta_ssid();
    doc_to_write["sta_pass"]         = default_template ? "12345678"  : sDevice.get_sta_pass();
    doc_to_write["connection_mode"]  = default_template ? "AP"        : sDevice.get_connection_mode();


    JsonObject ip_config = doc_to_write.createNestedObject("ip_config");
    IpConfig ipConfig;

    if (default_template){
        log_d("default template");
        ipConfig.set_mode("Dynamic");
        ipConfig.set_ip_address("0.0.0.0");
        ipConfig.set_subnet_mask("0.0.0.0");
        ipConfig.set_gateway_address("0.0.0.0");
    }
    else{
        log_d("template from DB");
        ipConfig = sDevice.get_ip_config();
    }

    const char*  ip_mode         = ipConfig.get_mode();
    const char*  ip_address      = ipConfig.get_ip_address();
    const char*  subnet_mask     = ipConfig.get_subnet_mask();
    const char*  gateway_address = ipConfig.get_gateway_address();

    log_d("ip_mode: %s", ip_mode);
    log_d("ip_address: %s", ip_address);
    log_d("subnet_mask: %s", subnet_mask);
    log_d("gateway_address: %s", gateway_address);

    ip_config["mode"]                = ip_mode;
    ip_config["ip_address"]          = ip_address;
    ip_config["subred_mask_address"] = subnet_mask;
    ip_config["gateway_address"]     = gateway_address;

    // usedgpios
    UsedGpio *usedGpios = sDevice.get_used_gpios();
    uint8_t sizeUsedGpios = DB.get_num_of_used_gpios();

    JsonArray used_gpios = doc_to_write.createNestedArray("used_gpios");

    for (int i = 0; i < sizeUsedGpios; i++)
    {
        JsonObject used_gpio = used_gpios.createNestedObject();
        used_gpio["id"]         = usedGpios[i].get_id();
        used_gpio["pin_number"] = usedGpios[i].get_pin_number();
        used_gpio["mode"]       = usedGpios[i].get_mode();
        used_gpio["label"]      = usedGpios[i].get_label();
        used_gpio["value"]      = usedGpios[i].get_value();
    }

    // gpio status
    GpioStatus *gpiosStatus = sDevice.get_gpios_status();
    // TODO: Buscar una forma, por ejemplo desde la web, de que el usuario setee la cantidad deseada de pines en caso de no existir el archivo de la base de datos
    uint8_t sizeGpioStatus = default_template ? 20 : DB.get_size_gpios(); // DB.get_size_gpios() get the size of gpios by the database file, in this case the file does not exist so it's hardcoded

    JsonArray gpios = doc_to_write.createNestedArray("gpios");
    for (uint8_t i = 0; i < sizeGpioStatus; i++)
    {
        JsonObject gpio_status     = gpios.createNestedObject();
        gpio_status["id"]          = default_template ? i : gpiosStatus[i].get_id();
        gpio_status["pin_number"]  = default_template ? i : gpiosStatus[i].get_pin_number();
        gpio_status["used"]        = default_template ? false : gpiosStatus[i].get_used();
    }

}


