#include "DB_Manager.h"
#include <Arduino.h>

#include<ArduinoJson.h>
#include "FileSystem.h"

void DB_Manager_::begin() {
  pinMode(LED_BUILTIN, OUTPUT);

  // blink the led a few times
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
  }

  digitalWrite(LED_BUILTIN, LOW);
}

void DB_Manager_::getUsedGPIOS(){
    String readJSON = Files.readFile(LittleFS, "/database/esp_soc.json");
    Serial.println(readJSON);
    
    /*
    if(readJSON == "ERROR"){
        Serial.print("Error leyendo archivo");
        
        String paqueteJSON;
        StaticJsonDocument<300> doc;
        doc["ssid"] = SSID;
        doc["id"] = 1;//1 indica que es por defecto, 2 que es custom
        doc["pass"] = PASSWORD;
        serializeJson(doc, paqueteJSON);//en paqueteJSON ya esta serializado el Json con los respectivos campos llenos

        // char paketeChar[paqueteJSON.length() + 1];
        // strcpy(paketeChar, paqueteJSON.c_str()); //convierte el packete en string a char array
        Serial.println("Guardando paquete de config: " + paqueteJSON);
        writeFile(LittleFS, "/config.json", paqueteJSON.c_str());
    }
    else{
        StaticJsonDocument<300> doc;
        DeserializationError error = deserializeJson(doc, readJSON);
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
    */
}

DB_Manager_ &DB_Manager_::getInstance() {
  static DB_Manager_ instance;
  return instance;
}

DB_Manager_ &DB = DB.getInstance();