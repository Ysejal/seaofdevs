#include "../lib/include/seaofdevs.h"
#include "../lib/include/file.h"
/**
 * @brief 
 * 
 * @param chemin 
 * @param acces 
 * @return file_t 
 */
file_t open_file(const char *chemin, int acces)
{
    file_t file_1;

    file_1.dir = chemin;
    file_1.acces = acces;

    if ((file_1.descriptor = open(chemin, acces)) == -1)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    return file_1;
}

game_t read_game_info(file_t f)
{
    game_t game_info;
    char buffer[BUFFER];

    read(f.descriptor, buffer, sizeof(buffer));

    char *typeCarte = strtok(buffer, ";");

    char *tailleX = strtok(NULL, ";");
    char *tailleY = strtok(NULL, "\n");

    char *nbJoueurs = strtok(NULL, ";");
    char *Cmax = strtok(NULL, ";");
    char *Kmax = strtok(NULL, ";");
    char *nbTours = strtok(NULL, "\0");

    game_info.typeCarte = typeCarte;
    game_info.tailleX = atoi(tailleX);
    game_info.tailleY = atoi(tailleY);
    game_info.nbJoueurs = atoi(nbJoueurs);
    game_info.Cmax = atoi(Cmax);
    game_info.Kmax = atoi(Kmax);
    game_info.nbTours = atoi(nbTours);

    return game_info;
}

int close_file(file_t file)
{
    return close(file.descriptor);
}
