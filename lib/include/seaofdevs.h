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
#include <math.h>
#include <stdbool.h>

#include "navalmap.h"

#define BUFFER 256

typedef struct game_s game_t;
typedef struct ship_s ship_t;
typedef struct pipe_s pipe_t;
typedef struct message_s message_t;

typedef enum action action_t;
typedef enum direction direction_t;

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

struct ship_s
{
    int id;
    coord_t coord;
    int coque;
    int kerosene;
};

struct pipe_s
{
    int fd[2];
};

enum action
{
    ATK,
    MOV,
    SCN,
    NONE
};

enum direction
{
    HAUT,
    BAS,
    DROITE,
    GAUCHE
};

struct message_s
{
    pthread_mutex_t mutex; //protéger des données partagées de modifications concurrentes et pour implémenter des sections critiques.
    pthread_cond_t cond;   //permet à un thread de suspendre son exécution juqu'à ce qu'une certaine condition (un prédicat) sur des données partagées soit vérifiée
    action_t action;       //action a traansmettre
    coord_t position;      //changement de position effectue
};

#endif