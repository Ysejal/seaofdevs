#ifndef _H_FILE_
#define _H_FILE_

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

typedef struct file_s file_t;

/**
 * @brief 
 * 
 */
struct file_s
{
    int descriptor;
    const char *dir;
    int acces;
};

/**
 * @brief Ouverture du fichier
 * 
 * @param chemin Nom/Chemin du fichier à ouvrir
 * @param acces Accès au fichier (cf. flags de open())
 * @return file_t Structure file_t (le descripteur est mis à -1 si l'ouverture a échouée)
 */
file_t open_file(const char *chemin, int acces);

/**
 * @brief 
 * 
 * @param file 
 * @return int 
 */
int close_file(file_t file);

/**
 * @brief 
 * 
 * @param f 
 * @return ssize_t 
 */
map_t read_map(file_t f);

#endif