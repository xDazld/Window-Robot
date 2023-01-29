#include <Arduino.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <LittleFS.h>
#include "wifi.h"

const int dirPin = D0;
const int stepPin = D8;

ESP8266WebServer server(80);

void motorControl(int steps, int speed, boolean direction) {
    digitalWrite(dirPin, direction);
    for (int i = 0; i < steps; i++) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(speed);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(speed);
        yield();
    }
}

void handleRoot() {
    File index = LittleFS.open("index.html", "r");
    server.send(200, "text/html", index.readString());
    index.close();
}

void handleStyles() {
    File styles = LittleFS.open("assets/css/styles.min.css", "r");
    server.send(200, "text/css", styles.readString());
    styles.close();
}

void handleManifest() {
    File manifest = LittleFS.open("manifest.json", "r");
    server.send(200, "text/json", manifest.readString());
    manifest.close();
}

void handleBsInit() {
    File bsInit = LittleFS.open("assets/js/bs-init.js", "r");
    server.send(200, "text/javascript", bsInit.readString());
    bsInit.close();
}

void stepperON() {
    File index = LittleFS.open("index.html", "r");
    server.send(200, "text/html", index.readString());
    index.close();
    motorControl(20000, 1000, HIGH);
}

void stepperOFF() {
    File index = LittleFS.open("index.html", "r");
    server.send(200, "text/html", index.readString());
    index.close();
    motorControl(20000, 1000, LOW);
}

void setup() {
    WiFi.begin(Ssid, Password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
    pinMode(dirPin, OUTPUT);
    pinMode(stepPin, OUTPUT);
    digitalWrite(dirPin, 1);
    server.on("/", handleRoot);
    server.on("/cycleWind", stepperON);
    server.on("/cycleUnwind", stepperOFF);
    server.on("/assets/css/styles.min.css", handleStyles);
    server.on("manifest.json", handleManifest);
    server.on("assets/js/bs-init.js", handleBsInit);

    MDNS.begin("windowcontrol", WiFi.localIP());

    LittleFS.begin();

    server.begin();

    MDNS.addService("http", "tcp", 80);
}

void loop() {
    server.handleClient();
    MDNS.update();
}
