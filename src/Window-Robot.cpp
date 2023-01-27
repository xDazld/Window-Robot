#include <Arduino.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "index.h"

const int dirPin = D0;
const int stepPin = D8;

const char* ssid = "VTOW-Res308-2.4ghz";
const char* password = "relentless49rpc45";

const String root = Main_Page;

ESP8266WebServer server(80);

void motorControl(int steps, int speed, boolean direction){
  digitalWrite(dirPin, direction);
  for(int i = 0; i<steps; i++){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(speed);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(speed);
    yield();
  }
}

void handleRoot(){
  server.send(200, "text/html", root);
}

void stepperON(){
  server.send(200, "text/html", root);
  motorControl(20000, 1000, HIGH);
}

void stepperOFF(){
  server.send(200, "text/html", root);
  motorControl(20000, 1000, LOW);
}

void setup() {
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  digitalWrite(dirPin, 1);
  server.on("/", handleRoot);
  server.on("/stepperON", stepperON);
  server.on("/stepperOFF", stepperOFF);

  MDNS.begin("windowcontrol", WiFi.localIP());

  server.begin();

  MDNS.addService("http", "tcp", 80);
}

void loop() {
  server.handleClient();
  MDNS.update();
}
