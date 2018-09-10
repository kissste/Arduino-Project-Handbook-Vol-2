char data = 0; // Create a variable for data
void setup() {
  Serial.begin(9600); // Data rate for serial communication
  pinMode(9, OUTPUT); // Set pin 9 as an output
}
void loop() {
  if (Serial.available() > 0) { // Send data
    data = Serial.read(); // Read incoming data and
    // store it into variable data
    Serial.print(data); // Print data value to the Serial Monitor
    Serial.print("\n"); // Start a new line
    if (data == '1') // If value is 1, turn on LED
      digitalWrite(9, HIGH);
    else if (data == '0') // If value is 0, turn off LED
      digitalWrite(9, LOW);
  }
}
