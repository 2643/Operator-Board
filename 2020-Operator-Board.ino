#include <Joystick.h>
#include <Adafruit_SSD1306.h>
#include <DynamicHID.h>
#include <SPI.h>
#include <Joystick.h>
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/*
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
*/

//int c;

//pins for the buttons
int SixPosSwitch = A0;
//int PotPin = A1; 
int buttonPins[16] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, A2, A3, A4, A5};
int buttonPress[16];

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, 
  JOYSTICK_TYPE_MULTI_AXIS, 16, 0,
  true, true, false, false, false, false,
  true, true, false, false, false);

const bool testAutoSendMode = false;

void setup() 
{
  /*
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(2000);
  display.clearDisplay();
  
  display.drawPixel(10, 10, WHITE);
  display.display();
  testdrawchar(0, 0);
  */
  
  for(int x = 0; x < 16; x++)
  {
    pinMode(buttonPins[x], INPUT_PULLUP);
  }

  pinMode(A0, INPUT_PULLUP);
  //pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);
  
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

/*
void testdrawchar(int feet, int inches)
{
  display.clearDisplay();
  display.setTextSize(4);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print(feet);
  display.print("\'");
  display.print(inches);
  display.print("\"");
  display.display();
  delay(1);
} */

/* May need this later in the season, at the moment, not necessary
void calculate(int potVal)
{
  int inch = potVal * c;
  int feet = inch / 12;
  inch = inch % 12;
  testdrawchar(feet, inch);
}*/

void loop() 
{
  //Setting the range of the throttle and the rudder
  //Joystick.setThrottle(analogRead(PotPin)-66);


  //level 1: 0-200
  //level 2: 201-480
  //level 3: 481-600
  //level 4: 601-710
  //level 5: 711-810
  //level 6: 811-1000
  Joystick.setRudder(analogRead(SixPosSwitch));


  
  //calculate(analogRead(PotPin)-66); May need this later in the season if we decide to put the display on the operator board

  //getting which buttons are pressed
  for(int x = 0; x < 16; x++)
  {
      buttonPress[x] = !digitalRead(buttonPins[x]);
  }

  //telling which buttons are pressed
  for(int x = 0; x < 16; x++)
  {
    Joystick.setButton(x, buttonPress[x]);
  }

  Joystick.sendState();
  //Serial.println(analogRead(PotPin));
  Serial.println(analogRead(SixPosSwitch));
}
