//ardu-pip-boy

#include <Arduboy2.h>

Arduboy2 pipboy;
#include "func.h"

void setup() {
  // put your setup code here, to run once:
  pipboy.begin();
  pipboy.clear();
  pipboy.setFrameRate(60); //no need to waste power, right?
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!pipboy.nextFrame()) return;
  pipboy.pollButtons();
  pipboy.clear();
  gameloop();
  pipboy.display();
}
