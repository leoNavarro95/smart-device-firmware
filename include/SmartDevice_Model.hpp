#pragma once

#define SIZE_MAC 17
#define MAX_SIZE_MODE 8
#define MAX_SIZE_CONN_MODE 4
#define MAX_SIZE_LABEL 16
#define MAX_SIZE_VALUE 8
#define MAX_SIZE_SSID 32
#define MAX_SIZE_PASS 31

#define MAX_SIZE_IP_MODE 8  // Static | Dynamic
#define MAX_SIZE_IP_ADDRESS 15



#define MAX_SIZE_USED_GPIOS 30
#define SIZE_GPIOS 30

/**
 * @brief Represent a gpio and if it is used or not.
 *  This class will be used inside an array of objects of it. 
 *  This array of @e GpioStatus represent all GPIOS in the system and its
 *  availability.
 * 
 */
class GpioStatus {
    public:
    GpioStatus() = default;
    virtual ~GpioStatus() = default;

    private:
    uint8_t id;
    uint8_t pin_number;
    bool used;

    public:
    const uint8_t & get_id() const { return id; }
    uint8_t & get_mutable_id() { return id; }
    void set_id(const uint8_t & value) { this->id = value; }

    const uint8_t & get_pin_number() const { return pin_number; }
    uint8_t & get_mutable_pin_number() { return pin_number; }
    void set_pin_number(const uint8_t & value) { this->pin_number = value; }

    const bool & get_used() const { return used; }
    bool & get_mutable_used() { return used; }
    void set_used(const bool & value) { this->used = value; }
};

class IpConfig {
    public:
    IpConfig() = default;
    virtual ~IpConfig() = default;

    private:
    char mode[MAX_SIZE_IP_MODE]; //Static|Dynamic
    char ip_address[MAX_SIZE_IP_ADDRESS]; // 111.111.111.111
    char subnet_mask[MAX_SIZE_IP_ADDRESS];
    char gateway_address[MAX_SIZE_IP_ADDRESS];
    // TODO: DNS address

    public:
    const char* get_mode() const { return mode; }
    void set_mode(const char* value) { snprintf(this->mode, MAX_SIZE_IP_MODE, value);} // strcpy(this->mode, value); 

    const char* get_ip_address() const { return ip_address; }
    void set_ip_address(const char* value) { snprintf(this->ip_address, MAX_SIZE_IP_ADDRESS, value);}

    const char* get_subnet_mask() const { return subnet_mask; }
    void set_subnet_mask(const char* value) { snprintf(this->subnet_mask, MAX_SIZE_IP_ADDRESS, value);}
    
    const char* get_gateway_address() const { return gateway_address; }
    void set_gateway_address(const char* value) { snprintf(this->gateway_address, MAX_SIZE_IP_ADDRESS, value);}

};

class UsedGpio {
    public:
    UsedGpio() = default;
    virtual ~UsedGpio() = default;

    private:
    uint8_t id;
    uint8_t pin_number;
    char mode[MAX_SIZE_MODE];     //OUTPUT | INPUT | ANALOG | PWM...
    char label[MAX_SIZE_LABEL];    //Bombillo sala
    char value[MAX_SIZE_VALUE];    // ON | OFF | true | false | 1023 | 255

    public:
    const uint8_t & get_id() const { return id; }
    uint8_t & get_mutable_id() { return id; }
    void set_id(const uint8_t & value) { this->id = value; }

    const uint8_t & get_pin_number() const { return pin_number; }
    uint8_t & get_mutable_pin_number() { return pin_number; }
    void set_pin_number(const uint8_t & value) { this->pin_number = value; }

    const char * get_mode() { return mode; }
    void set_mode(const char * value) { snprintf(this->mode, MAX_SIZE_MODE, value); }

    const char * get_label() { return label; }

    /**
     * @brief Set the label object
     * 
     * @param value with less than MAX_SIZE_LABEL characters
     */
    void set_label(const char * value) { snprintf(this->label, MAX_SIZE_LABEL, value); }

    const char * get_value() { return value; }
    void set_value(const char * value) { snprintf(this->value, MAX_SIZE_VALUE, value); }
};

class SmartDevice {
    public:
    SmartDevice() = default;
    virtual ~SmartDevice() = default;

    private:
    char mac[SIZE_MAC]; //11:00:5e:00:53:af
    char ap_ssid[MAX_SIZE_SSID];
    char ap_pass[MAX_SIZE_PASS];
    char sta_ssid[MAX_SIZE_SSID];
    char sta_pass[MAX_SIZE_PASS];
    // TODO: mode multiAP
    char connection_mode [MAX_SIZE_CONN_MODE]; // 'STA'|'AP' 
    
    IpConfig ip_config;
    UsedGpio used_gpios[MAX_SIZE_USED_GPIOS];
    GpioStatus gpios[SIZE_GPIOS];

    public:
    const char* get_mac() const { return mac; }
    void set_mac(const char * value) { snprintf(this->mac, SIZE_MAC, value);}

    const char * get_ap_ssid() { return ap_ssid; }
    void set_ap_ssid(const char * value) { snprintf(this->ap_ssid, MAX_SIZE_SSID, value); }

    const char * get_ap_pass() { return ap_pass; }
    void set_ap_pass(const char * value) { snprintf(this->ap_pass, MAX_SIZE_PASS, value); }

    const char * get_sta_ssid() { return sta_ssid; }
    void set_sta_ssid(const char * value) { snprintf(this->sta_ssid, MAX_SIZE_SSID, value);}

    const char * get_sta_pass() { return sta_pass; }
    void set_sta_pass(const char * value) { snprintf(this->sta_pass, MAX_SIZE_PASS, value);}

    const char* get_connection_mode() const { return connection_mode; }
    void set_connection_mode(const char* value) { snprintf(this->connection_mode, MAX_SIZE_CONN_MODE, value);}

    /**
     * @brief Get the wifi ssid for the current connection mode
     * 
     * @return const char* 
     */
    const char* get_wifi_ssid() const {
        if( strcmp(this->connection_mode, "STA" ) == 0 )
            return sta_ssid;
        else
            return ap_ssid;
    }

    /**
     * @brief Get the wifi pass for the current connection mode
     * 
     * @return const char* 
     */
    const char* get_wifi_pass() const {
        if( strcmp(this->connection_mode, "STA" ) == 0 )
            return sta_pass;
        else
            return ap_pass;
    }

    const IpConfig & get_ip_config() const { return ip_config; }
    IpConfig & get_mutable_ip_config() { return ip_config; }
    void set_ip_config(const IpConfig & value) { this->ip_config = value; }
    
    UsedGpio* get_used_gpios() { return used_gpios;}
    
    void set_used_gpios(UsedGpio* value, uint8_t size) {
        if(size >= MAX_SIZE_USED_GPIOS){
            log_e("UsedGpio array size is bigger than reserved");
            return;
        } 
        for(int i = 0; i < size; i++){
            this-> used_gpios[i] = value[i];
        }
    }

    GpioStatus* get_gpios_status() { return gpios; }
    void set_gpios_status(GpioStatus* value, uint8_t size) { 
        if(size >= SIZE_GPIOS){
            log_e("GpioStatus array size is bigger than reserved");
            return;
        }
        for(int i = 0; i < SIZE_GPIOS; i++){
            this-> gpios[i] = value[i];
        }
    }

    // const std::vector<UsedGpio> & get_used_gpios() const { return used_gpios; }
    // std::vector<UsedGpio> & get_mutable_used_gpios() { return used_gpios; }
    // void set_used_gpios(const std::vector<UsedGpio> & value) { this->used_gpios = value; }
};


// DEMO USING THIS CLASS
/*
  if(DB.begin("/database/esp_soc.json"))
    DB.initDeviceFromDB(sdevice);

  Serial.printf("ap pass: %s\n", sdevice.get_ap_pass());
  Serial.printf("ap ssid: %s\n", sdevice.get_ap_ssid());
  Serial.printf("conncetion mode: %s\n", sdevice.get_connection_mode());
  Serial.printf("mac: %s\n", sdevice.get_mac());
  Serial.printf("sta pass: %s\n", sdevice.get_sta_pass());
  Serial.printf("sta ssid: %s\n", sdevice.get_sta_ssid());

  UsedGpio * used_gpios = sdevice.get_used_gpios(); 
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

  Gpio * gpios = sdevice.get_gpios(); 
  uint8_t size_gpios = DB.get_size_gpios();
  

  for(int i = 0; i < size_gpios; i++){
    Serial.println("====================================");
    Serial.printf("id: %d\n", gpios[i].get_id());
    Serial.printf("pin: %d\n", gpios[i].get_pin_number());
    Serial.printf("used: %s\n", (gpios[i].get_used() ? "yes" : "no"));
    Serial.println("====================================");
    Serial.println();
  }
*/