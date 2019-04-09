#ifndef _H_SEAOFDEVS_
#define _H_SEAOFDEVS_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <ncurses.h>

#define BUFFER 256

typedef struct game_s game_t;

/**
 * @brief Structure qui caracterise une partie de Sea Of Devs.
 * 
 * int nbJoueurs : Nombre de joueurs dans la partie.
 * int Cmax      : Valeurs initiales de la Coque.
 * int Kmax      : Valeurs initiales du Kerosene.
 * int nbTours   : Le nombre de touts maximum joues.
 */
struct game_s
{
    char *typeCarte;
    int tailleX;
    int tailleY;
    int nbJoueurs;
    int Cmax;
    int Kmax;
    int nbTours;
};

#endif