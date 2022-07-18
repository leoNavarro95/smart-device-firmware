#pragma once

#include<WiFi.h>

#include "SmartDevice_Model.hpp"
#include "DB_Manager.h"

class WifiManager
{
public:
    WifiManager() = default;
    virtual ~WifiManager() = default;    

private:
    IPAddress ip, gateway, subnet;

    void _setNet(IpConfig &ipConfig){
        // copy all address with the ipConfig Object
        const char * _ipAddress = ipConfig.get_ip_address();
        const char * _gateway = ipConfig.get_gateway_address();
        const char * _subnet = ipConfig.get_subnet_mask();

        this->ip.fromString(_ipAddress)    ? log_d("ip set success") : log_e("ip set error, invalid format, value: %s", _ipAddress);
        this->gateway.fromString(_gateway) ? log_d("gateway set success") : log_e("gateway set error, invalid format, value: %s", _gateway);
        this->subnet.fromString(_subnet)       ? log_d("subnet set success") : log_e("subnet set error, invalid format, value: %s", _subnet);
    }

    void connectWiFi_STA(IpConfig &ipConfig, const char* sta_pass, const char* sta_ssid)
    {
        bool useStaticIP = ipConfig.get_mode() == "Static" ? true : false;

        Serial.println("");
        WiFi.mode(WIFI_STA);

        WiFi.begin(sta_ssid, sta_pass);
        if (useStaticIP)
        {
            log_d("Using static IP");
            this->_setNet(ipConfig);
            WiFi.config(this->ip, this->gateway, this->subnet);
        }

        log_d("Connecting to %s ...", sta_ssid);

        // TODO: este metodo es bloqueante, no va a salir del while mientras no se conecte. Existen formas mejores usando eventos del sistema, implementarlas luego
        while (WiFi.status() != WL_CONNECTED)
        {
            delay(100);
            Serial.print('.');
        }

        Serial.println("");
        Serial.print("Iniciado STA:\t");
        Serial.println(sta_ssid);
        Serial.print("IP address:\t");
        Serial.println(WiFi.localIP());
    }

    void connectWiFi_AP(IpConfig &ipConfig, const char* ap_pass, const char* ap_ssid)
    {
        bool useStaticIP = ipConfig.get_mode() == "Static" ? true : false;

        WiFi.mode(WIFI_AP);
        Serial.print("\nIniciando AP:\n");
        Serial.println(ap_ssid);

        while (!WiFi.softAP(ap_ssid, ap_pass))
        {
            Serial.println(".");
            delay(100);
        }
        if (useStaticIP)
        {   
            log_d("Using static IP");
            this->_setNet(ipConfig);
            WiFi.softAPConfig(this->ip, this->gateway, this->subnet);
        }

        Serial.print("\n AP SSID:\t");
        Serial.println(ap_ssid);
        Serial.print("IP address:\t");
        Serial.println(WiFi.softAPIP());
    }

public:
    /**
     * @brief Init wifi controller from sDevice configured IpConfig, which it is getted from database in init process
     * 
     * @param sDevice This object has IpConfig with all needed configuration
     */
    void begin(SmartDevice &sDevice)
    {   
        IpConfig ipConfig = sDevice.get_ip_config();
        const char * conn_mode = sDevice.get_connection_mode();
        log_d("Connection mode: %s", conn_mode);

        if ( strcmp(conn_mode, "STA" ) == 0 ){ 
            const char* sta_pass = sDevice.get_sta_pass();
            const char* sta_ssid = sDevice.get_sta_ssid();

            connectWiFi_STA(ipConfig, sta_pass, sta_ssid);
        } else {
            const char* ap_pass = sDevice.get_ap_pass();
            const char* ap_ssid = sDevice.get_ap_ssid();

            connectWiFi_AP(ipConfig, ap_pass, ap_ssid);
        }
        
        sDevice.set_mac(WiFi.macAddress().c_str());

        // saving in model Dynamic IP, when in Static IP mode, the ip addresses are getted from database 
        if( strcmp(ipConfig.get_mode(), "Dynamic" ) == 0){
            IpConfig newIpConfig;
            
            if(strcmp(sDevice.get_connection_mode(), "AP") == 0){
                newIpConfig.set_ip_address( WiFi.softAPIP().toString().c_str() );
                newIpConfig.set_gateway_address( WiFi.softAPBroadcastIP().toString().c_str() ); //TODO: averiguar como obtener realmente las IP para gateway y subnet
                newIpConfig.set_subnet_mask( WiFi.softAPNetworkID().toString().c_str() );
            } else{
                newIpConfig.set_ip_address( WiFi.localIP().toString().c_str() );
                newIpConfig.set_gateway_address( WiFi.gatewayIP().toString().c_str() );
                newIpConfig.set_subnet_mask( WiFi.subnetMask().toString().c_str() );
            }

            newIpConfig.set_mode( "Dynamic" );
            
            sDevice.set_ip_config( newIpConfig );
        }
        
        DB.refresh( sDevice );
    }
};