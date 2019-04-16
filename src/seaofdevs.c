#include "../lib/include/seaofdevs.h"
#include "../lib/include/file.h"
#include "../lib/include/navalmap.h"
#include "../lib/include/board.h"

/**
 * @brief Fonction de creation de processus Joueurs
 * 
 * @param nbJoueurs 
 */
void fork_ship(navalmap_t *nm, int nbJoueurs)
{
    /* Les Joueurs */
    for (int i = 0; i < nbJoueurs; i++)
    {
        if (fork() == 0)
        {
            printf("[ship id : %d] pid %d from [server] pid %d\n", i, getpid(), getppid());
            exit(0);
        }
    }
    /* Le serveur */
    for (int i = 0; i < nbJoueurs; i++)
        wait(NULL);
}

int main(int argc, char **argv)
{
    srand(time(NULL));

    file_t fichier;
    game_t game_info;
    navalmap_t *sod_map = NULL;

    fichier = open_file(argv[1], O_RDONLY);
    game_info = read_game_info(fichier);

    map_t map = getmap_t(game_info);
    coord_t size_map = getcoord_t(game_info);

    sod_map = init_navalmap(map, size_map, game_info.nbJoueurs);
    fork_ship(sod_map, game_info.nbJoueurs);

    free_navalmap(sod_map);

    close_file(fichier);
    return 0;
}
