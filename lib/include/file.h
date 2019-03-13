#ifndef _H_FILE_
#define _H_FILE_

typedef struct file_s file_t;

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

#endif