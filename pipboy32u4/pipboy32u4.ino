//ardu-pip-boy
#include <Keyboard.h>
#include <Arduboy2.h>
#include <Tinyfont.h>
#include <Joystick.h>
#include <ArduboyTones.h>
Arduboy2 pipboy;
ArduboyTones radio(pipboy.audio.enabled);
Tinyfont tinyfont= Tinyfont(pipboy.sBuffer, Arduboy2::width(), Arduboy2::height());

#include "func.h"

void setup() {
  // put your setup code here, to run once:
  pipboy.begin();
  pipboy.clear();
  pipboy.setFrameRate(60); //no need to waste power, right?
  Keyboard.begin();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!pipboy.nextFrame()) return;
  pipboy.pollButtons();
  pipboy.clear();
  gameloop();
  pipboy.display();
}
