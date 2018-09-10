// Arduino seven-segment display example software
// http://hacktronics.com/Tutorials/arduino-and-7-segment-led.html
// License: http://www.opensource.org/licenses/mit-license.php
// Define the LEDs to be lit to create a number
byte seven_seg_digits[10][7] = { { 1,1,1,1,1,1,0 }, // = 0
{ 0,1,1,0,0,0,0 }, // = 1
{ 1,1,0,1,1,0,1 }, // = 2
{ 1,1,1,1,0,0,1 }, // = 3
{ 0,1,1,0,0,1,1 }, // = 4
{ 1,0,1,1,0,1,1 }, // = 5
{ 1,0,1,1,1,1,1 }, // = 6
{ 1,1,1,0,0,0,0 }, // = 7
{ 1,1,1,1,1,1,1 }, // = 8
{ 1,1,1,0,0,1,1 } // = 9
};
// Set the seven-segment LED pins as output
void setup() {
pinMode(2, OUTPUT);
pinMode(3, OUTPUT);
pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
pinMode(6, OUTPUT);
pinMode(7, OUTPUT);
pinMode(8, OUTPUT);
pinMode(9, OUTPUT);
writeDot(0); // Start with the decimal point off
}
void writeDot(byte dot) {
digitalWrite(9, dot);
}
void sevenSegWrite(byte digit) {
byte pin = 2;
for(byte segCount = 0; segCount < 7; ++segCount) {
digitalWrite(pin, seven_seg_digits[digit][segCount]);
++pin;
}
}
void loop() {
for(byte count = 10; count > 0; --count) { // Start the countdown
delay(1000); // 1 second between each digit
sevenSegWrite(count - 1); // Counting down by 1
}
delay(4000);
}
