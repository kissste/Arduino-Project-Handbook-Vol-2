// Reproduced with kind permission from Nick Koumaris
// http://www.educ8s.tv
#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>
#define TRIG_PIN A4
#define ECHO_PIN A5
#define MAX_DISTANCE 200
#define MAX_SPEED 190 // Sets speed of DC motors
#define MAX_SPEED_OFFSET 20
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);
AF_DCMotor motor1(1, MOTOR12_1KHZ); // First motor to connection 1
AF_DCMotor motor2(3, MOTOR12_1KHZ); // Second motor to connection 3
Servo myservo; // Give the servo a name
boolean goesForward = false;
int distance = 100; // Define an int for distance and speed
int speedSet = 0;
void setup() {
  myservo.attach(9); // Servo attached to pin 9
  myservo.write(115); // Set servo at 115 degrees
  delay(2000);
  distance = readPing(); // Read the distance from the sensor
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}
void loop() {
  int distanceR = 0;
  int distanceL = 0;
  delay(40);
  // If distance is less than 15 cm, carry out this function
  if (distance <= 15) {
    moveStop();
    delay(100);
    moveBackward();
    delay(300);
    moveStop();
    delay(200);
    distanceR = lookRight();
    delay(200);
    distanceL = lookLeft();
    delay(200);
    if (distanceR >= distanceL) {
      turnRight();
      moveStop();
    } else { // Or else carry on
      turnLeft();
      moveStop();
    }
  } else {
    moveForward();
  }
  distance = readPing();
}
int lookRight() { // The servo moves to the right
  myservo.write(50);
  delay(500);
  int distance = readPing();
  delay(100);
  myservo.write(115);
  return distance;
}
int lookLeft() { // The servo looks to the left
  myservo.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  myservo.write(115);
  return distance;
  delay(100);
}
int readPing() {
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0) {
    cm = 250;
  }
  return cm;
}
void moveStop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}
void moveForward() {
  if (!goesForward) { // If area is clear, motors move forward
    goesForward = true;
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    // Slowly bring up speed to avoid loading down
    // batteries too quickly
    for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) {
      motor1.setSpeed(speedSet);
      motor2.setSpeed(speedSet + MAX_SPEED_OFFSET);
      delay(5);
    }
  }
}
void moveBackward() {
  goesForward = false;
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  // Slowly bring up speed to avoid loading down
  // batteries too quickly
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet + MAX_SPEED_OFFSET);
    delay(5);
  }
}
void turnRight() { // Movement for turning right
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  delay(300);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
}
void turnLeft() { // Movement for turning left
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  delay(300);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
}

