#include <Arduino.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const int dirPin = D0;
const int stepPin = D1;
const int switchPin = D2;

const char* ssid = "Window-Control";
const char* password = "password";

ESP8266WebServer server(80);

void motorControl(){
  for(int i=0; i<10000; i++){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  }
}

void handleRoot(){
  server.send(200, "text/html", "<a href=\"/cycle\"><Button>Stepper ON</Button></a>");
}

void cycleStepper(){
  server.send(200, "text/html", "<a href=\"/cycle\"><Button>Stepper ON</Button></a>");
  motorControl();
}

void setup() {
  WiFi.softAP(ssid, password);
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(switchPin, INPUT_PULLUP);
  digitalWrite(dirPin, 1);
  server.on("/", handleRoot);
  server.on("/cycle", cycleStepper);
  server.begin();
}

void loop() {
  server.handleClient();
}
