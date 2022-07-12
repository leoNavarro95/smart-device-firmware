#pragma once

#define SIZE_MAC 17
#define MAX_SIZE_MODE 8
#define MAX_SIZE_CONN_MODE 4
#define MAX_SIZE_LABEL 16
#define MAX_SIZE_VALUE 8
#define MAX_SIZE_SSID 32
#define MAX_SIZE_PASS 31

#define MAX_SIZE_USED_GPIOS 30
#define SIZE_GPIOS 30

class Gpio {
    public:
    Gpio() = default;
    virtual ~Gpio() = default;

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
    char mode[5]; //Static|Dynamic
    char ip_address[16]; // 111.111.111.111
    char subred_mask_address[16];
    char gateway_address[16];
    // TODO: DNS address

    public:
    const char* get_mode() const { return mode; }
    void set_mode(const char* value) { strcpy(this->mode, value);}

    const char* get_ip_address() const { return ip_address; }
    void set_ip_address(const char* value) { strcpy(this->ip_address, value);}

    const char* get_subred_mask_address() const { return subred_mask_address; }
    void set_subred_mask_address(const char* value) { strcpy(this->subred_mask_address, value);}
    
    const char* get_gateway_address() const { return gateway_address; }
    void set_gateway_address(const char* value) { strcpy(this->gateway_address, value);}

};

class UsedGpio {
    public:
    UsedGpio() = default;
    virtual ~UsedGpio() = default;

    private:
    uint8_t id;
    uint8_t pin_number;
    char mode[MAX_SIZE_MODE + 1];     //OUTPUT | INPUT | ANALOG | PWM...
    char label[MAX_SIZE_LABEL + 1];    //Bombillo sala
    char value[MAX_SIZE_VALUE + 1];    // ON | OFF | true | false | 1023 | 255

    public:
    const uint8_t & get_id() const { return id; }
    uint8_t & get_mutable_id() { return id; }
    void set_id(const uint8_t & value) { this->id = value; }

    const uint8_t & get_pin_number() const { return pin_number; }
    uint8_t & get_mutable_pin_number() { return pin_number; }
    void set_pin_number(const uint8_t & value) { this->pin_number = value; }

    const char * get_mode() { return mode; }
    void set_mode(const char * value) { strcpy(this->mode, value); }

    const char * get_label() { return label; }
    void set_label(const char * value) { strcpy(this->label, value); }

    const char * get_value() { return value; }
    void set_value(const char * value) { strcpy(this->value, value); }
};

class SmartDevice {
    public:
    SmartDevice() = default;
    virtual ~SmartDevice() = default;

    private:
    char mac[SIZE_MAC + 1]; //11:00:5e:00:53:af
    char ap_ssid[MAX_SIZE_SSID + 1];
    char ap_pass[MAX_SIZE_PASS + 1];
    char sta_ssid[MAX_SIZE_SSID + 1];
    char sta_pass[MAX_SIZE_PASS + 1];
    // TODO: mode multiAP
    char connection_mode [MAX_SIZE_CONN_MODE + 1]; // 'STA'|'AP' 
    
    IpConfig ip_config;
    UsedGpio used_gpios[MAX_SIZE_USED_GPIOS];
    Gpio gpios[SIZE_GPIOS];

    public:
    const char* get_mac() const { return mac; }
    void set_mac(const char * value) { strcpy(this->mac, value);}

    const char * get_ap_ssid() { return ap_ssid; }
    void set_ap_ssid(const char * value) { strcpy(this->ap_ssid, value); }

    const char * get_ap_pass() { return ap_pass; }
    void set_ap_pass(const char * value) { strcpy(this->ap_pass, value); }

    const char * get_sta_ssid() { return sta_ssid; }
    void set_sta_ssid(const char * value) { strcpy(this->sta_ssid, value); }

    const char * get_sta_pass() { return sta_pass; }
    void set_sta_pass(const char * value) { strcpy(this->sta_pass, value); }

    const char* get_connection_mode() const { return connection_mode; }
    void set_connection_mode(const char* value) { strcpy(this->connection_mode, value);}

    const IpConfig & get_ip_config() const { return ip_config; }
    IpConfig & get_mutable_ip_config() { return ip_config; }
    void set_ip_config(const IpConfig & value) { this->ip_config = value; }
    
    UsedGpio* get_used_gpios() { return used_gpios;}
    
    void set_used_gpios(UsedGpio* value, uint8_t size) {
        if(size > MAX_SIZE_USED_GPIOS){
            Serial.printf("[SmartD][E]- UsedGpio array size is bigger than reserved");
            return;
        } 
        for(int i = 0; i < MAX_SIZE_USED_GPIOS; i++){
            this-> used_gpios[i] = value[i];
        }
    }

    Gpio* get_gpios() { return gpios; }
    void set_gpios(Gpio* value, uint8_t size) { 
        if(size > SIZE_GPIOS){
            Serial.printf("[SmartD][E]- Gpio array size is bigger than reserved");
            return;
        }
        for(int i = 0; i < SIZE_GPIOS; i++){
            this-> gpios[i] = value[i];
        }
    }

    // const std::vector<UsedGpio> & get_used_gpios() const { return used_gpios; }
    // std::vector<UsedGpio> & get_mutable_used_gpios() { return used_gpios; }
    // void set_used_gpios(const std::vector<UsedGpio> & value) { this->used_gpios = value; }

    // const std::vector<Gpio> & get_gpios() const { return gpios; }
    // std::vector<Gpio> & get_mutable_gpios() { return gpios; }
    // void set_gpios(const std::vector<Gpio> & value) { this->gpios = value; }
};
