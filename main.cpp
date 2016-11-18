#include <iostream>
#include "affichage/screen.h"
#include "menu.h"
#include "grid.h"

using namespace std;

int main() {

    bool quit = false;

    // States
    const int menu = 0, game = 1, editor = 2;
    int state = menu; // Starting state : menu

    // Current level for game state
    int currentLevel = 1;

    // SDL initialization
    initSDL();

    // Screen initialization
    SDL_Surface* screen;
    initScreen(screen);

    // Menu initialization
    initMenu();

    // Resource loading
    SDL_Surface* gameBackground = loadImage("assets/background.bmp");

    SDL_Event event;
    int mouseX, mouseY; // Cursor coordinates in pixels
    int mouseXCoord, mouseYCoord; // Coordinates of the case pointed by the cursor

    while (!quit) {

        // Event management
        while (SDL_PollEvent(&event)) {

            switch (event.type) {

            case SDL_QUIT:
                quit = true;
                break;

            case SDL_MOUSEMOTION:
                mouseX = event.button.x;
                mouseY = event.button.y;
                pixelsToCoords(mouseX, mouseY, mouseXCoord, mouseYCoord);
                break;

            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button) {
                case SDL_BUTTON_LEFT:
                    if (state == menu) {
                        if (isMouseOnPlayButton(mouseX, mouseY))
                            state = game;
                        else if (isMouseOnEditButton(mouseX, mouseY))
                            state = editor;
                        else if (isMouseOnQuitButton(mouseX, mouseY))
                            quit = true;
                    }
                    break;
                default: break;
                }
                break;

            case SDL_KEYDOWN:
                break;

            default: break;

            }

        }

        setScreenBackground(screen, state == menu ? getMenuBackground(mouseX, mouseY) : gameBackground);

        if (state == game) {

            // TODO: game

        } else if (state == editor) {

            // TODO: editor

        }

        updateScreen(screen);
    }

    SDL_FreeSurface(screen);
    freeMenuSurfaces();
    SDL_FreeSurface(gameBackground);
}

