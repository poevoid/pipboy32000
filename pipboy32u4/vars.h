#pragma once
#define INV 0
#define USB 1
#define MAP 2
#define RAD 3

uint8_t gamestate = 0;
uint8_t currentframe = 0;
uint8_t firstframe = 0;
uint8_t framecount = 7; //1 less than actual number of frames, first frame = 0
uint8_t startcounter = 0;

uint8_t mainMenu = INV;
