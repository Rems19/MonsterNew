#include "grid.h"

/****************** Nom de la fonction **********************
* NOM_FONCTION                                              *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Vous décrivez ici ce que fait cette fonction              *
*********************** Entrées *****************************
* Vous décrivez ici les données en entrée de la fonction    *
*********************** Sorties *****************************
* Vous détaillez ici ce que renvoie la fonction             *
************************************************************/
void coordsToPixels(int coordX, int coordY, int & x, int & y) {
    x = MARGIN_LEFT + coordX * CASE_WIDTH;
    y = MARGIN_TOP + coordY * CASE_HEIGHT;
}

/****************** Nom de la fonction **********************
* NOM_FONCTION                                              *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Vous décrivez ici ce que fait cette fonction              *
*********************** Entrées *****************************
* Vous décrivez ici les données en entrée de la fonction    *
*********************** Sorties *****************************
* Vous détaillez ici ce que renvoie la fonction             *
************************************************************/
void pixelsToCoords(int x, int y, int & coordX, int & coordY) {
    if (x - MARGIN_LEFT < 0 || x > MARGIN_LEFT + WIDTH * CASE_WIDTH || y - MARGIN_TOP < 0 || y > MARGIN_TOP + HEIGHT * CASE_HEIGHT) {
        coordX = -1;
        coordY = -1;
    } else {
        coordX = (x - MARGIN_LEFT) / CASE_WIDTH;
        coordY = (y - MARGIN_TOP) / CASE_HEIGHT;
    }
}

/****************** Nom de la fonction **********************
* NOM_FONCTION                                              *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Vous décrivez ici ce que fait cette fonction              *
*********************** Entrées *****************************
* Vous décrivez ici les données en entrée de la fonction    *
*********************** Sorties *****************************
* Vous détaillez ici ce que renvoie la fonction             *
************************************************************/
void initGrid(TGrid & grid) {
    for (int xCoord = 0; xCoord < WIDTH; xCoord++) {
        for (int yCoord = 0; yCoord < HEIGHT; yCoord++) {
            grid[xCoord][yCoord].type = EMPTY;
            grid[xCoord][yCoord].direction = NONE;
        }
    }
}

/****************** Nom de la fonction **********************
* NOM_FONCTION                                              *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Vous décrivez ici ce que fait cette fonction              *
*********************** Entrées *****************************
* Vous décrivez ici les données en entrée de la fonction    *
*********************** Sorties *****************************
* Vous détaillez ici ce que renvoie la fonction             *
************************************************************/
void draw(TGrid grid, SDL_Surface *s) {
    int x = -1;
    int y = -1;

    for(int i = 0; i < WIDTH; i++) {
        for(int j = 0; j < HEIGHT; j++) {

            coordsToPixels(i, j, x, y);   //on récupère la position en pixel de la case selectionnée

            switch (grid[i][j].direction) {

            case UP:
                applySurface(x + 5, y + 5, surf_haut, s, NULL);
                break;
            case DOWN:
                applySurface(x + 5, y + 5, surf_bas, s, NULL);
                break;
            case RIGHT:
                applySurface(x + 5, y + 5, surf_droite, s, NULL);
                break;
            case LEFT:
                applySurface(x + 5, y + 5, surf_gauche, s, NULL);
                break;
            default:
                break;
            }

            switch (grid[i][j].type) {

            case MONSTER:
                applySurface(x, y, surf_monstre, s, NULL);
                break;
            case ICE:
                applySurface(x, y - 14, surf_glacon, s, NULL);
                break;
            case BOOK:
                applySurface(x, y - 14, surf_livre, s, NULL);
                break;
            case SLEEPER:
                applySurface(x, y - 10, surf_dormeur, s, NULL);
                break;
            default: break;
            }
        }
    }
}

/****************** Nom de la fonction **********************
* NOM_FONCTION                                              *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Vous décrivez ici ce que fait cette fonction              *
*********************** Entrées *****************************
* Vous décrivez ici les données en entrée de la fonction    *
*********************** Sorties *****************************
* Vous détaillez ici ce que renvoie la fonction             *
************************************************************/
void loadLevel(TGrid & grid, int currentLevel) {

    std::string lvl;
    int n;
    CaseType caseType;
    int x = 0;
    int y = 0;

    lvl = "levels/niveaux" + std::to_string(currentLevel) + ".txt";

    std::ifstream monFlux(lvl);  //Ouverture d'un fichier en lecture

    if(monFlux) {
        while(!monFlux.eof()) {
            monFlux >> n;
            caseType = (CaseType) n;

            grid[x][y].type = EMPTY;
            switch(caseType) {
            case UP_E:
                grid[x][y].direction = UP;
                break;
            case DOWN_E:
                grid[x][y].direction = DOWN;
                break;
            case RIGHT_E:
                grid[x][y].direction = RIGHT;
                break;
            case LEFT_E:
                grid[x][y].direction = LEFT;
                break;
            default:
                grid[x][y].type = caseType;
                grid[x][y].direction = NONE;
                break;
            }

            if(y + 1  < HEIGHT) {
                y++;
            } else {
                y = 0;
                x++;
            }
        }
    } else {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." <<  std::endl;
    }
    monFlux.close();
}

/****************** Nom de la fonction **********************
* NOM_FONCTION                                              *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Vous décrivez ici ce que fait cette fonction              *
*********************** Entrées *****************************
* Vous décrivez ici les données en entrée de la fonction    *
*********************** Sorties *****************************
* Vous détaillez ici ce que renvoie la fonction             *
************************************************************/
bool sortie(int x, int y, Direction &direction){

    bool sortie = false;

    if(direction == LEFT && x == 0){
        sortie = true;
    }

    if(direction == RIGHT && x == WIDTH - 1){
        sortie = true;
    }

    if(direction == UP && y == 0){
        sortie = true;
    }

    if(direction == DOWN && y == HEIGHT - 1){
        sortie = true;
    }

    return sortie;
}

/****************** Nom de la fonction **********************
* NOM_FONCTION                                              *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Vous décrivez ici ce que fait cette fonction              *
*********************** Entrées *****************************
* Vous décrivez ici les données en entrée de la fonction    *
*********************** Sorties *****************************
* Vous détaillez ici ce que renvoie la fonction             *
************************************************************/
void collisionWith(TGrid & grid, int x, int y) {
    switch(grid[x][y].type) {
    case ICE:
        grid[x][y].type = EMPTY;
        break;
    case SLEEPER:
        grid[x][y].type = MONSTER;
        break;
    default: break;
    }
}

/****************** Nom de la fonction **********************
* NOM_FONCTION                                              *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Vous décrivez ici ce que fait cette fonction              *
*********************** Entrées *****************************
* Vous décrivez ici les données en entrée de la fonction    *
*********************** Sorties *****************************
* Vous détaillez ici ce que renvoie la fonction             *
************************************************************/
void checkColAroundMonster(TGrid & grid, int xCoord, int yCoord) {


    if(xCoord + 1 < WIDTH ) {
        if(grid[xCoord + 1][yCoord].type == SLEEPER) {
            grid[xCoord + 1][yCoord].type = MONSTER;
        }
    }

    if(xCoord - 1 > -1 ) {
        if(grid[xCoord - 1][yCoord].type == SLEEPER) {
            grid[xCoord - 1][yCoord].type = MONSTER;
        }
    }

    if(yCoord - 1 > -1 ) {
        if(grid[xCoord][yCoord - 1].type == SLEEPER) {
            grid[xCoord][yCoord - 1].type = MONSTER;
        }
    }

    if(yCoord + 1 < HEIGHT ) {
        if(grid[xCoord][yCoord + 1].type == SLEEPER) {
            grid[xCoord][yCoord + 1].type = MONSTER;
        }
    }
}

/****************** Nom de la fonction **********************
* NOM_FONCTION                                              *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Vous décrivez ici ce que fait cette fonction              *
*********************** Entrées *****************************
* Vous décrivez ici les données en entrée de la fonction    *
*********************** Sorties *****************************
* Vous détaillez ici ce que renvoie la fonction             *
************************************************************/
void moveP(TGrid & grid, int x, int y, Direction & direction, SDL_Surface *s, int num){

    int i;
    int j;

    coordsToPixels(x, y, i, j);

    int caseFinalx = x;
    int caseFinaly = y;

    int coordCaseFinalx = 0;
    int coordCaseFinaly = 0;

    int delay = 1; // Changer la vitesse de l'animation ici

    CaseType nextCaseType;
    Direction caseDir;

    if(direction == RIGHT){

        bool stop = false;
        int dx = 0;
        while (!stop) {
            nextCaseType = grid[x + dx + 1][y].type;
            caseDir = grid[x + dx][y].direction;
            if ((caseDir != NONE && caseDir != RIGHT) || ( nextCaseType != EMPTY)  || x + dx == WIDTH - 1)
                stop = true;
            else dx++;
        }
        caseFinalx += dx;

        grid[x][y].type = EMPTY;
        coordsToPixels(caseFinalx, caseFinaly, coordCaseFinalx, coordCaseFinaly);

        while(i < coordCaseFinalx){
            i++;
            setScreenBackground(s,surf_background);
            draw(grid, s);
            applySurface(i,j,surf_monstre,s,NULL);
            SDL_Flip(s);
            SDL_Delay(delay);
        }

        grid[caseFinalx][caseFinaly].type = MONSTER;
    }

    if(direction == DOWN){

        bool stop = false;
        int dy = 0;
        while (!stop) {
            nextCaseType = grid[x][y + dy + 1].type;
            caseDir = grid[x][y + dy].direction;
            if ((caseDir != NONE && caseDir != DOWN) || ( nextCaseType != EMPTY) || y + dy == HEIGHT - 1)
                stop = true;
            else dy++;
        }
        caseFinaly += dy;

        grid[x][y].type = EMPTY;
        coordsToPixels(caseFinalx, caseFinaly, coordCaseFinalx, coordCaseFinaly);

        while(j < coordCaseFinaly){
            j++;
            setScreenBackground(s,surf_background);
            draw(grid, s);
            applySurface(i,j,surf_monstre,s,NULL);
            SDL_Flip(s);
            SDL_Delay(delay);
        }
        grid[caseFinalx][caseFinaly].type = MONSTER;


    }

    if(direction == UP){

        bool stop = false;
        int dy = 0;
        while (!stop) {
            nextCaseType = grid[x][y - dy - 1].type;
            caseDir = grid[x][y - dy].direction;
            if ((caseDir != NONE && caseDir != UP) || ( nextCaseType != EMPTY) || y - dy == 0)
                stop = true;
            else dy++;
        }
        caseFinaly -= dy;

        grid[x][y].type = EMPTY;
        coordsToPixels(caseFinalx, caseFinaly, coordCaseFinalx, coordCaseFinaly);


        while(j > coordCaseFinaly){
            j--;
            setScreenBackground(s,surf_background);
            draw(grid, s);
            applySurface(i,j,surf_monstre,s,NULL);
            SDL_Flip(s);
            SDL_Delay(delay);

        }

        grid[caseFinalx][caseFinaly].type = MONSTER;


    }

    if(direction == LEFT){

        bool stop = false;
        int dx = 0;
        while (!stop) {
            nextCaseType = grid[x - dx - 1][y].type;
            caseDir = grid [x - dx][y].direction;
            if ((caseDir != NONE && caseDir != LEFT) || ( nextCaseType != EMPTY) || x - dx == 0)
                stop = true;
            else dx++;
        }
        caseFinalx -= dx;

        grid[x][y].type = EMPTY;
        coordsToPixels(caseFinalx, caseFinaly, coordCaseFinalx, coordCaseFinaly);

        while(i > coordCaseFinalx){
            i--;
            setScreenBackground(s,surf_background);
            draw(grid, s);
            applySurface(i,j,surf_monstre,s,NULL);
            SDL_Flip(s);
            SDL_Delay(delay);
        }
        grid[caseFinalx][caseFinaly].type = MONSTER;
    }

    /***********************************************************************************
 ******** evenement après deplacement du monstre
 ********************************************************************************/
    Direction dir = caseDir;
    if (dir != NONE) {
        moveP(grid, caseFinalx, caseFinaly, dir, s, num);
    } else if(sortie(caseFinalx,caseFinaly,direction)==true) {
        initGrid(grid);
        loadLevel(grid, num);
    } else {
        int colWithX = 0;
        int colWithY = 0;

        switch(direction){
        case RIGHT :
            colWithX = caseFinalx+1;
            colWithY = caseFinaly;
            collisionWith(grid, colWithX,colWithY);
            setScreenBackground(s,surf_background);
            draw(grid, s);
            SDL_Flip(s);
            break;
        case LEFT :
            colWithX = caseFinalx-1;
            colWithY = caseFinaly;
            collisionWith(grid, colWithX,colWithY);
            setScreenBackground(s,surf_background);
            draw(grid, s);
            SDL_Flip(s);
            break;
        case UP :
            colWithX = caseFinalx;
            colWithY = caseFinaly-1;
            collisionWith(grid, colWithX,colWithY);
            setScreenBackground(s,surf_background);
            draw(grid, s);
            SDL_Flip(s);
            break;
        case DOWN :
            colWithX = caseFinalx;
            colWithY = caseFinaly+1;
            collisionWith(grid, colWithX,colWithY);
            setScreenBackground(s,surf_background);
            draw(grid, s);
            SDL_Flip(s);
            break;
        default:
            break;

        }
        checkColAroundMonster(grid, caseFinalx, caseFinaly);
    }
    direction = NONE;
}

/****************** Nom de la fonction **********************
* NOM_FONCTION                                              *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Vous décrivez ici ce que fait cette fonction              *
*********************** Entrées *****************************
* Vous décrivez ici les données en entrée de la fonction    *
*********************** Sorties *****************************
* Vous détaillez ici ce que renvoie la fonction             *
************************************************************/
Direction mouvement (TGrid & grid, SDL_Event &event, Direction &direction, SDL_Surface *s, int mouseXcoord, int mouseYcoord, int currentLvl) {

    int caseDirectionY = 0;
    int caseDirectionX = 0;

    if(grid[mouseXcoord][mouseYcoord].type == 1 && event.button.button == SDL_BUTTON_LEFT){

        while(event.type!=SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT){

            SDL_PollEvent(&event);

            pixelsToCoords(event.button.x, event.button.y, caseDirectionX, caseDirectionY);

            if(caseDirectionX == mouseXcoord && caseDirectionY < mouseYcoord){
                direction = UP;
            }
            if(caseDirectionX == mouseXcoord && caseDirectionY > mouseYcoord){
                direction = DOWN;
            }
            if(caseDirectionX > mouseXcoord && caseDirectionY == mouseYcoord) {
                direction = RIGHT;
            }
            if(caseDirectionX < mouseXcoord && caseDirectionY == mouseYcoord) {
                direction = LEFT;
            }
            if(caseDirectionX == mouseXcoord && caseDirectionY == mouseYcoord) {
                direction = NONE;
            }
        }
    }

    while(direction != NONE) {
        moveP(grid, mouseXcoord, mouseYcoord, direction, s, currentLvl);
    }

    return direction;
}

/****************** Nom de la fonction **********************
* NOM_FONCTION                                              *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Vous décrivez ici ce que fait cette fonction              *
*********************** Entrées *****************************
* Vous décrivez ici les données en entrée de la fonction    *
*********************** Sorties *****************************
* Vous détaillez ici ce que renvoie la fonction             *
************************************************************/
bool checkWin(TGrid grid) {
    bool win = true;
    int i = 0;
    int j = 0;

    while (win == true && i < HEIGHT) {
        j = 0;
        while (win == true && j < WIDTH) {
            if (grid[j][i].type == SLEEPER) {
                win = false;
            }
            j++;
        }
        i++;
    }
    return win;
}

/****************** Nom de la fonction **********************
* NOM_FONCTION                                              *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Vous décrivez ici ce que fait cette fonction              *
*********************** Entrées *****************************
* Vous décrivez ici les données en entrée de la fonction    *
*********************** Sorties *****************************
* Vous détaillez ici ce que renvoie la fonction             *
************************************************************/
void levelWin(TGrid & grid, SDL_Surface *s, int &num, State &state, int levelMax) {
    if(checkWin(grid) == 1 && num < levelMax) {
        updateScreen(s);
        SDL_Delay(500);
        setScreenBackground(s,surf_win);
        SDL_Flip(s);
        SDL_Delay(1500);

        num++;

        initGrid(grid);
        loadLevel(grid, num);

    } else if(checkWin(grid) == 1 && num == levelMax) {
        setScreenBackground(s,surf_winEnd);
        SDL_Flip(s);
        SDL_Delay(3000);
        state = MENU;
    }
}

