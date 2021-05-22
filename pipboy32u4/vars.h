#pragma once
#define INV 0
#define USB 1
#define MAP 2
#define RAD 3
#define JOYSTICK_REPORT_ID 0x03

uint8_t gamestate = 0;
uint8_t currentframe = 0;
uint8_t firstframe = 0;
uint8_t framecount = 7; //1 less than actual number of frames, first frame = 0
uint8_t startcounter = 0;
uint8_t mainMenu = INV;
uint8_t USBselect = 0;
uint8_t INVselect = 0;
uint8_t RADselect = 0;
uint8_t INVcursorx;
uint8_t INVcursory;

uint8_t currentawaveframe = 0;
uint8_t currentbwaveframe = 13;
/*///////////////////////////////JOYSTICK////////////////////////////////////////////////////*/
unsigned long holdSpecialButton = 0, startHeldDown = 0, selectHeldDown = 0;
bool startButton = false, selectButton = false;
const int m = 0xFFFF;
const int buttonHeldTime = 300, buttonReleaseTime = 1000;
/*/////////////////////////////////////////////////////////////////////////////////////////////////*/

extern void CommandAtRunBarMSWIN(char *SomeCommand); //Opens the run bar and executes the command.
extern void CommandAtRunBarGnome(char *SomeCommand);

/********************************************************************
 * Opens the run bar and executes the command. 
 ********************************************************************/
void CommandAtRunBarMSWIN(char *SomeCommand){
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  delay(100);
  Keyboard.releaseAll();
  delay(1500);
  Keyboard.print(SomeCommand);
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
}
void CommandAtRunBarGnome(char *SomeCommand){
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_F2);
  delay(100);
  Keyboard.releaseAll();
  delay(1500);
  Keyboard.print(SomeCommand);
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
}
