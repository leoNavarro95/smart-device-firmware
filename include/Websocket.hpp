#include<ArduinoJson.h>

#include "SmartDevice_Model.hpp"
#include "Server.hpp"
#include "API.hpp"

AsyncWebSocket ws("/ws");


class WebSocket;
static WebSocket *globalPtr; // TODO: mala practica (solo es posible una sola instancia de la clase lo cual de momento no es problema), uso puntero global para acceder al this dentro del callback onWsEvent

class WebSocket {
	public: 
	WebSocket() = default;
	virtual ~WebSocket() = default;

	private: 
	SmartDevice _sdevice;

	void ProcessRequest(AsyncWebSocketClient *client, String request)
	{
		StaticJsonDocument<300> doc;
		DeserializationError error = deserializeJson(doc, request);
		if (error) { 
			log_d("Deserialize Json error: %s", error.c_str());
			return; 
		}
		
		String command = doc["command"];
		if(command == "setGPIO") 
			setGPIO(doc["id"], (bool)doc["status"]);
		else if(command == "setPWM")
			setPWM(doc["id"], (int)doc["pwm"]);
		else if(command == "doAction")
			doAction(doc["id"]);
		else if(command == "updateWifi")
			setWifi( this->_sdevice, doc["mode"], doc["ssid"], doc["pass"] );
	}

	static void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
	{

		if (type == WS_EVT_CONNECT) {
			log_d("ws[%s][%u] connect", server->url(), client->id());
			client->printf("{\"message\": \"Hello Client %u\"}", client->id());
			client->ping();
		}
		else if (type == WS_EVT_DISCONNECT) {
			log_d("ws[%s][%u] disconnect: %u\n", server->url(), client->id());
		}
		else if (type == WS_EVT_ERROR) {
			log_d("ws[%s][%u] error(%u): %s\n", server->url(), client->id(), *((uint16_t *)arg), (char *)data);
		}
		else if (type == WS_EVT_PONG) {
			log_d("ws[%s][%u] pong[%u]: %s\n", server->url(), client->id(), len, (len) ? (char *)data : "");
		}
		else if (type == WS_EVT_DATA) {
			AwsFrameInfo *info = (AwsFrameInfo *)arg;
			String msg = ""; // TODO char msg[info->len]
			if (info->final && info->index == 0 && info->len == len) {
				if (info->opcode == WS_TEXT) {
					for (size_t i = 0; i < info->len; i++)
						msg += (char)data[i];
				}
				else {
					char buff[3];
					for (size_t i = 0; i < info->len; i++) {
						sprintf(buff, "%02x ", (uint8_t)data[i]);
						msg += buff;
					}
				}

				if (info->opcode == WS_TEXT)
					globalPtr -> ProcessRequest(client, msg);
			}
			else {
				// message is comprised of multiple frames or the frame is split into multiple packets
				if (info->opcode == WS_TEXT) {
					for (size_t i = 0; i < len; i++)
						msg += (char)data[i];
				} 
				else {
					char buff[3];
					for (size_t i = 0; i < len; i++) {
						sprintf(buff, "%02x ", (uint8_t)data[i]);
						msg += buff;
					}
				}
				log_d("%s\n", msg.c_str());

				if ((info->index + len) == info->len) {
					if (info->final) {
						if (info->message_opcode == WS_TEXT)
							globalPtr -> ProcessRequest(client, msg);
					}
				}
			}
		}
	}

	public:
	
	void init( SmartDevice &sDevice ){
		globalPtr = this;
		
		this->_sdevice = sDevice;

		ws.onEvent( this -> onWsEvent );
		server.addHandler( &ws );
		log_d("WebSocket server started");
	}

	void updateGPIO(String input, bool value)
	{
		String response;
		StaticJsonDocument<300> doc;
		doc["command"] = "updateGPIO";
		doc["id"] = input;
		doc["status"] = value;
		serializeJson(doc, response);

		ws.textAll(response);

		Serial.print(input);
		Serial.println(value ? String(" ON") : String(" OFF"));
	}
};






// void sendStatus(){

// }




