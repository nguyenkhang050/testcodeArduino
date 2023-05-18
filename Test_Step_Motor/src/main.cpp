#include <Arduino.h>
int tep = 54;
int dir = 55;
int ena = 38;

void setup() {
  // put your setup code here, to run once:
  pinMode(ena, OUTPUT);
  pinMode(tep, OUTPUT);
  pinMode(dir, OUTPUT);

  digitalWrite(ena, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(dir, LOW);
  for(int x = 0; x< 200; x++){
    digitalWrite(tep, HIGH);
    delayMicroseconds(1000);
    digitalWrite(tep, LOW);
    delayMicroseconds(1000);
  }
  delay(1000);
}