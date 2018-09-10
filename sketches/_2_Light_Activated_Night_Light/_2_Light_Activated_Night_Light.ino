int lightPin = A0; // Pin connected to the photoresistor
int ledPin = 13; // Pin connected to the LED
void setup() {
  Serial.begin(9600); // Begin serial communication
  pinMode(ledPin, OUTPUT); // Setting the LED pin as an output
}
// This loop reads the analog pin value and
// sends that to the LED as an output
void loop() {
  // Read the value of the photoresistor
  Serial.println(analogRead(lightPin));
  // Write the value to the Serial Monitor
  // Send the value to the ledPin and divide by 4
  analogWrite(ledPin, analogRead(lightPin) / 4);
  delay(10); // Short delay before the sequence loops again
}
