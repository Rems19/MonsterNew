#include "screen.h"
#include <iostream>

void initScreen(SDL_Surface* & screen) {
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
}

void setScreenBackground(SDL_Surface* screen, SDL_Surface* background) {
    applySurface(0, 0, background, screen, NULL);
}

void updateScreen(SDL_Surface* screen) {
    SDL_Flip(screen);
}
