#include "sdl_funcs.h"

/****************** Nom de la fonction **********************
* initSDL()                                                 *
******************** Auteur , Dates *************************
* REMI                                                      *
********************* Description ***************************
* Permet d'initialiser tous les éléments la librairie SDL   *
*********************** Entrées *****************************
*                                                           *
*********************** Sorties *****************************
*                                                           *
************************************************************/
void initSDL() {
    SDL_Init(SDL_INIT_EVERYTHING);
}

/****************** Nom de la fonction **********************
* loadImage                                                 *
******************** Auteur , Dates *************************
* REMI                                                      *
********************* Description ***************************
* Permet de retourner l'adresse d'une image chargée         *
* à partir d'un string passé en paramètre                   *
*********************** Entrées *****************************
* std::string filename: correspond au chemin d'accès de     *
* l'image que l'on veut charger                             *
*********************** Sorties *****************************
* SDL_Surface* optimizedImage: corespond à l'adresse de     *
* de l'image que l'on a chargé                              *
************************************************************/
SDL_Surface* loadImage(std::string filename) {

    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;

    loadedImage = IMG_Load(filename.c_str());

    if (loadedImage != NULL) {
        optimizedImage = SDL_DisplayFormat(loadedImage);
        SDL_FreeSurface(loadedImage);
    }

    return optimizedImage;
}

/****************** Nom de la fonction **********************
* loadImageWithColorKey                                     *
******************** Auteur , Dates *************************
* REMI                                                      *
********************* Description ***************************
* Meme fonction que loadImage mais permet en plus de charger*
* une image en ignorant une couleur et d'ajouter un         *
* transparent                                               *
*********************** Entrées *****************************
* std::string filename: correspond au chemin d'accès de     *
*                       l'image que l'on veut charger       *
* int r, int g, int b: correspond au codage rgb pour enlever*
*                      la couleur correspondante            *
*********************** Sorties *****************************
*  SDL_Surface* optimizedImage: corespond à l'adresse de    *
* de l'image que l'on a chargé                              *
************************************************************/
SDL_Surface* loadImageWithColorKey(std::string filename, int r, int g, int b, int alpha) {

    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;

    loadedImage = IMG_Load(filename.c_str());

    if(loadedImage != NULL) {

        optimizedImage = SDL_DisplayFormat(loadedImage);
        SDL_FreeSurface(loadedImage);

        if(optimizedImage != NULL) {
            Uint32 colorkey = SDL_MapRGB(optimizedImage -> format, r, g, b);
            SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey);
            SDL_SetAlpha(optimizedImage, SDL_SRCALPHA, alpha);
        }
    }

    return optimizedImage;
}

/****************** Nom de la fonction **********************
* applySurface                                              *
******************** Auteur , Dates *************************
* REMI                                                      *
********************* Description ***************************
* Permet d'appliquer une surface source à une surface de    *
* destination en la modifiant à partir de coordonnées x et y.
* Il y a la possibilité d'appliquer uniquement une partie   *
* de la surface source grace au paramètre SDL_Rect* clip    *
*********************** Entrées *****************************
* SDL_Surface* source: pointeur vers l'image source         *
* SDL_Surface* destination: pointeur vers l'image de        *
*                           destination (ecran)             *
* int x, int y: coordonnée de l'image chargée vers la       *
*               surface de destination                      *
*********************** Sorties *****************************
*                                                           *
************************************************************/
void applySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip) {
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, clip, destination, &offset );
}
