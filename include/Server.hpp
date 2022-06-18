AsyncWebServer server(80);

void InitServer()
{ 
	server.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");

	server.onNotFound([](AsyncWebServerRequest *request) {
		request->send(400, "text/plain", "Not found");
	});

	server.begin();
	Serial.println("HTTP server started");
}
