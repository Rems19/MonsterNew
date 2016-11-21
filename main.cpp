#include <iostream>
#include "affichage/screen.h"
#include "menu/menu.h"
#include "game/grid.h"
#include "levelCreator/levelcreator.h"

using namespace std;

int main() {

    bool quit = false;

    // States
    const int menu = 0, game = 1, editor = 2;
    int state = menu; // Starting state : menu

    // Current level for game state
    int currentLevel = 5;

    // Choice for levelCretor
    int choice = 1;

    // SDL initialization
    initSDL();

    // Screen initialization
    SDL_Surface* screen;

    initScreen(screen);

    // Menu initialization
    initMenu();

    // Grid initialization

    initGrid();
    readLevel(currentLevel);

    //Surfaces game Initialization
    loadSurfaces();

    // Resource loading
    SDL_Surface* gameBackground = loadImage("assets/background.bmp");
    SDL_Surface* selectLevelBackground = loadImage("assets/niveaux.png");

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

            case SDL_MOUSEBUTTONUP:
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

            draw(screen);

        } else if (state == editor) {

            if(currentLevel > 0){                    //si on a choisi le niveau on lance l'éditeur

                checkEvent(event,choice);
                draw(screen);
                drawCursor(screen,event,choice);
                saveLevel(currentLevel);
            } else {                                //sinon on reste a l'accueil
                setScreenBackground(screen,selectLevelBackground);
                // levelSelect(mouseX,mouseY,currentLevel);
            }

        }

        updateScreen(screen);
    }

    SDL_FreeSurface(screen);
    freeMenuSurfaces();
    freeSurfaces();
    SDL_FreeSurface(gameBackground);
    SDL_FreeSurface(selectLevelBackground);
}

