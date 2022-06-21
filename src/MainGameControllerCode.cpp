#include <Arduino.h>
#include <Keyboard.h>
#include <Mouse.h>

//ctrl alt  s to open serial monitor in vscode
// Joystick 1:
const int VRx1 = A0; // Connect to Analog Pin 0
const int VRy1 = A1; // Connect to Analog Pin 1


// Joystick 2:
const int VRx2 = A2; // Connect to Analog Pin 2
const int VRy2 = A3; // Connect to Analog Pin 3

const int xAxis = A0;         // joystick X axis
const int yAxis = A1;         // joystick Y axis
// parameters for reading the joystick:
int range = 12;               // output range of X or Y movement
int responseDelay = 5;        // response delay of the mouse, in ms
int threshold = range / 4;    // resting threshold
int center = range / 2;       // resting position value

bool mouseIsActive = true;    // whether or not to control the mouse


/*
  reads an axis (0 or 1 for x or y) and scales the analog input range to a range
  from 0 to <range>
*/



void Joy1() {
  // Joystick 1:
  if ((analogRead(VRy1) >= 900) && (analogRead(VRx1)) >= 0) {
    Serial.println("w_1");
    Keyboard.press(KEY_UP_ARROW);
    delay(25);
    Keyboard.releaseAll();
  }

  else if ((analogRead(VRy1)) <= 10 && (analogRead(VRx1)) >= 0) {
    Serial.println("s_1");
    Keyboard.press(KEY_DOWN_ARROW);
    delay(25);
    Keyboard.releaseAll();
    

  }

  else if ((analogRead(VRy1)) >= 350 && (analogRead(VRy1)) <= 900 && (analogRead(VRx1)) <= 300) {
    Serial.println("d_1");
    Keyboard.press(KEY_RIGHT_ARROW);
    delay(25);
    Keyboard.releaseAll();

  }

  else if ((analogRead(VRy1)) >= 50 && (analogRead(VRy1)) <= 650 && (analogRead(VRx1)) >= 600) {
    Serial.println("a_1");
    Keyboard.press(KEY_LEFT_ARROW);
    delay(25);
    Keyboard.releaseAll();
  }

}

int readAxis(int thisAxis) {
  // read the analog input:
  int reading = analogRead(thisAxis);

  // map the reading from the analog input range to the output range:
  reading = map(reading, 0, 1023, 0, range);

  // if the output reading is outside from the rest position threshold, use it:
  int distance = reading - center;

  if (abs(distance) < threshold) {
    distance = 0;
  }

  // return the distance for this axis:
  return distance;
}

void Joy2() {
    // read and scale the two axes:
  int xReading = readAxis(A2);
  int yReading = readAxis(A3);
  if (mouseIsActive) {
    Mouse.move(xReading, yReading, 0);

    delay(responseDelay);
    
  }

}
void setup() {
  Serial.begin(115200);
  Keyboard.begin();
  Mouse.begin();
  Serial.println("----Arduino Start----");

}

void loop() {
  Joy1();
  Joy2();


}
