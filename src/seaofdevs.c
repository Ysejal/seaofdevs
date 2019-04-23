#include "../lib/include/seaofdevs.h"
#include "../lib/include/file.h"
#include "../lib/include/board.h"
#include "../lib/include/action.h"

void *playerjob(void *arg)
{
    ship_t *ship = (ship_t *)arg;
    printf("[\x1b[33mPlayer\x1b[0m] : ship #%d %dC %dK at (%d;%d) \n", ship->id, ship->coque, ship->kerosene, ship->coord.x, ship->coord.y);
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

    /* Initialize and set thread detached attribute */
    for (i = 0; i < game_info.nbJoueurs; i++)
    {
        /* Initialize Default Sihp */
        ships[i].id = i;
        ships[i].coque = game_info.Cmax;
        ships[i].kerosene = game_info.Kmax;
        ships[i].coord = sod_map->shipPosition[i];
        /* Initialize Pipe */
        pipe(toPlayer[i].fd);
        pipe(toServer[i].fd);
        pthread_create(&players[i], NULL, playerjob, (void *)&ships[i]);
    }

    /* Free attribute and wait for the other threads */
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
