#include "monster.h"


/****************** Nom de la fonction **********************
* collisionWith                                             *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Permet de supprimer un glaçon ou de réveiller un dormeur  *
* présent dans une case donnée en paramètre                 *
*********************** Entrées *****************************
* TGrid & grid: tableau correspondant à la grille           *
* int x, int y: coordonnées de la case en collsion          *
*********************** Sorties *****************************
* retourne vrai s'il y a eu collision false sinon           *
************************************************************/
CaseType collisionWith(TGrid & grid, int x, int y) {

    CaseType col = EMPTY;

    switch(grid[x][y].type) {
    case ICE:

        grid[x][y].type = EMPTY;
        col = ICE;
        break;

    case SLEEPER:
        grid[x][y].type = MONSTER;
        col = SLEEPER;
        break;

    default: break;
    }

    return col;

}

/****************** Nom de la fonction **********************
* sortie                                                    *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Retourne un booléen pour savoir si un monstre sort de la  *
* grille                                                    *
*********************** Entrées *****************************
* int x, y: correspond aux coordonnées du monstre (grille)  *
* Direction direction: correspond à la direction du         *
* déplacement du monstre                                    *
*********************** Sorties *****************************
* revoie true ou false si le monstre sort ou non            *
************************************************************/
bool sortie(int x, int y, Direction direction){

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
* checkColAroundMonster                                     *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Permet à partir des coordonnées d'un monstre de réveiller *
* tous les monstres autour                                  *
*********************** Entrées *****************************
* TGrid & grid: tableau correspondant à la grille           *
* int x, int y: coordonnées de la case du monstre           *
*********************** Sorties *****************************
* ne retourne rien (référence)                              *
************************************************************/
void checkColAroundMonster(TGrid & grid, int x, int y) {

    if(x + 1 < WIDTH ) {
        if(grid[x + 1][y].type == SLEEPER) {
            grid[x + 1][y].type = MONSTER;
        }
    }

    if(x - 1 > -1 ) {
        if(grid[x - 1][y].type == SLEEPER) {
            grid[x - 1][y].type = MONSTER;
        }
    }

    if(y - 1 > -1 ) {
        if(grid[x][y - 1].type == SLEEPER) {
            grid[x][y - 1].type = MONSTER;
        }
    }

    if(y + 1 < HEIGHT ) {
        if(grid[x][y + 1].type == SLEEPER) {
            grid[x][y + 1].type = MONSTER;
        }
    }
}

/****************** Nom de la fonction **********************
* moveXYAccordingToDirection                                *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Permet d'incrémenter des coefficients x et y en fonction  *
* de la direction (qui permettent d'avoir la position des   *
* cases suivantes)                                          *
*********************** Entrées *****************************
* TGrid & grid: tableau correspondant à la grille           *
* int x, int y: coordonnées de la case du monstre           *
* Direction & direction: direction donnée pour le déplacer  *
*                        le monstre                         *
* SDL_Surface *s: surface de la fenêtre                     *
*********************** Sorties *****************************
* ne retourne rien (référence)                              *
************************************************************/
void moveXYAccordingToDirection(Direction direction, int & x, int & y) {

    switch (direction) {
    case RIGHT:
        x += 1;
        y += 0;
        break;
    case LEFT:
        x += -1;
        y += 0;
        break;
    case UP:
        x += 0;
        y += -1;
        break;
    case DOWN:
        x += 0;
        y += 1;
        break;
    default:
        x += 0;
        y += 0;
        break;
    }
}

/****************** Nom de la fonction **********************
* findNextCase                                              *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Permet de déterminer et d'affecter les coordonnées de la  *
* case final du monstre après déplacement dans une          *
* direction                                                 *
*********************** Entrées *****************************
* TGrid & grid: tableau correspondant à la grille           *
* int x, int y: coordonnées de la case du monstre           *
* int caseFinalx, int caseFinaly): coordonnées de la case   *
*                                  finale du monstre        *
* Direction & direction: direction donnée pour le déplacer  *
*                        le monstre                         *
* SDL_Surface *s: surface de la fenêtre                     *
*********************** Sorties *****************************
* ne retourne rien (référence)                              *
************************************************************/
Direction findNextCase(TGrid & grid, Direction direction, int x, int y, int & caseFinalx, int & caseFinaly) {

    CaseType nextCaseType;
    Direction caseDir;

    caseFinalx = x;
    caseFinaly = y;

    bool stop = false;

    int dx = 0;
    int dy = 0;

    moveXYAccordingToDirection(direction, dx, dy);
    caseDir = grid[x][y].direction;
    nextCaseType = grid[x + dx][y + dy].type;

    if(direction != NONE) {

        while (!stop) {

            if ((caseDir != NONE && caseDir != direction) || ( nextCaseType != EMPTY) || x + dx == WIDTH  ||y + dy == HEIGHT  || y + dy == -1 || x + dx == -1 ) {
                stop = true;

            } else {
                caseDir = grid[x + dx][y + dy].direction;
                moveXYAccordingToDirection(direction, dx, dy);
                nextCaseType = grid[x + dx][y + dy].type;
            }
        }
        caseFinalx += dx;
        caseFinaly += dy;

        dx = 0;
        dy = 0;

        moveXYAccordingToDirection(direction, dx, dy);

        caseFinalx -= dx;
        caseFinaly -= dy;

        if(caseFinalx == x && caseFinaly == y && grid[x][y].direction != NONE) {
            caseDir = NONE;    //si on est bloqué par un obstacle et que l'on reste sur place
        }
    }

    return caseDir;
}

/****************** Nom de la fonction **********************
* animMonster                                               *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Permet de déplacer le monstre à partir d'un direction     *
* et d'agir en fonction de ce déplacement (collisions,      *
*sortie, changement de direction, modification de la grille,*
* affichage)                                                *
*********************** Entrées *****************************
* TGrid & grid: tableau correspondant à la grille           *
* int x, int y: coordonnées de la case du monstre           *
* int caseFinalx, int caseFinaly): coordonnées de la case   *
*                                  finale du monstre        *
* Direction & direction: direction donnée pour le déplacer  *
*                        le monstre                         *
* SDL_Surface *s: surface de la fenêtre                     *
* int num: correspond au numéro du niveau en cour           *
*********************** Sorties *****************************
* ne retourne rien (référence)                              *
************************************************************/
void animMonster(TGrid & grid, SDL_Surface *s, Direction & direction,int x, int y,  int caseFinalx, int caseFinaly) {

    int i;
    int j;

    int coordCaseFinalx;
    int coordCaseFinaly;

    coordsToPixels(x, y, i, j);

    coordsToPixels(caseFinalx, caseFinaly, coordCaseFinalx, coordCaseFinaly);

    while( i != coordCaseFinalx || j != coordCaseFinaly  ) {
        moveXYAccordingToDirection(direction, i, j);
        setScreenBackground(s,surf_background);
        draw(grid, s);
        applySurface(i + 5,j,surf_monstre,s,NULL);
        SDL_Flip(s);
        SDL_Delay(DELAY);
    }
}

/****************** Nom de la fonction **********************
* animGlacon                                                *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Permet d'animer le glaçon lorsqu'il est détruit dans une  *
* case de coodonnées x , y                                  *
*********************** Entrées *****************************
* TGrid & grid: tableau correspondant à la grille           *
* int x, int y: coordonnées de la case du glacon            *
* SDL_Surface *s: surface de la fenêtre                     *
*********************** Sorties *****************************
* ne retourne rien (référence)                              *
************************************************************/
void animGlacon(TGrid & grid, SDL_Surface *s,int x, int y) {
    int coordCasex;
    int coordCasey;

    coordsToPixels(x, y, coordCasex, coordCasey);

    for (int i = 0; i < 2; i++ ) {

        setScreenBackground(s,surf_background);
        draw(grid, s);

        switch(i) {

        case 0:
            applySurface(coordCasex -2,coordCasey -8, surf_glacon1, s, NULL);
            break;
        case 1:
            applySurface(coordCasex-2,coordCasey -8, surf_glacon2, s, NULL);
            break;
        }

        SDL_Flip(s);
        SDL_Delay(100);
    }

}


/****************** Nom de la fonction **********************
* moveMonster                                               *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Permet de déplacer le monstre à partir d'un direction     *
* et d'agir en fonction de ce déplacement (collisions,      *
*sortie, changement de direction, modification de la grille,*
* affichage)                                                *
*********************** Entrées *****************************
* TGrid & grid: tableau correspondant à la grille           *
* int x, int y: coordonnées de la case du monstre           *
* Direction & direction: direction donnée pour le déplacer  *
*                        le monstre                         *
* SDL_Surface *s: surface de la fenêtre                     *
* int num: correspond au numéro du niveau en cour           *
*********************** Sorties *****************************
* ne retourne rien (référence)                              *
************************************************************/
void moveMonster(TGrid & grid, int x, int y, Direction & direction, SDL_Surface *s, int num){

    int caseFinalx;
    int caseFinaly;

    Direction nextCaseDir = findNextCase(grid, direction, x, y, caseFinalx, caseFinaly );

    grid[x][y].type = EMPTY;

    animMonster(grid, s, direction, x, y, caseFinalx, caseFinaly);

    grid[caseFinalx][caseFinaly].type = MONSTER;


    /***********************************************************************************
 ******** evenement après deplacement du monstre
 ********************************************************************************/
    if (nextCaseDir != NONE) {      // si la case sur laquelle on est une direction on la modifie
        direction = nextCaseDir;
    }

    if(sortie(caseFinalx,caseFinaly,direction)) {
        initGrid(grid);
        loadLevel(grid, num);
    } else {

        int colWithX;
        int colWithY;

        colWithX = caseFinalx;
        colWithY = caseFinaly;

        moveXYAccordingToDirection(direction, colWithX, colWithY);

        if( collisionWith(grid, colWithX,colWithY) == ICE) animGlacon(grid, s, colWithX, colWithY);

        setScreenBackground(s,surf_background);
        draw(grid, s);
        SDL_Flip(s);

        if (nextCaseDir != NONE){
            moveMonster(grid, caseFinalx, caseFinaly, direction, s, num);
        } else {
            checkColAroundMonster(grid, caseFinalx, caseFinaly);
        }
    }
}

/****************** Nom de la fonction **********************
* mouvement                                                 *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Permet de selectionner une direction en cliquant sur un   *
* monstre et en relachant sur une case                      *
*********************** Entrées *****************************
* TGrid & grid: tableau correspondant à la grille           *
* int mouseXcoord, int mouseYcoord: coordonnées de la souris*
* Direction & direction: direction donnée pour le déplacer  *
*                        le monstre                         *
* SDL_Surface *s: surface de la fenêtre                     *
* int currentLevel: correspond au numéro du niveau en cour  *
* SDL_Event &event: variable d'évènement de du programme    *
*********************** Sorties *****************************
*ne retourne rien                                           *
************************************************************/
void mouvement (TGrid & grid, SDL_Event &event,SDL_Surface *s, int mouseXcoord, int mouseYcoord, int currentLvl) {

    int caseDirectionY = 0;
    int caseDirectionX = 0;

    Direction direction = NONE;

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

    if(direction != NONE)
        moveMonster(grid, mouseXcoord, mouseYcoord, direction, s, currentLvl);

}


/****************** Nom de la fonction **********************
* checkWin                                                  *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Permet de savoir si on a fini un niveau en renvoyant vrai *
* ou faux (s'il reste des dormeurs)                         *
*********************** Entrées *****************************
* TGrid & grid: tableau correspondant à la grille           *
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
* levelWin                                                  *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* permet d'agir quand l'on termine un niveau :              *
* on passe au niveau suivant ou on lance le screen de fin   *
* puis on repasse au menu                                   *
*********************** Entrées *****************************
* TGrid & grid: tableau correspondant à la grille           *
* int &num: numero du niveau actuel                         *
* State &state: statut du programme                         *
* levelMax: entier correspondant au nombre max de niveau    *
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
