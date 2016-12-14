#ifndef SCREEN_H
#define SCREEN_H

#include "affichage/sdl_funcs.h"


const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 512;
const int SCREEN_BPP = 32;

void initScreen(SDL_Surface* & screen);
void setScreenBackground(SDL_Surface* screen, SDL_Surface* background);
void updateScreen(SDL_Surface* screen);

#endif // SCREEN_H
