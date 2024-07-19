#include <WiFi.h>
#include <WebServer.h>
#include "GDEP073E01.h"

// const char* ssid = "cs-103-obs";
// const char* password = "966AA1AC";

const char* ssid = "Lazarovich";
const char* password = "l1aza9ro9vic4h";

WebServer server(80);
GDEP073E01 epdDisplay;

unsigned char* encodedImage = nullptr;
int encodedImageLength = 0;

void handleRoot() {
    server.send(200, "text/plain", "ESP32 EPD Server");
}

void handleSetLength() {
    if (server.hasArg("plain") == false) {
        server.send(200, "text/plain", "Body not received");
        return;
    }

    String body = server.arg("plain");
    encodedImageLength = body.toInt();
    Serial.printf("Received length: %d\n", encodedImageLength);

    if (encodedImageLength <= 0) {
        server.send(400, "text/plain", "Invalid length");
        return;
    }

    if (encodedImage != nullptr) {
        free(encodedImage);
    }

    encodedImage = (unsigned char*)malloc(encodedImageLength);
    if (encodedImage == nullptr) {
        server.send(500, "text/plain", "Memory allocation failed");
        return;
    }

    server.send(200, "text/plain", "Length received");
}

void handleImageUpload() {
    if (server.hasArg("plain") == false) {
        server.send(200, "text/plain", "Body not received");
        return;
    }

    if (encodedImage == nullptr) {
        server.send(400, "text/plain", "Length not set");
        return;
    }

    String body = server.arg("plain");
    memcpy(encodedImage, body.c_str(), encodedImageLength);

    Serial.println("Image data received. Displaying image...");

    epdDisplay.init_fast();
    epdDisplay.display(encodedImage, encodedImageLength);
    epdDisplay.sleep();   

    free(encodedImage);
    encodedImage = nullptr;
    server.send(200, "text/plain", "Image received and displayed");
}

void setup() {
    //SPI
    SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0)); 
    SPI.begin ();

    //Serial
    Serial.begin(115200);
    delay(1000);

    //WiFi station mode
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("\nConnecting");

    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(100);
    }

    Serial.printf("\nConnected to the WiFi network %s\n", WiFi.SSID());
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());

    epdDisplay.init();
    epdDisplay.clear();

    server.on("/", HTTP_GET, handleRoot);
    server.on("/setLength", HTTP_POST, handleSetLength);
    server.on("/upload", HTTP_POST, handleImageUpload);

    server.begin();
    Serial.println("HTTP server started");
}

void loop() {
    server.handleClient();
}
