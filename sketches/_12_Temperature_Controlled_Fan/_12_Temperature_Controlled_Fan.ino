#define SENS_PIN A0 // Defines A0 pin as "sensor"
#define FAN_PIN 5
int Vin; // Reads value from Arduino pin
float Temperature; // Receives converted voltage value to temp
float TF; // Receives converted value in °F
void setup() {
  pinMode(FAN_PIN, OUTPUT); // Fan pin as an output
  Serial.begin(9600); // Start Serial Monitor
}
void loop() {
  Vin = analogRead (SENS_PIN); // Tells Arduino to read pin
  // and stores value in Vin
  Temperature = (500 * Vin) / 1023 * (1.8) + 32; // Converts voltage value
  // into temperature
  // and stores value in
  // Temperature (as °F)
  TF = Temperature;
  Serial.print("Temperature: "); // Sends text to display screen
  Serial.print(TF); // Shows value of temperature in Serial Monitor
  Serial.println(" F"); // Writes F to indicate it is in Fahrenheit
  if (TF > 71) { // If temperature is more than 71
    digitalWrite(FAN_PIN, HIGH); // Turn fan on
  }
  else if (TF < 71) {
    digitalWrite(FAN_PIN, LOW); // Or keep fan off
  }
  delay(1000); // Waits for a second to read the pin again
}
