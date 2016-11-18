#ifndef SDL_FUNCS_H
#define SDL_FUNCS_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>

// Initialization
void initSDL();

// Resource loading
SDL_Surface* loadImage(std::string filename);
SDL_Surface* loadImageWithColorKey(std::string filename, int r, int g, int b);

// Drawing methods
void applySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);

#endif // SDL_FUNCS_H
