#ifndef GRID_H
#define GRID_H

#include <array>
#include "affichage/screen.h"

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

using TGrid = std::array< std::array<int, HEIGHT> , WIDTH >;

void coordsToPixels(int coordX, int coordY, int & x, int & y);
void pixelsToCoords(int x, int y, int & coordX, int & coordY);

void initGrid();

#endif // GRID_H
