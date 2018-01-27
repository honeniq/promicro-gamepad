// Simple gamepad example that demonstraits how to read five Arduino
// digital pins and map them to the Arduino Joystick library.
//
// The digital pins 2 - 6 are grounded when they are pressed.
// Pin 2 = UP
// Pin 3 = RIGHT
// Pin 4 = DOWN
// Pin 5 = LEFT
// Pin 6 = FIRE
//
// NOTE: This sketch file is for use with Arduino Leonardo and
//       Arduino Micro only.
//
// by Matthew Heironimus
// 2016-11-24
//--------------------------------------------------------------------

#include <Joystick.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  6, 0,                  // Button Count, Hat Switch Count
  true, true, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

void setup() {
  // Initialize Button Pins
  pinMode(18, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);
  pinMode(20, INPUT_PULLUP);
  pinMode(21, INPUT_PULLUP);

  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);

  // Initialize Joystick Library
  Joystick.begin();
  Joystick.setXAxisRange(-1, 1);
  Joystick.setYAxisRange(-1, 1);
}

// Last state of the buttons
int lastDpadState[4] = {0,0,0,0}; // Up, Right, Down, Left
int lastButtonState[6] = {0,0,0,0,0,0};

void loop() {
  for (int i = 0; i <= 3; i++) {
    int currentDpadState = !digitalRead(i + 18);
    if (currentDpadState != lastDpadState[i]) {
      switch (i) {
        case 0:
          Joystick.setYAxis(-currentDpadState);
          break;
        case 1:
          Joystick.setXAxis(currentDpadState);
          break;
        case 2:
          Joystick.setYAxis(currentDpadState);
          break;
        case 3:
          Joystick.setXAxis(-currentDpadState);
          break;
      }
      lastDpadState[i] = currentDpadState;
    }
  }

  for (int i = 0; i <= 5; i++) {
    int currentButtonState = !digitalRead(i + 2);
    if (currentButtonState != lastButtonState[i]) {
      Joystick.setButton(i, currentButtonState);
      lastButtonState[i] = currentButtonState;
    }
  }
  delay(10);
}