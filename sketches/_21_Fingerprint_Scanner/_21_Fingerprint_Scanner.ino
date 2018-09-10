#include <Servo.h>
#include <Adafruit_Fingerprint.h>
#if ARDUINO >= 100
#include <SoftwareSerial.h>
#else
#include <NewSoftSerial.h>
#endif
int getFingerprintIDez();
int ledaccess = 7; // Green LED pin
int leddeny = 8; // Red LED pin
int servoPin = 9; // Servo pin
Servo doorLock;
// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino (WHITE wire)
#if ARDUINO >= 100
SoftwareSerial mySerial(2, 3); // Ppins for the fingerprint sensor
#else
NewSoftSerial mySerial(2, 3);
#endif
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
void setup() {
  doorLock.attach(servoPin); // We define the servo pin
  pinMode(ledaccess, OUTPUT); // Green LED pin set as an ouput
  pinMode(leddeny, OUTPUT); // Red LED pin set as an output
  pinMode(servoPin, OUTPUT); // Servo pin set as an output
  Serial.begin(9600); // Start sending messages to the Serial Monitor
  Serial.println("fingertest");
  finger.begin(57600); // Set data rate for the sensor serial port
  // Start the module and checking for fingerprint
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1);
  }
  Serial.println("Waiting for valid finger...");
}
void loop() {
  int ID = getFingerprintIDez(); //Get the fingerprint ID#
  // Reset the device to the test state
  digitalWrite(ledaccess, HIGH);
  digitalWrite(leddeny, HIGH);
  doorLock.write(0);
  if (ID >= 0) { // Valid ID. Unlocked state
    // Enable the access LED, turn off the deny LED
    digitalWrite(ledaccess, HIGH);
    digitalWrite(leddeny, LOW);
    // Unlock the servo
    doorLock.write(180);
  }
  else if (ID == -3) { // ID doesn't match any registed print
    // Locked state
    // Enable the deny LED, turn off the access LED
    digitalWrite(ledaccess, LOW);
    digitalWrite(leddeny, HIGH);
  }
  delay(5000);
}
uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK: // Sensor takes a photo when a finger is
      // placed on the module window
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  p = finger.image2Tz(); // OK success! We have a fingerprint and
  // now check that it can be read
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  p = finger.fingerFastSearch(); // OK converted! It's valid, so
  // check it against module memory
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match"); // No match found,
    // back to the start
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }
  // We found a match! So the following will run:
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID;
}
// Returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  int p = finger.getImage();
  if (p != FINGERPRINT_OK) return -1;
  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) return -2;
  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK) ; {
    Serial.println("No match found");
    return -3;
  }
  // Found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID;
}
