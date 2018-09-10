int speakerPin = 13; // Piezo defined as pin 13
int key_c = 2; // Define Arduino pins for the keys
int key_d = 3;
int key_e = 4;
int key_f = 5;
int key_g = 6;
int key_a = 7;
int key_b = 8;
int key_C= 9;
// Value for each key press
int keypress_c = 0; int keypress_d = 0; int keypress_e = 0;
int keypress_f = 0; int keypress_g = 0; int keypress_a = 0;
int keypress_b = 0; int keypress_C = 0;
// Define the frequency of each note
int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
// 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C'
int keytone = 0; // Give a value for keytone
void setup() {
pinMode(key_c, INPUT); // Set up key pins as inputs
pinMode(key_d, INPUT);
pinMode(key_e, INPUT);
pinMode(key_f, INPUT);
pinMode(key_g, INPUT);
pinMode(key_a, INPUT);
pinMode(key_b, INPUT);
pinMode(key_C, INPUT);
pinMode(speakerPin, OUTPUT); // Set up piezo pin as an output
}
// Start a loop to read the press of each key
void loop() {
keypress_c = digitalRead(key_c); keypress_d = digitalRead(key_d);
keypress_e = digitalRead(key_e); keypress_f = digitalRead(key_f);
keypress_g = digitalRead(key_g); keypress_a = digitalRead(key_a);
keypress_b = digitalRead(key_b); keypress_C = digitalRead(key_C);
// And if the key press is HIGH, play the corresponding tone
if((keypress_c == HIGH) || (keypress_e == HIGH) ||
(keypress_g == HIGH) || (keypress_d == HIGH) ||
(keypress_f == HIGH) || (keypress_a == HIGH) ||
(keypress_b == HIGH) || (keypress_C == HIGH))
{
if (keypress_c == HIGH) {
keytone = tones[0];
}
if (keypress_d == HIGH) {
keytone = tones[1];
}
if (keypress_e == HIGH) {
keytone = tones[2];
}
if (keypress_f == HIGH) {
keytone = tones[3];
}
if (keypress_g == HIGH) {
keytone = tones[4];
}
if (keypress_a == HIGH) {
keytone = tones[5];
}
if (keypress_b == HIGH) {
keytone = tones[6];
}
if (keypress_C == HIGH) {
keytone = tones[7];
}
digitalWrite(speakerPin, HIGH); // Turn on piezo to play tone
delayMicroseconds(keytone);
digitalWrite(speakerPin, LOW); // Turn off after a short delay
delayMicroseconds(keytone);
}
else { // If no key is pressed, piezo remains silent
digitalWrite(speakerPin, LOW);
}
}
