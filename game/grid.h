#ifndef GRID_H
#define GRID_H

#include <array>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include "affichage/sdl_funcs.h"
#include "affichage/screen.h"
#include "affichage/surfaces.h"

// Spacing between the grid and the screen borders
const int MARGIN_TOP = 32;
const int MARGIN_RIGHT = 15;
const int MARGIN_BOTTOM = 68;
const int MARGIN_LEFT = 15;

// Grid size
const int WIDTH = 5;
const int HEIGHT = 9;

// Case size
const int CASE_WIDTH = (SCREEN_WIDTH - MARGIN_LEFT - MARGIN_RIGHT) / WIDTH;
const int CASE_HEIGHT = (SCREEN_HEIGHT - MARGIN_TOP - MARGIN_BOTTOM) / HEIGHT;

enum Direction { NONE = 0, UP = 1, DOWN = -1, LEFT = 2, RIGHT = -2};

struct caseType {
    int type;
    Direction direction;
};

using TGrid = std::array< std::array<caseType, HEIGHT> , WIDTH >;


void coordsToPixels(int coordX, int coordY, int & x, int & y);
void pixelsToCoords(int x, int y, int & coordX, int & coordY);

void initGrid(TGrid & grid);
void loadLevel(TGrid & grid, int currentLevel);

void draw(TGrid grid, SDL_Surface *s);

void loadSurfaces();
void freeSurfaces();

/*******************************
 *LE JEU
 *******************************/
void moveP(TGrid & grid, int x, int y, Direction &direction, SDL_Surface *s, int num);
bool sortie(int x, int y, Direction &direction);
void levelWin(TGrid & grid, SDL_Surface *s,int &num, int &menu );
Direction mouvement (TGrid & grid, SDL_Event &event, Direction &direction,SDL_Surface *s,
                      int mouseXcoord, int mouseYcoord, int currentLvl);
void checkColAroundMonster(TGrid & grid, int xCoord, int yCoord);

#endif // GRID_H
