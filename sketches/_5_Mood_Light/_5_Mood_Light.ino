int redPin = 11; // pin connected to red leg of the RGB LED
int greenPin = 10; // pin connected to green leg of the RGB LED
int bluePin = 9; // pin connected to blue leg of the RGB LED
void setup() {
setRgb(0,0,0); // Set all colors at 0
}
void loop() {
int Rgb[3]; // 3 RGB pins
Rgb[0] = 0; // A value for each
Rgb[1] = 0;
Rgb[2] = 0;
for (int decrease = 0; decrease < 3; decrease += 1) { // colors increase and decrease in value
int increase = decrease == 2 ? 0 : decrease + 1;
for(int i = 0; i < 255; i += 1) { // Fade the colors
Rgb[decrease] -= 1;
Rgb[increase] += 1;
setRgb(Rgb[0], Rgb[1], Rgb[2]);
delay(20);
}
}
}
void setRgb( int red, int green, int blue) {
analogWrite(redPin, red);
analogWrite(greenPin, green);
analogWrite(bluePin, blue);
}
