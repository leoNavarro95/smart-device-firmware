void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){ 
	if(type == WS_EVT_CONNECT){
		log_d("ws[%s][%u] connect", server->url(), client->id());
		client->printf("{\"message\": \"Hello Client %u\"}", client->id());
		//enviar trama con todos los datos
		
		client->ping();
	} else if(type == WS_EVT_DISCONNECT){
		log_d("ws[%s][%u] disconnect: %u\n", server->url(), client->id());
	} else if(type == WS_EVT_ERROR){
		log_d("ws[%s][%u] error(%u): %s\n", server->url(), client->id(), *((uint16_t*)arg), (char*)data);
	} else if(type == WS_EVT_PONG){
		log_d("ws[%s][%u] pong[%u]: %s\n", server->url(), client->id(), len, (len)?(char*)data:"");
	} else if(type == WS_EVT_DATA){
		AwsFrameInfo * info = (AwsFrameInfo*)arg;
		String msg = "";
		if(info->final && info->index == 0 && info->len == len){
			if(info->opcode == WS_TEXT){
				for(size_t i=0; i < info->len; i++) {
					msg += (char) data[i];
				}
			} else {
				char buff[3];
				for(size_t i=0; i < info->len; i++) {
					sprintf(buff, "%02x ", (uint8_t) data[i]);
					msg += buff ;
				}
			}

			if(info->opcode == WS_TEXT)
			ProcessRequest(client, msg);
			
		} else {
			//message is comprised of multiple frames or the frame is split into multiple packets
			if(info->opcode == WS_TEXT){
				for(size_t i=0; i < len; i++) {
					msg += (char) data[i];
				}
			} else {
				char buff[3];
				for(size_t i=0; i < len; i++) {
					sprintf(buff, "%02x ", (uint8_t) data[i]);
					msg += buff ;
				}
			}
			log_d("%s\n",msg.c_str());

			if((info->index + len) == info->len){
				if(info->final){
					if(info->message_opcode == WS_TEXT)
					ProcessRequest(client, msg);
				}
			}
		}
	}
}

void InitWebSockets()
{
	ws.onEvent(onWsEvent);
	server.addHandler(&ws);
	Serial.println("WebSocket server started");
}

