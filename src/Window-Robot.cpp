#include <Arduino.h>

const int dirPin = D0;
const int stepPin = D1;

const int switchPin = D2;

void setup() {
  Serial.begin(9600);
  Serial.println("On");
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(switchPin, INPUT_PULLUP);
  digitalWrite(dirPin, 1);
}

void cycleMotor(){
  int count = 0;
  while(digitalRead(switchPin) == LOW && count < 100){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
    count++;
  }
}

void loop() {
  cycleMotor();
}
