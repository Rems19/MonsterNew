#ifndef MONSTER_H
#define MONSTER_H

#include <array>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>

#include "main.h"
#include "affichage/sdl_funcs.h"
#include "affichage/screen.h"
#include "affichage/surfaces.h"
#include "grid.h"


//Slow Animation
const int DELAY = 2;

/*******************************
 * GAME
 *******************************/
void moveMonster(TGrid & grid, int x, int y, Direction &direction, SDL_Surface *s, int num);
void levelWin(TGrid & grid, SDL_Surface *s, int &num, State &state, int levelMax);
void mouvement (TGrid & grid, SDL_Event &event,SDL_Surface *s,
                      int mouseXcoord, int mouseYcoord, int currentLvl);
void checkColAroundMonster(TGrid & grid, int xCoord, int yCoord);

#endif // MONSTER_H
