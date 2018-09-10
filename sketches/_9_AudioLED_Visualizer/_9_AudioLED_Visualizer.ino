// Used with kind permission from James Newbould
// http://robomaniac123.zxq.net
int led[9] = {2, 3, 4, 5, 6, 7, 8, 9, 10}; // Pins connected to LEDs
int leftChannel = A0; // Pin connected to headphone jack
int left, i; // Create a variable for left and i
void setup() {
  for (i = 0; i < 9; i++)
    pinMode(led[i], OUTPUT); // Set LEDs as output
}
void loop() { // Light LEDs from left to right and back again
  // depending on the value from A0
  left = analogRead(leftChannel); // Read left value
  left = left / 10; // Set level of sensitivity between 1 and 50
  if (left == 0) {
    for (i = 0; i < 9; i++) { // If value is low, turn off LED
      digitalWrite(led[i], LOW);
    }
  }
  else { // Or else turn on LEDs in sequence
    for (i = 0; i < left; i++) {
      digitalWrite(led[i], HIGH);
    }
    for (i = i; i < 9; i++) {
      digitalWrite(led[i], LOW);
    }
  }
}
