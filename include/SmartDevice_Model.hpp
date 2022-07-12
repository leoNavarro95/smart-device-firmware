#pragma once

#include <optional>
#include <stdexcept>
#include <regex>

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
    const char* mode;
    const char* label;
    const char* value;

    public:
    const uint8_t & get_id() const { return id; }
    uint8_t & get_mutable_id() { return id; }
    void set_id(const uint8_t & value) { this->id = value; }

    const uint8_t & get_pin_number() const { return pin_number; }
    uint8_t & get_mutable_pin_number() { return pin_number; }
    void set_pin_number(const uint8_t & value) { this->pin_number = value; }

    const char * get_mode() { return mode; }
    void set_mode(const char * value) { this->mode = value; }

    const char * get_label() { return label; }
    void set_label(const char * value) { this->label = value; }

    const char * get_value() { return value; }
    void set_value(const char * value) { this->value = value; }
};

class SmartDevice {
    public:
    SmartDevice() = default;
    virtual ~SmartDevice() = default;

    private:
    char mac[18]; //11:00:5e:00:53:af
    const char * ap_ssid;
    const char * ap_pass;
    const char * sta_ssid;
    const char * sta_pass;
    // TODO: mode multiAP
    char connection_mode [5]; // 'STA'|'AP' 
    
    IpConfig ip_config;
    UsedGpio * used_gpios;
    Gpio * gpios;

    public:
    // char* get_mutable_mac() { return mac; }
    const char* get_mac() const { return mac; }
    void set_mac(const char* value) { strcpy(this->mac, value);}

    const char * get_ap_ssid() { return ap_ssid; }
    void set_ap_ssid(const char * value) { this->ap_ssid = value; }

    const char * get_ap_pass() { return ap_pass; }
    void set_ap_pass(const char * value) { this->ap_pass = value; }

    const char * get_sta_ssid() { return sta_ssid; }
    void set_sta_ssid(const char * value) { this->sta_ssid = value; }

    const char * get_sta_pass() { return sta_pass; }
    void set_sta_pass(const char * value) { this->sta_pass = value; }

    const char* get_connection_mode() const { return connection_mode; }
    void set_connection_mode(const char* value) { strcpy(this->connection_mode, value);}

    const IpConfig & get_ip_config() const { return ip_config; }
    IpConfig & get_mutable_ip_config() { return ip_config; }
    void set_ip_config(const IpConfig & value) { this->ip_config = value; }
    
    UsedGpio* get_used_gpios() { return used_gpios;}
    void set_used_gpios(UsedGpio* value) { this-> used_gpios = value;}

    Gpio* get_gpios() { return gpios; }
    void set_gpios(Gpio* value) { this-> gpios = value; }

    // const std::vector<UsedGpio> & get_used_gpios() const { return used_gpios; }
    // std::vector<UsedGpio> & get_mutable_used_gpios() { return used_gpios; }
    // void set_used_gpios(const std::vector<UsedGpio> & value) { this->used_gpios = value; }

    // const std::vector<Gpio> & get_gpios() const { return gpios; }
    // std::vector<Gpio> & get_mutable_gpios() { return gpios; }
    // void set_gpios(const std::vector<Gpio> & value) { this->gpios = value; }
};
