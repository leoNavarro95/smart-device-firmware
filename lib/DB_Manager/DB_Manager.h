#pragma once

#include<ArduinoJson.h>
#include "../../include/SmartDevice_Model.hpp"

#define DOC_SIZE 4096 // by tool: https://arduinojson.org/v6/assistant
#define MAX_SIZE_PATH 46

// Singleton pattern. In case of use a RTOS, need to be managed to be thread safe
class DB_Manager_ {

private:
    DB_Manager_() = default;
    uint8_t size_used_gpios;
    uint8_t size_gpios;
    StaticJsonDocument<DOC_SIZE> doc;
    char path[MAX_SIZE_PATH];

public:
    static DB_Manager_ &getInstance(); // Accessor for singleton instance
    DB_Manager_(const DB_Manager_ &) = delete; // no copying
    DB_Manager_ &operator=(const DB_Manager_ &) = delete;

    bool begin( const char* database_path);
    void initDeviceFromDB(SmartDevice &sDevice);
    esp_err_t refresh(SmartDevice &sDevice, bool newFile = false);
    void createDefault(SmartDevice &sDevice){this->refresh(sDevice, true);}

    /**
     * @brief Print all used gpios, just for debbuggin propose
     * @attention usage 
     * @code {.cpp}
     *  DB.printGpioArr(sdevice.get_gpios_status());
     * @endcode
     * @param used_gpios pointer to array with the used gpios
     */
    void printGpioArr( UsedGpio * used_gpios);
    /**
     * @brief Print all gpios status, just for debbuggin propose
     * 
     * @param gpios pointer to array with the gpios status
     */
    void printGpioArr( GpioStatus * gpios);
    
    /**
     * @brief Attempts to set a new used gpio
     * 
     * @param sDevice device object to work with
     * @param gpio new gpio instance for update
     * @return ESP_OK if success, ESP_FAIL if fails
     */
    esp_err_t setUsedGpio( SmartDevice &sDevice, UsedGpio newUsedGpio);

    // TODO falta por implementar
    void removeUsedGpio( SmartDevice &sDevice, uint8_t idOfGpioToRemove);

    const uint8_t & get_num_of_used_gpios() const { return size_used_gpios; }
    void set_num_of_used_gpios(const uint8_t & value) { this->size_used_gpios = value; }

    const uint8_t & get_size_gpios() const { return size_gpios; }
    void set_size_gpios(const uint8_t & value) { this->size_gpios = value; }
};

extern DB_Manager_ &DB;


/*
//Guarda la configuracion en la SPIFFS en config.json --Llamado desde WebSochets.hpp 
void saveConfig(String SSID, String Pass, int Id){
    String paqueteJSON;
    const size_t capacity = JSON_OBJECT_SIZE(6) + 79;
    DynamicJsonDocument doc(capacity);

    doc["ssid"] = SSID;
    doc["id"] = Id;
    doc["pass"] = Pass;
    //Vuelve a tomar los valores ya configurados para no perderlos
    doc["nivelMinimo"] = NIVEL_BAJO;
    doc["nivelMaximo"] = NIVEL_ALTO;
    doc["flujoMinimo"] = UMBRAL_FLUJO;

    serializeJson(doc, paqueteJSON);//en paqueteJSON ya esta serializado el Json con los respectivos campos llenos

    // Serial.println("Guardando paquete de config: " + paqueteJSON);
    writeFile(SPIFFS, "/config.json", paqueteJSON.c_str());
    //luego se debe reiniciar el esp32 para que sean validos los cambios
    //quiero enviar un responce "OK" para decirle a la web que se admitió el cambio y si no un "ERROR"
    ESP.restart();


}


//Obtiene la configuracion desde el archivo config.json que se encuentra en la SPIFFS
void getConfig(){
    String DatoJSON = readFile(SPIFFS, "/config.json");
    if(DatoJSON == "ERROR"){
        Serial.print("Error leyendo archivo de config. Configuración tomada por defecto");
        
        String paqueteJSON;
        StaticJsonDocument<300> doc;
        doc["ssid"] = SSID;
        doc["id"] = 1;//1 indica que es por defecto, 2 que es custom
        doc["pass"] = PASSWORD;
        serializeJson(doc, paqueteJSON);//en paqueteJSON ya esta serializado el Json con los respectivos campos llenos

        // char paketeChar[paqueteJSON.length() + 1];
        // strcpy(paketeChar, paqueteJSON.c_str()); //convierte el packete en string a char array
        Serial.println("Guardando paquete de config: " + paqueteJSON);
        writeFile(SPIFFS, "/config.json", paqueteJSON.c_str());
    }
    else{
        StaticJsonDocument<300> doc;
        DeserializationError error = deserializeJson(doc, DatoJSON);
        if (error) { Serial.println("Error de parseado de Json"); return;}
        SSID = doc["ssid"] | "Sistema Manati ApError";//obtiene el valor de la etiqueta ssid, si no existe se settea una por defecto
        PASSWORD = doc["pass"] | "Administrador";
        int id = (int)doc["id"] | 1;
        if(id == 1)     Serial.println("Advertencia está usando configuración por defecto");

        NIVEL_ALTO = doc["nivelMaximo"] | 100;
        NIVEL_BAJO = doc["nivelMinimo"] | 70;
        UMBRAL_FLUJO = doc["flujoMinimo"] | 5;

        Serial.println("##1");
        Serial.println(String(NIVEL_ALTO) + " " + String(NIVEL_BAJO) + " " + String(UMBRAL_FLUJO));
        Serial.println("##1");
    }
}

*/