#include <Arduino.h>
#include <Servo.h>

Servo myservo;

int pos = 0;    // variable to store the servo position
int potValue;

void setup() {
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the Servo object
}

void loop() {
  potValue = analogRead(A0);
  potValue = map(potValue, 0, 1023, 0, 1023);
  myservo.writeMicroseconds(potValue);
  Serial.println(potValue);
  delay(15);
}