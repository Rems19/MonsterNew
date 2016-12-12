#include "grid.h"

/****************** Nom de la fonction **********************
* coordsToPixels                                            *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Permet de convertir les coordonnées par rapport à la      *
* grille en coordonnées par rapport à la fenêtre en faisant *
* un passage par référence                                  *
*********************** Entrées *****************************
* int coordX int coordY: coordonnées par rapport à la grille*
* int & x, int & y: coordonnées par rapport à la fenêtre    *
*********************** Sorties *****************************
* ne retourne rien (référence)                              *
************************************************************/
void coordsToPixels(int coordX, int coordY, int & x, int & y) {
    x = MARGIN_LEFT + coordX * CASE_WIDTH;
    y = MARGIN_TOP + coordY * CASE_HEIGHT;
}

/****************** Nom de la fonction **********************
*  pixelsToCoords                                           *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Permet de convertir les coordonnées par rapport à la      *
* fenêtre en coordonnées par rapport à la grille en faisant *
* un passage par référence                                  *
* -1 est affecté si le curseur n'est pas sur la grille      *
*********************** Entrées *****************************
* int x, int y: coordonnées par rapport à la fenêtre        *
* int &coordX int &coordY: coordonnées par rapport à la grille
*********************** Sorties *****************************
* ne retourne rien (référence)                              *
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
* initGrid                                                  *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Permet d'initialiser les valeurs d'une grille passée en   *
* référence en la remplissant de case vide                  *
*********************** Entrées *****************************
* TGrid & grid: tableau de type Tgrid par référence         *
*********************** Sorties *****************************
* ne retourne rien (référence)                              *
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
* draw                                                      *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Permet de charger l'affichage des éléments de la grille   *
* dans la mémoire tampon en passant une surface par référence
*********************** Entrées *****************************
* TGrid & grid: tableau de type Tgrid(grille)               *
* SDL_Surface *s: pointeur vers surface de notre fenêtre    *
*********************** Sorties *****************************
*   ne retourne rien (référence)                            *
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
                applySurface(x-2 , y - 8, surf_glacon, s, NULL);
                break;
            case BOOK:
                applySurface(x, y - 14, surf_livre, s, NULL);
                break;
            case SLEEPER:
                applySurface(x, y - 10, surf_dormeur, s, NULL);
                break;
            default:
                break;
            }
        }
    }
}

/****************** Nom de la fonction **********************
* loadLevel                                                 *
******************** Auteur , Dates *************************
* Nom/Date : Éventuellement la version                      *
********************* Description ***************************
* Permet de charger un niveau à partir d'un fichier texte   *
* correspondant à un entier passé en paramètre              *
*********************** Entrées *****************************
*  TGrid & grid: tableau de type Tgrid par référence        *
* currentLevel: entier correspondant au niveau à charger    *
*********************** Sorties *****************************
* ne retourne rien (référence)              *
************************************************************/
void loadLevel(TGrid & grid, int currentLevel) {

    std::string lvl;
    CaseType caseType;
    Direction direction;
    int type;
    int dir;
    int x = 0;
    int y = 0;

    lvl = "levels/niveaux" + std::to_string(currentLevel) + ".txt";

    std::ifstream monFlux(lvl);  //Ouverture d'un fichier en lecture

    if(monFlux) {
        while(!monFlux.eof()) {
            monFlux >> type;
            monFlux >> dir;

            caseType = (CaseType) type;
            direction = (Direction) dir;

            grid[x][y].type = caseType;
            grid[x][y].direction = direction;


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
int collisionWith(TGrid & grid, int x, int y) {

    int col = 0;

    switch(grid[x][y].type) {
    case ICE:

        grid[x][y].type = EMPTY;
        col = 1;
        break;

    case SLEEPER:
        grid[x][y].type = MONSTER;
        col = 2;
        break;

    default: break;
    }

    return col;

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

    int i;
    int j;

    coordsToPixels(x, y, i, j);

    int caseFinalx = x;
    int caseFinaly = y;

    int coordCaseFinalx = 0;
    int coordCaseFinaly = 0;

    int delay = 2; // Changer la vitesse de l'animation ici

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

        if(dx == 0 && grid[x][y].direction != NONE) {
            caseDir = NONE;    //si on est bloqué par un obstacle et que l'on reste sur place
        }

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

        if(dy == 0 && grid[x][y].direction != NONE) {
            caseDir = NONE;    //si on est bloqué par un obstacle et que l'on reste sur place
        }

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

        if(dy == 0 && grid[x][y].direction != NONE) {
            caseDir = NONE;    //si on est bloqué par un obstacle et que l'on reste sur place
        }

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

        if(dx == 0 && grid[x][y].direction != NONE) {
            caseDir = NONE;    //si on est bloqué par un obstacle et que l'on reste sur place
        }

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
    bool collision = false;

    if (dir != NONE) {      // si la case sur laquelle on est une direction on la modifie
        direction = dir;
    }

    if(sortie(caseFinalx,caseFinaly,direction) == true) {
        initGrid(grid);
        loadLevel(grid, num);
    } else {
        int colWithX = 0;
        int colWithY = 0;

        switch(direction){
        case RIGHT :
            colWithX = caseFinalx+1;
            colWithY = caseFinaly;
            collision = collisionWith(grid, colWithX,colWithY);
            setScreenBackground(s,surf_background);
            draw(grid, s);
            SDL_Flip(s);
            break;
        case LEFT :
            colWithX = caseFinalx-1;
            colWithY = caseFinaly;
            collision = collisionWith(grid, colWithX,colWithY);
            setScreenBackground(s,surf_background);
            draw(grid, s);
            SDL_Flip(s);
            break;
        case UP :
            colWithX = caseFinalx;
            colWithY = caseFinaly-1;
            collision = collisionWith(grid, colWithX,colWithY);
            setScreenBackground(s,surf_background);
            draw(grid, s);
            SDL_Flip(s);
            break;
        case DOWN :
            colWithX = caseFinalx;
            colWithY = caseFinaly+1;
            collision = collisionWith(grid, colWithX,colWithY);
            setScreenBackground(s,surf_background);
            draw(grid, s);
            SDL_Flip(s);
            break;
        default:
            break;
        }
        if(collision) SDL_Delay(200);

        if (dir != NONE){
            moveMonster(grid, caseFinalx, caseFinaly, direction, s, num);
        } else {
            checkColAroundMonster(grid, caseFinalx, caseFinaly);
        }
    }

    direction = NONE;
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

