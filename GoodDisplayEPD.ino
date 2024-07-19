#include <WiFi.h>
#include <WebServer.h>
#include "GDEP073E01.h"

// const char* ssid = "cs-103-obs";
// const char* password = "966AA1AC";

const char* ssid = "Lazarovich";
const char* password = "l1aza9ro9vic4h";

WebServer server(80);
GDEP073E01 epdDisplay;

unsigned char* image = nullptr;
int imageSize = 0;
int chunkSize = 0;
int receivedBytes = 0;

void handleRoot() {
    server.send(200, "text/plain", "ESP32 EPD Server");
}

void handleSetImageSize() {
    if (server.hasArg("plain") == false) {
        server.send(200, "text/plain", "Body not received");
        return;
    }

    String body = server.arg("plain");
    imageSize = body.toInt();
    Serial.printf("Received image size: %d\n", imageSize);

    if (imageSize <= 0) {
        server.send(400, "text/plain", "Invalid image size");
        return;
    }

    if (image != nullptr) {
        free(image);
    }

    image = (unsigned char*)malloc(imageSize);
    if (image == nullptr) {
        server.send(500, "text/plain", "Memory allocation failed");
        return;
    }

    server.send(200, "text/plain", "Image size received");
}

void handleSetChunkSize() {
    if (server.hasArg("plain") == false) {
        server.send(200, "text/plain", "Body not received");
        return;
    }

    String body = server.arg("plain");
    chunkSize = body.toInt();
    Serial.printf("Received chunk size: %d\n", chunkSize);

    if (chunkSize <= 0) {
        server.send(400, "text/plain", "Invalid chunk size");
        return;
    }

    server.send(200, "text/plain", "Chunk size received");
}

void handleImageUpload() {
    if (server.hasArg("plain") == false) {
        server.send(200, "text/plain", "Body not received");
        return;
    }

    if (image == nullptr) {
        server.send(400, "text/plain", "Image size not set");
        return;
    }

    if (chunkSize == 0) {
        server.send(400, "text/plain", "Chunk size not set");
        return;
    }

    String body = server.arg("plain");
    size_t bodyLength = body.length();

    if (bodyLength < chunkSize && receivedBytes + bodyLength < imageSize) {
        server.send(400, "text/plain", "Resend chunk");
        return;
    }
    if (receivedBytes + bodyLength > imageSize) {
        server.send(400, "text/plain", "Too much data");
        return;
    }

    memcpy(image + receivedBytes, body.c_str(), bodyLength);
    receivedBytes += bodyLength;

    if (receivedBytes < imageSize) {
        server.send(200, "text/plain", "Chunk received");
        return;
    }

    Serial.println("Image data received. Displaying image...");

    epdDisplay.init_fast();
    epdDisplay.display(image, imageSize);
    epdDisplay.sleep();   

    free(image);
    image = nullptr;
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

    Serial.println("Clearing Display");
    epdDisplay.init();
    epdDisplay.clear();
    epdDisplay.sleep();
    Serial.println("Cleared Display");

    server.on("/", HTTP_GET, handleRoot);
    server.on("/setSize", HTTP_POST, handleSetImageSize);
    server.on("/setChunk", HTTP_POST, handleSetChunkSize);
    server.on("/upload", HTTP_POST, handleImageUpload);

    server.begin();
    Serial.println("HTTP server started");
}

void loop() {
    server.handleClient();
}
