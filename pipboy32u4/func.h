#pragma once

#include "arrays.h"

void animate(){
  if (pipboy.everyXFrames(9)) {
    if (currentframe < framecount) {
      ++currentframe;
      ++startcounter;
    }
    else {
      currentframe = firstframe;
    }
  }
}
void startup(){
  //start animation, vault boy probably.
  Sprites::drawOverwrite(WIDTH/2-vaultboyWidth/2,0, vaultboy, currentframe);
  animate();
  if (startcounter == framecount*4){
    gamestate = 1;
  }
}

void handleMainMenu(){
  if (mainMenu == INV){//highlight INV
    pipboy.drawLine(0,51, 35, 51);
    pipboy.drawLine(35, 51, 35, 64);
  }
  if (mainMenu == USB){//highlight UDB
    pipboy.drawLine(33, 51, 65, 51);
    pipboy.drawLine(33, 51, 33, 65);
    pipboy.drawLine(65,51,65,64);
  }
  if (mainMenu == MAP){//highlight MAP
    pipboy.drawLine(63, 51, 63, 64);
    pipboy.drawLine(63,51, 95, 51);
    pipboy.drawLine(95, 51, 95, 64);
  }
  if (mainMenu == RAD){ //highlight RAD
    pipboy.drawLine(93, 51, 93, 64);
    pipboy.drawLine(93, 51, 128, 51);
  }
  if (pipboy.justPressed(RIGHT_BUTTON) && mainMenu < 3){
    ++mainMenu;
  }
  if (pipboy.justPressed(LEFT_BUTTON) && mainMenu > 0){
    --mainMenu;
  }
}

void UI(){
 //actual "game"
 //menus include: Inventory (INV), MAP, USB interfaces (USB), and "Radio" (RAD)  
 //draw menu 
 pipboy.setCursor(0,56);
 pipboy.print(F("  INV  USB  MAP  RAD"));
 pipboy.drawLine(0, 52, 128, 52);//bottom H-line
 pipboy.drawLine(34, 52, 34, 64);//INV | USB
 pipboy.drawLine(64, 52, 64, 64);// USB | MAP
 pipboy.drawLine(94, 52, 94, 64);// MAP | RAD
 
 
 //update menu
 handleMainMenu();
 //update specific menu parts if they are selected 
 //change selection based on current screen and selection counter. 
 //change current screen
 
}

void gameloop(){
  switch (gamestate){

    case 0:
    startup();
    break;

    case 1:
    //user interface
    UI();
    break;
    
  }
}
