#include <NewPing.h> // This calls the NewPing library
#define trigPin 12 // Trig pin attached to Arduino 12
#define echoPin 13 // Echo pin attached to Arduino 13
#define soakerPin 3
#define MAX_DISTANCE 500

NewPing sonar(trigPin, echoPin, MAX_DISTANCE);

void setup() {
  Serial.begin(9600);
  pinMode(soakerPin, OUTPUT);
}
void loop() {
  int distance;
  distance = sonar.ping_cm();
  Serial.print(distance);
  Serial.println(" cm");
  if (distance <= 15) { // If distance is less than 15
    digitalWrite(soakerPin, HIGH); // Soaker shoots water
    delay(250);
    digitalWrite(soakerPin, LOW); // Short pulse of water
  }
  else {
    digitalWrite(soakerPin, LOW); // Soaker will remain off
  }
  delay(500);
}
