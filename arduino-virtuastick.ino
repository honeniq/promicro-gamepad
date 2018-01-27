#include <Joystick.h>

#define OFFSET_DPAD 18
#define OFFSET_BUTTON 2

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  6, 0,                  // Button Count, Hat Switch Count
  true, true, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

void setup() {
  // Initialize Button Pins
  pinMode(18, INPUT_PULLUP); // D-pad Up
  pinMode(19, INPUT_PULLUP); // D-pad Right
  pinMode(20, INPUT_PULLUP); // D-pad Down
  pinMode(21, INPUT_PULLUP); // D-pad Left
  pinMode(2, INPUT_PULLUP);  // Button 1
  pinMode(3, INPUT_PULLUP);  // Button 2
  pinMode(4, INPUT_PULLUP);  // Button 3
  pinMode(5, INPUT_PULLUP);  // Button 4
  pinMode(6, INPUT_PULLUP);  // Button 5
  pinMode(7, INPUT_PULLUP);  // Button 6

  // Initialize Joystick Library
  Joystick.begin();
  Joystick.setXAxisRange(-1, 1);
  Joystick.setYAxisRange(-1, 1);
}

// Last state of the buttons
int lastDpadState[4] = {0,0,0,0};        // Up, Right, Down, Left
int lastButtonState[6] = {0,0,0,0,0,0};  // Button 1 - 6

void loop() {
  updateDpad();
  updateButton();

  delay(10);
}

void updateDpad() {
  for (int i = 0; i <= 3; i++) {
    int currentDpadState = !digitalRead(i + OFFSET_DPAD);
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
}

void updateButton() {
  for (int i = 0; i <= 5; i++) {
    int currentButtonState = !digitalRead(i + OFFSET_BUTTON);
    if (currentButtonState != lastButtonState[i]) {
      Joystick.setButton(i, currentButtonState);
      lastButtonState[i] = currentButtonState;
    }
  }
}