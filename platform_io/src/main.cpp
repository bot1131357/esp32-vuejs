#include <Arduino.h>

#include <FS.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include "utility.h"

AsyncWebServer server(80);

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

void notFound(AsyncWebServerRequest *request) {
	request->send(404, "text/plain", "Not found");
}

void setup() {

	Serial.begin(250000);
	delay(10);

	if (!SPIFFS.begin())
	{
		sdprintln("SPIFFS failed to start.");
		while (1) {}
	}
	sdprintln("SPIFFS initialization ok!)",5);

	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);
	if (WiFi.waitForConnectResult() != WL_CONNECTED) {
		sdprintfln("WiFi Failed!");
		return;
	}

	sdprintfln("IP address: %s", WiFi.localIP().toString().c_str());
	sdprintfln("Gateway address: %s", WiFi.gatewayIP().toString().c_str());

	server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
		// request->send(200, "text/plain", "Hello, world");
		request->send(SPIFFS, "/index.html");
	});
	// use this if you're using gzip bundle
	server.on("/index.min.js", HTTP_GET, [](AsyncWebServerRequest *request) {
		// request->send(200, "text/plain", "Hello, world");
		
		AsyncWebServerResponse *response = request->beginResponse(SPIFFS, "/index.min.js.gz", "text/javascript");
		response->addHeader("Content-Encoding", "gzip");
		request->send(response);
	});

	// assets
	// 1. need to rename to 32 char
	// 2. remove references to /assets, since SPIFFS is a flat file system
	server.serveStatic("/", SPIFFS, "/");


	server.onNotFound(notFound);

	server.begin();
}

void loop() {
}