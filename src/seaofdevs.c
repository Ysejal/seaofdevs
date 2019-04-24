#include "../lib/include/seaofdevs.h"
#include "../lib/include/file.h"
#include "../lib/include/board.h"
#include "../lib/include/action.h"

void *playerjob(void *arg)
{
    pipe_t *info = (pipe_t *)arg;
    message_t actions;
    actions.action = SCN;
    write(info->fd[1], &actions, sizeof(struct message_s));
    pthread_exit(NULL);
}

int main(int argc, char **argv)
{
    /* Seed */
    srand(time(NULL));
    initNavalMapLib();

    /* Variables */
    file_t fichier;
    game_t game_info;
    navalmap_t *sod_map = NULL;
    int i;

    printf("[\x1b[32mServer\x1b[0m] : welcome to the sea of devs !\n");

    /* File Parse */
    fichier = open_file(argv[1], O_RDONLY);
    printf("[\x1b[32mServer\x1b[0m] : reading %s\n", argv[1]);
    game_info = read_game_info(fichier);

    /* Tubes pour chaque Joueurs */
    pipe_t *toPlayer = malloc(sizeof(struct pipe_s) * game_info.nbJoueurs);
    pipe_t *toServer = malloc(sizeof(struct pipe_s) * game_info.nbJoueurs);

    /* Les messages que chaque thread va communiquer */
    message_t actions[game_info.nbJoueurs];

    /* Navalmap */
    map_t map = getmap_t(game_info);
    coord_t size_map = getcoord_t(game_info);
    sod_map = init_navalmap(map, size_map, game_info.nbJoueurs);

    /* Place ships */
    sod_map->initEntityMap(sod_map);
    placeRemainingShipsAtRandom(sod_map);

    /* Draw Navalmap */
    draw_navalmap(sod_map);

    /* Threads */
    pthread_t players[game_info.nbJoueurs];

    /* Navires */
    ship_t ships[game_info.nbJoueurs];

    /* Initialize thread */
    for (i = 0; i < game_info.nbJoueurs; i++)
    {
        /* Initialize Default Ship */
        ships[i].id = i;
        ships[i].coque = game_info.Cmax;
        ships[i].kerosene = game_info.Kmax;
        ships[i].coord = sod_map->shipPosition[i];
        /* Initialize Pipe */
        pipe(toPlayer[i].fd);
        pipe(toServer[i].fd);
        pthread_create(&players[i], NULL, playerjob, (void *)&toServer);
        printf("[\x1b[32mServer\x1b[0m] : Initialize ship #%d with %dC %dK at (%d;%d)\n", ships[i].id, ships[i].coque, ships[i].kerosene, ships[i].coord.x, ships[i].coord.y);
    }

    for (int tour = 1; tour <= game_info.nbTours; tour++)
    {
        for (int p = 0; p < game_info.nbJoueurs; p++)
        {
            read(toServer[p].fd[0], actions, sizeof(struct message_s) * game_info.nbJoueurs);
            printf("[\x1b[32mServer\x1b[0m] : turn %d/%d\n", tour, game_info.nbTours);
        }
    }

    /* Wait for the other threads */
    for (i = 0; i < game_info.nbJoueurs; i++)
    {
        pthread_join(players[i], NULL);
        printf("[\x1b[32mServer\x1b[0m] : completed join with ship #%d\n", ships[i].id);
    }

    /* End Routines */
    free_navalmap(sod_map);
    close_file(fichier);
    printf("[\x1b[32mServer\x1b[0m] : program completed. Exiting.\n");
    return 0;
}
