/* Created by David Cuartielles modified 30 Aug 2011 by Tom Igoe
This example code is in the public domain http://arduino.cc/en/
Tutorial/AnalogInput */
#include <Servo.h> // Call the Servo library (built into the IDE)
Servo myservo;
int pos = 0; // Give the position a value
int lightPin = A0; // Pin connected to the photoresistor
void setup() {
  myservo.attach(9); // Pin connected to the servo
}
void loop() {
  // Read voltage from photoresistor, can read 1024 possible values
  int lightLevel = analogRead(lightPin);
  // Scale 1024 values to 180
  lightLevel = map(lightLevel, 0, 1023, 0, 179);
  // Scale of 0-179 (180 values)
  pos = constrain(lightLevel, 0, 179);
  myservo.write(pos); // Set the servo angle
  delay(100);
}
