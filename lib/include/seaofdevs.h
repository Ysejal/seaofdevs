#ifndef _H_SEAOFDEVS_
#define _H_SEAOFDEVS_

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <ctype.h>

#define BUFFER 256

typedef struct game_s game_t;
typedef struct ship_s ship_t;

/**
 * @brief Structure qui caracterise une partie de Sea Of Devs
 * 
 * int nbJoueurs : Nombre de joueurs dans la partie
 * int Cmax      : Valeurs initiales de la Coque
 * int Kmax      : Valeurs initiales du Kerosene
 * int nbTours   : Le nombre de tours max
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

/**
 * @brief Structure qui represente un navire
 * 
 */
struct ship_s
{
    int id;
    int x, y;
    int coque;
    int kerosene;
};

#endif