//ardu-pip-boy

#include <Keyboard.h>
#include <Encoder.h> //available here: https://github.com/PaulStoffregen/Encoder
#include <Arduboy2.h>
#include <Tinyfont.h>
#include <Joystick.h> 
#include <ArduboyTones.h>


Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  1, 0,                  // Button Count, Hat Switch Count
  true, true, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering
  
Arduboy2 pipboy;
ArduboyTones radio(pipboy.audio.enabled);
Tinyfont tinyfont= Tinyfont(pipboy.sBuffer, Arduboy2::width(), Arduboy2::height());
Encoder Enc(3, 0);

#include "func.h"


void setup() {
  // put your setup code here, to run once:
  pipboy.begin();
  pinMode(3, INPUT_PULLUP);
  pinMode(0, INPUT_PULLUP);
  pipboy.audio.enabled();
  pipboy.clear();
  pipboy.setFrameRate(45); //no need to waste power, right?
  Keyboard.begin();
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (!pipboy.nextFrame()) return;
  pipboy.pollButtons();
  pipboy.clear();
  handleEncoder();
  gameloop();
  pipboy.display();
}
