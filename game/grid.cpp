#include "grid.h"

TGrid grid;

SDL_Surface *surf_background;
SDL_Surface *surf_haut;
SDL_Surface *surf_bas;
SDL_Surface *surf_gauche;
SDL_Surface *surf_droite;
SDL_Surface *surf_dormeur;
SDL_Surface *surf_glacon;
SDL_Surface *surf_monstre;
SDL_Surface *surf_livre;
SDL_Surface *surf_menu;
SDL_Surface *surf_win;
SDL_Surface *surf_winEnd;

void loadSurfaces() {
    surf_background = loadImage("assets/background.bmp");
    surf_haut = loadImageWithColorKey("assets/haut.png", 0, 255, 255);
    surf_bas = loadImageWithColorKey("assets/bas.png", 0, 255, 255);
    surf_gauche = loadImageWithColorKey("assets/gauche.png", 0, 255, 255);
    surf_droite = loadImageWithColorKey("assets/droite.png", 0, 255, 255);
    surf_dormeur = loadImageWithColorKey("assets/dormeur.png", 0, 255, 255);
    surf_glacon = loadImageWithColorKey("assets/glacon.png", 0, 255, 255);
    surf_monstre = loadImageWithColorKey("assets/monstre.png", 0, 255, 255);
    surf_livre = loadImageWithColorKey("assets/livre.png", 0, 255, 255);
    surf_menu = loadImage("assets/menuetedit.bmp");
    surf_win = loadImage("assets/winSprite.bmp");
    surf_winEnd = loadImage("assets/winEndSprite.bmp");
}

void freeSurfaces() {
    SDL_FreeSurface(surf_background);
    SDL_FreeSurface(surf_haut);
    SDL_FreeSurface(surf_bas);
    SDL_FreeSurface(surf_gauche);
    SDL_FreeSurface(surf_droite);
    SDL_FreeSurface(surf_dormeur);
    SDL_FreeSurface(surf_glacon);
    SDL_FreeSurface(surf_monstre);
    SDL_FreeSurface(surf_livre);
    SDL_FreeSurface(surf_menu);
    SDL_FreeSurface(surf_win);
    SDL_FreeSurface(surf_winEnd);
}

void coordsToPixels(int coordX, int coordY, int & x, int & y) {
    x = MARGIN_LEFT + coordX * CASE_WIDTH;
    y = MARGIN_TOP + coordY * CASE_HEIGHT;
}

void pixelsToCoords(int x, int y, int & coordX, int & coordY) {
    if (x - MARGIN_LEFT < 0 || x > MARGIN_LEFT + WIDTH * CASE_WIDTH || y - MARGIN_TOP < 0 || y > MARGIN_TOP + HEIGHT * CASE_HEIGHT) {
        coordX = -1;
        coordY = -1;
    } else {
        coordX = (x - MARGIN_LEFT) / CASE_WIDTH;
        coordY = (y - MARGIN_TOP) / CASE_HEIGHT;
    }
}

Direction coordToDirection(int x,int y){

    Direction dirCase;

    switch(grid[x][y].type) {
    case 5:
        dirCase = UP;
        break;
    case 6:
        dirCase = DOWN;
        break;
    case 7:
        dirCase = RIGHT;
        break;
    case 8:
        dirCase = LEFT;
        break;
    default:
        dirCase = NONE;
        break;
    }
    return dirCase;

}

void initGrid() {
    for (int xCoord = 0; xCoord < WIDTH; xCoord++) {
        for (int yCoord = 0; yCoord < HEIGHT; yCoord++) {
            grid[xCoord][yCoord].type = 0;
            grid[xCoord][yCoord].direction = NONE;
        }
    }
}

void draw(SDL_Surface *s) {
    int x = -1;
    int y = -1;

    for(int i = 0; i < WIDTH; i++) {
        for(int j = 0; j < HEIGHT; j++) {

            coordsToPixels(i, j, x, y);   //on récupère la position en pixel de la case selectionnée

            switch (grid[i][j].type) {

            case 1 :
                applySurface(x,y,surf_monstre,s,NULL);
                break;
            case 2:
                applySurface(x,y-14,surf_glacon,s,NULL);
                break;
            case 3:
                applySurface(x,y-14,surf_livre,s,NULL);
                break;
            case 4:
                applySurface(x,y-10,surf_dormeur,s,NULL);
                break;
            case 5:
                applySurface(x+5,y+5,surf_haut,s,NULL);
                break;
            case 6:
                applySurface(x+5,y+5,surf_bas,s,NULL);
                break;
            case 7:
                applySurface(x+5,y+5,surf_droite,s,NULL);
                break;
            case 8:
                applySurface(x+5,y+5,surf_gauche,s,NULL);
                break;
            }
        }
    }
}

void readLevel(int currentLevel) {

    std::string lvl;
    int a ;
    int x = 0;
    int y = 0;

    lvl = "levels/niveaux" + std::to_string(currentLevel) + ".txt";

    std::ifstream monFlux(lvl);  //Ouverture d'un fichier en lecture

    if(monFlux)
    {
        while(!monFlux.eof()) //On lit une ligne complète
        {
            monFlux >> a;
            if(a < 5) {
                grid[x][y].type = a;
            } else {
                switch(a){

                case 5:
                   grid[x][y].direction = UP;
                    break;
                case 6:
                    grid[x][y].direction = DOWN;
                    break;
                case 7:
                    grid[x][y].direction = RIGHT;
                    break;
                case 8:
                    grid[x][y].direction = LEFT;
                    break;
                }
            }

            if( y+1  < HEIGHT ) {
                y++;
            } else {
                y = 0;
                x++;
            }
        }
    }else{
        std::cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." <<  std::endl;
    }
    monFlux.close();
}

void saveLevel(int currentLevel) {

    int type;

    std::string lvl;
    lvl = "levels/niveaux" + std::to_string(currentLevel) + ".txt";

    std::ofstream fichier(lvl,  std::ios::out |  std::ios::trunc);

    if(fichier){

        for(int i = 0; i < WIDTH; i++) {
            for(int j = 0; j < HEIGHT; j++) {
                type = grid[i][j].type;
                fichier << type << std::endl;
            }
        }
        fichier.close();
    }else{
        std::cout << "ERREUR: Impossible d'ouvrir le fichier en ecriture." << std::endl;
    }
}

void checkEditorEvent(SDL_Event &event, int &choix) {

    Uint8 *keystates = SDL_GetKeyState( NULL );
    Uint8 mousestates = SDL_GetMouseState(NULL,NULL);

    int sourisX = event.button.x;
    int sourisY = event.button.y;

    int x = -1;
    int y = -1;

    pixelsToCoords(sourisX, sourisY, x, y);

    if(keystates[SDLK_a]){
        choix = 1;
    }
    if(keystates[SDLK_z]){
        choix = 2;
    }
    if(keystates[SDLK_e]){
        choix = 3;
    }
    if(keystates[SDLK_r]){
        choix = 4;
    }
    if(keystates[SDLK_UP]){
        choix = 5;
    }
    if(keystates[SDLK_DOWN]){
        choix = 6;
    }
    if(keystates[SDLK_RIGHT]){
        choix = 7;
    }
    if(keystates[SDLK_LEFT]){
        choix = 8;
    }

    if(mousestates & SDL_BUTTON_LEFT){
        grid[x][y].type = choix;
    }else if(mousestates & SDL_BUTTON_RMASK){
        grid[x][y].type = 0;
    }

}

void drawCursor(SDL_Surface *s,SDL_Event &event, int choix){

    int sourisX = event.button.x;
    int sourisY = event.button.y;

    if((sourisX && sourisY) != 0){
        switch (choix){

        case 1 :
            applySurface(sourisX,sourisY,surf_monstre,s,NULL);
            break;
        case 2:
            applySurface(sourisX,sourisY,surf_glacon,s,NULL);
            break;
        case 3:
            applySurface(sourisX,sourisY,surf_livre,s,NULL);
            break;
        case 4:
            applySurface(sourisX,sourisY,surf_dormeur,s,NULL);
            break;
        case 5:
            applySurface(sourisX,sourisY,surf_haut,s,NULL);
            break;
        case 6:
            applySurface(sourisX,sourisY,surf_bas,s,NULL);
            break;
        case 7:
            applySurface(sourisX,sourisY,surf_droite,s,NULL);
            break;
        case 8:
            applySurface(sourisX,sourisY,surf_gauche,s,NULL);
            break;
        }
    }
}

bool isOnLevel(int mouseX, int mouseY, int buttonX, int buttonY){

    int dx = mouseX - buttonX, dy = mouseY - buttonY;
    return dx * dx + dy * dy <= 25 * 25;
}

void levelSelect(int mouseX, int mouseY, int &currentLevel) {
    int cpt = 1; //62 160 25
    int i = 0;
    int j = 0;

    currentLevel = -1;

    while(currentLevel == -1 && j < 5 && i < 3){
        if(isOnLevel(mouseX, mouseY, 62 + i*90, 160 + j*80))
            currentLevel = cpt;
        if( i+1 < 3 ){
            i++;
        } else {
            j++;
            i = 0;
        }

        cpt++;
    }
    readLevel(currentLevel);
}


bool sortie(int x, int y, Direction &direction){

    bool sortie = false;

    if(direction == LEFT && x == 0){
        sortie = true;
    }
    if(direction == RIGHT && x == WIDTH-1){
        sortie = true;
    }

    if(direction == UP && y == 0){
        sortie = true;
    }

    if(direction == DOWN && y == HEIGHT-1){
        sortie = true;
    }

    return sortie;
}

void collisionWith(int x, int y){
    switch(grid[x][y].type){
    case 2:
        grid[x][y].type = 0;
        break;
    case 4:
        grid[x][y].type = 1;
        break;
    }
}

void moveP(int x,int y,Direction &direction, SDL_Surface *s, int num){

    int i;
    int j;

    coordsToPixels(x, y, i, j);

    int caseFinalx = x;
    int caseFinaly = y;

    int coordCaseFinalx = 0;
    int coordCaseFinaly = 0;

    int delay = 1; // Changer la vitesse de l'animation ici

    int nextCaseObject;
    Direction caseDir;

    if(direction == RIGHT){

        bool stop = false;
        int dx = 0;
        while (!stop) {
            nextCaseObject = grid[x + dx + 1][y].type;
            caseDir = grid[x + dx][y].direction;
            if ((caseDir != NONE && caseDir != RIGHT) || ( nextCaseObject != 0 && nextCaseObject < 5)  || x + dx == WIDTH - 1)
                stop = true;
            else dx++;
        }
        caseFinalx += dx;

        grid[x][y].type = 0;
        coordsToPixels(caseFinalx, caseFinaly, coordCaseFinalx, coordCaseFinaly);

        while(i < coordCaseFinalx){
            i++;
            setScreenBackground(s,surf_background);
            draw(s);
            applySurface(i,j,surf_monstre,s,NULL);
            SDL_Flip(s);
            SDL_Delay(delay);
        }

        grid[caseFinalx][caseFinaly].type = 1;
    }

    if(direction == DOWN){

        bool stop = false;
        int dy = 0;
        while (!stop) {
            nextCaseObject = grid[x][y + dy + 1].type;
            caseDir = grid[x][y + dy].direction;
            if ((caseDir != NONE && caseDir != DOWN) || ( nextCaseObject != 0 && nextCaseObject < 5) || y + dy == HEIGHT - 1)
                stop = true;
            else dy++;
        }
        caseFinaly += dy;

        grid[x][y].type = 0;
        coordsToPixels(caseFinalx, caseFinaly, coordCaseFinalx, coordCaseFinaly);

        while(j < coordCaseFinaly){
            j++;
            setScreenBackground(s,surf_background);
            draw(s);
            applySurface(i,j,surf_monstre,s,NULL);
            SDL_Flip(s);
            SDL_Delay(delay);
        }
        grid[caseFinalx][caseFinaly].type = 1;


    }

    if(direction == UP){

        bool stop = false;
        int dy = 0;
        while (!stop) {
            nextCaseObject = grid[x][y - dy - 1].type;
            caseDir = grid[x][y - dy].direction;
            if ((caseDir != NONE && caseDir != UP) || ( nextCaseObject != 0 && nextCaseObject < 5) || y - dy == 0)
                stop = true;
            else dy++;
        }
        caseFinaly -= dy;

        grid[x][y].type = 0;
        coordsToPixels(caseFinalx, caseFinaly, coordCaseFinalx, coordCaseFinaly);


        while(j > coordCaseFinaly){
            j--;
            setScreenBackground(s,surf_background);
            draw(s);
            applySurface(i,j,surf_monstre,s,NULL);
            SDL_Flip(s);
            SDL_Delay(delay);

        }

        grid[caseFinalx][caseFinaly].type = 1;


    }

    if(direction == LEFT){

        bool stop = false;
        int dx = 0;
        while (!stop) {
            nextCaseObject = grid[x - dx - 1][y].type;
            caseDir = grid [x - dx][y].direction;
            if ((caseDir != NONE && caseDir != LEFT) || ( nextCaseObject != 0 && nextCaseObject < 5) || x - dx == 0)
                stop = true;
            else dx++;
        }
        caseFinalx -= dx;

        grid[x][y].type = 0;
        coordsToPixels(caseFinalx, caseFinaly, coordCaseFinalx, coordCaseFinaly);

        while(i > coordCaseFinalx){
            i--;
            setScreenBackground(s,surf_background);
            draw(s);
            applySurface(i,j,surf_monstre,s,NULL);
            SDL_Flip(s);
            SDL_Delay(delay);
        }
        grid[caseFinalx][caseFinaly].type = 1;
    }

    /***********************************************************************************
 ******** evenement après deplacement du monstre
 ********************************************************************************/
    Direction dir = caseDir;
    if (dir != NONE) {
        moveP(caseFinalx, caseFinaly, dir, s, num);
    } else if(sortie(caseFinalx,caseFinaly,direction)==true) {
        initGrid();
        readLevel(num);
    } else {
        int colWithX = 0;
        int colWithY = 0;

        switch(direction){
        case RIGHT :
            colWithX = caseFinalx+1;
            colWithY = caseFinaly;
            collisionWith(colWithX,colWithY);
            setScreenBackground(s,surf_background);
            draw(s);
            SDL_Flip(s);
            break;
        case LEFT :
            colWithX = caseFinalx-1;
            colWithY = caseFinaly;
            collisionWith(colWithX,colWithY);
            setScreenBackground(s,surf_background);
            draw(s);
            SDL_Flip(s);
            break;
        case UP :
            colWithX = caseFinalx;
            colWithY = caseFinaly-1;
            collisionWith(colWithX,colWithY);
            setScreenBackground(s,surf_background);
            draw(s);
            SDL_Flip(s);
            break;
        case DOWN :
            colWithX = caseFinalx;
            colWithY = caseFinaly+1;
            collisionWith(colWithX,colWithY);
            setScreenBackground(s,surf_background);
            draw(s);
            SDL_Flip(s);
            break;
        }
    }
    direction = NONE;
}


Direction mouvement (SDL_Event &event, Direction &direction, SDL_Surface *s, int mouseXcoord, int mouseYcoord, int currentLvl){

    int caseDirectionY = 0;
    int caseDirectionX = 0;

    Uint8 mousestates;
    int sourisX;
    int sourisY;

    if(grid[mouseXcoord][mouseYcoord].type == 1 && event.button.button == SDL_BUTTON_LEFT){

        while(event.button.button == SDL_BUTTON_LEFT){

            SDL_PollEvent(&event);
            mousestates = SDL_GetMouseState(NULL,NULL);
            sourisX = event.button.x;
            sourisY = event.button.y;

            pixelsToCoords(event.button.x, event.button.y, caseDirectionX, caseDirectionY);


            if(caseDirectionX == mouseXcoord && caseDirectionY < mouseYcoord){
                direction = UP;
            }
            if(caseDirectionX == mouseXcoord && caseDirectionY > mouseYcoord){
                direction = DOWN;
            }
            if(caseDirectionX > mouseXcoord && caseDirectionY == mouseYcoord){
                direction = RIGHT;
            }
            if(caseDirectionX < mouseXcoord && caseDirectionY == mouseYcoord){
                direction = LEFT;
            }
            if(caseDirectionX == mouseXcoord && caseDirectionY == mouseYcoord){
                direction = NONE;
            }
        }
    }

    while(direction !=NONE){
        moveP(mouseXcoord,mouseYcoord,direction,s,currentLvl);
    }

    return direction;
}

bool checkWin(){
    bool win = true;
    int i = 0;
    int j = 0;

    while (win == true && i<HEIGHT) {
        j = 0;
        while (win == true && j<WIDTH){
            if (grid[j][i].type == 4){
                win = false;
            }
            j++;
        }
        i++;
    }
    return win;
}

void levelWin(SDL_Surface *s,int &num, int &state ){
    if(checkWin() == 1 && num<6){
        SDL_Delay(500);
        setScreenBackground(s,surf_win);
        SDL_Flip(s);
        SDL_Delay(1500);

        num++;

        initGrid();
        readLevel(num);

    }else if(checkWin() == 1 && num==6){
        setScreenBackground(s,surf_winEnd);
        SDL_Flip(s);
        SDL_Delay(3000);
        state = 0;
    }
}
