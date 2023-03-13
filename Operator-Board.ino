// 2023 Operator Board written by Eric Cao based on the 2020 code
// For any future programmers looking at this,
// make sure that electrical actually did the wiring correctly if something doesn't work

#include <SPI.h>
#include <Arduino.h>
#include <Wire.h>

#include <Joystick.h>
#include <Encoder.h>

//pins for the buttons
int buttonPins[15] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13, A2, A4, A1, A3, A5};
int buttonPress[15];

int SixPosSwitch = A0;

// delay because of the weird six switch hardware
int period = 150;
unsigned long time_now = 0;

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, 
  JOYSTICK_TYPE_MULTI_AXIS, 15, 0,
  true, true, false, false, false, false,
  true, true, false, false, false);

Encoder Enc(2, 3);

const bool testAutoSendMode = false;

void setup() {
  for(int x = 0; x < 15; x++) {
    pinMode(buttonPins[x], INPUT_PULLUP);
  }

  pinMode(A0, INPUT_PULLUP);
  
  Joystick.setThrottleRange(0, 1023);
  Joystick.setRudderRange(0, 1023);
  
  if(testAutoSendMode)
  {
    Joystick.begin();
  }
  else
  {
    Joystick.begin(false);
  }
  
  Serial.begin(9600);
}

long oldPosition  = -999;

void loop() {
  // getting which buttons are pressed
  for(int x = 0; x < 15; x++) {
      buttonPress[x] = !digitalRead(buttonPins[x]);
  }

  // telling which buttons are pressed
  for(int x = 0; x < 15; x++) {
    Joystick.setButton(x, buttonPress[x]);
  }

  // encoder / knob
  long newPosition = Enc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    Joystick.setThrottle(-(newPosition % 1024));
  }

  // read six switch with the delay
  if(millis() >= time_now + period){
    time_now += period;
    Joystick.setRudder(analogRead(SixPosSwitch));
  }

  Joystick.sendState();
}
