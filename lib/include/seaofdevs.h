#ifndef _H_SEAOFDEVS_
#define _H_SEAOFDEVS_

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

typedef struct map_s map_t;
typedef struct game_s game_t;

/**
 * @brief Structure qui definit une carte de Sea Of Devs.
 * 
 * char *typeCarte : Type de la carte.
 * int tailleX     : Largeur de la carte.
 * int tailleY     : Hauteur de la carte.
 */
struct map_s
{
    char *typeCarte;
    int tailleX;
    int tailleY;
};

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
    int nbJoueurs;
    int Cmax;
    int Kmax;
    int nbTours;
};

#endif