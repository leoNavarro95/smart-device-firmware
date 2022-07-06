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
    std::string mode;
    std::string ip_address;
    std::string subred_mask_address;
    std::string gateway_address;

    public:
    const std::string & get_mode() const { return mode; }
    std::string & get_mutable_mode() { return mode; }
    void set_mode(const std::string & value) { this->mode = value; }

    const std::string & get_ip_address() const { return ip_address; }
    std::string & get_mutable_ip_address() { return ip_address; }
    void set_ip_address(const std::string & value) { this->ip_address = value; }

    const std::string & get_subred_mask_address() const { return subred_mask_address; }
    std::string & get_mutable_subred_mask_address() { return subred_mask_address; }
    void set_subred_mask_address(const std::string & value) { this->subred_mask_address = value; }

    const std::string & get_gateway_address() const { return gateway_address; }
    std::string & get_mutable_gateway_address() { return gateway_address; }
    void set_gateway_address(const std::string & value) { this->gateway_address = value; }
};

class UsedGpio {
    public:
    UsedGpio() = default;
    virtual ~UsedGpio() = default;

    private:
    uint8_t id;
    uint8_t pin_number;
    std::string mode;
    std::string label;
    std::string value;

    public:
    const uint8_t & get_id() const { return id; }
    uint8_t & get_mutable_id() { return id; }
    void set_id(const uint8_t & value) { this->id = value; }

    const uint8_t & get_pin_number() const { return pin_number; }
    uint8_t & get_mutable_pin_number() { return pin_number; }
    void set_pin_number(const uint8_t & value) { this->pin_number = value; }

    const std::string & get_mode() const { return mode; }
    std::string & get_mutable_mode() { return mode; }
    void set_mode(const std::string & value) { this->mode = value; }

    const std::string & get_label() const { return label; }
    std::string & get_mutable_label() { return label; }
    void set_label(const std::string & value) { this->label = value; }

    const std::string & get_value() const { return value; }
    std::string & get_mutable_value() { return value; }
    void set_value(const std::string & value) { this->value = value; }
};

class SmartDevice {
    public:
    SmartDevice() = default;
    virtual ~SmartDevice() = default;

    private:
    std::string mac;
    std::string ap_ssid;
    std::string ap_pass;
    std::string sta_ssid;
    std::string sta_pass;
    std::string connection_mode;
    IpConfig ip_config;
    std::vector<UsedGpio> used_gpios;
    std::vector<Gpio> gpios;

    public:
    const std::string & get_mac() const { return mac; }
    std::string & get_mutable_mac() { return mac; }
    void set_mac(const std::string & value) { this->mac = value; }

    const std::string & get_ap_ssid() const { return ap_ssid; }
    std::string & get_mutable_ap_ssid() { return ap_ssid; }
    void set_ap_ssid(const std::string & value) { this->ap_ssid = value; }

    const std::string & get_ap_pass() const { return ap_pass; }
    std::string & get_mutable_ap_pass() { return ap_pass; }
    void set_ap_pass(const std::string & value) { this->ap_pass = value; }

    const std::string & get_sta_ssid() const { return sta_ssid; }
    std::string & get_mutable_sta_ssid() { return sta_ssid; }
    void set_sta_ssid(const std::string & value) { this->sta_ssid = value; }

    const std::string & get_sta_pass() const { return sta_pass; }
    std::string & get_mutable_sta_pass() { return sta_pass; }
    void set_sta_pass(const std::string & value) { this->sta_pass = value; }

    const std::string & get_connection_mode() const { return connection_mode; }
    std::string & get_mutable_connection_mode() { return connection_mode; }
    void set_connection_mode(const std::string & value) { this->connection_mode = value; }

    const IpConfig & get_ip_config() const { return ip_config; }
    IpConfig & get_mutable_ip_config() { return ip_config; }
    void set_ip_config(const IpConfig & value) { this->ip_config = value; }

    const std::vector<UsedGpio> & get_used_gpios() const { return used_gpios; }
    std::vector<UsedGpio> & get_mutable_used_gpios() { return used_gpios; }
    void set_used_gpios(const std::vector<UsedGpio> & value) { this->used_gpios = value; }

    const std::vector<Gpio> & get_gpios() const { return gpios; }
    std::vector<Gpio> & get_mutable_gpios() { return gpios; }
    void set_gpios(const std::vector<Gpio> & value) { this->gpios = value; }
};
