#include "editor.h"

void checkEditorKeyEvent(int & choice) {

    Uint8 *keystates = SDL_GetKeyState( NULL );

    if(keystates[SDLK_a]){
        choice = 1;
    }
    if(keystates[SDLK_z]){
        choice = 2;
    }
    if(keystates[SDLK_e]){
        choice = 3;
    }
    if(keystates[SDLK_r]){
        choice = 4;
    }
    if(keystates[SDLK_UP]){
        choice = 5;
    }
    if(keystates[SDLK_DOWN]){
        choice = 6;
    }
    if(keystates[SDLK_RIGHT]){
        choice = 7;
    }
    if(keystates[SDLK_LEFT]){
        choice = 8;
    }
}

void checkEditorMouseClickEvent(TGrid & grid, int coordX, int coordY, int choice) {

    Uint8 mousestates = SDL_GetMouseState(NULL,NULL);

    if (mousestates &SDL_BUTTON_LEFT) {
        if(choice < 5) {
            grid[coordX][coordY].type = choice;
            grid[coordX][coordY].direction = NONE;
        } else {
             grid[coordX][coordY].type = 0;

             switch(choice) {
             case 5:
                 grid[coordX][coordY].direction = UP;
                 break;
             case 6:
                 grid[coordX][coordY].direction = DOWN;
                 break;
             case 7:
                 grid[coordX][coordY].direction = RIGHT;
                 break;
             case 8:
                 grid[coordX][coordY].direction = LEFT;
                 break;
             }
        }

    } else if(mousestates & SDL_BUTTON_RMASK) {
        grid[coordX][coordY].type = 0;
        grid[coordX][coordY].direction = NONE;

    }
}

void drawCursor(SDL_Surface *s, int mouseX, int mouseY, int choice) {

    if((mouseX && mouseY) != 0){
        switch (choice){

        case 1 :
            applySurface(mouseX, mouseY, surf_monstre, s, NULL);
            break;
        case 2:
            applySurface(mouseX, mouseY, surf_glacon, s, NULL);
            break;
        case 3:
            applySurface(mouseX, mouseY, surf_livre, s, NULL);
            break;
        case 4:
            applySurface(mouseX, mouseY, surf_dormeur, s, NULL);
            break;
        case 5:
            applySurface(mouseX, mouseY, surf_haut, s, NULL);
            break;
        case 6:
            applySurface(mouseX, mouseY, surf_bas, s, NULL);
            break;
        case 7:
            applySurface(mouseX, mouseY, surf_droite, s, NULL);
            break;
        case 8:
            applySurface(mouseX, mouseY, surf_gauche, s, NULL);
            break;
        }
    }
}

int levelSelect(int mouseX, int mouseY) {
    int x = 0;
    int y = 0;
    int found = 0;
    while (x < 3 && y < 5 && found == 0) {
        int dx = mouseX - (62 + 90 * x), dy = mouseY - (160 + 80 * y);
        if (dx * dx + dy * dy <= 25 * 25) {
            found = 3 * y + x + 1;
        }
        x++;
        if (x == 3) {
            y++;
            x = 0;
        }
    }
    return found;
}

void saveLevel(TGrid grid, int level) {

    int type;

    std::string lvl;
    lvl = "levels/niveaux" + std::to_string(level) + ".txt";

    std::ofstream fichier(lvl,  std::ios::out |  std::ios::trunc);

    if(fichier) {
        for(int i = 0; i < WIDTH; i++) {
            for(int j = 0; j < HEIGHT; j++) {

                type = grid[i][j].type;

                if(type == 0)
                     switch(grid[i][j].direction) {
                     case UP:
                         type = 5;
                         break;
                     case DOWN:
                         type = 6;
                         break;
                     case RIGHT:
                         type = 7;
                         break;
                     case LEFT:
                         type = 8;
                         break;
                     }
                fichier << type << std::endl;
            }
        }
        fichier.close();
    } else {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier en ecriture." << std::endl;
    }
}
