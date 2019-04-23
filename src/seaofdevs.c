#include "../lib/include/seaofdevs.h"
#include "../lib/include/file.h"
#include "../lib/include/board.h"
#include "../lib/include/action.h"

void *playerjob(void *arg)
{
    ship_t *ship = (ship_t *)arg;
    printf("[\x1b[33mPlayer\x1b[0m] : ship #%ld %dC %dK at (%d;%d) \n", ship->id, ship->coque, ship->kerosene, ship->coord.x, ship->coord.y);
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

    int rc;
    void *status;
    long t;

    printf("[\x1b[32mServer\x1b[0m] : welcome to the sea of devs !\n");

    /* File Parse */
    fichier = open_file(argv[1], O_RDONLY);
    printf("[\x1b[32mServer\x1b[0m] : reading %s\n", argv[1]);
    game_info = read_game_info(fichier);

    /* Navalmap */
    map_t map = getmap_t(game_info);
    coord_t size_map = getcoord_t(game_info);
    sod_map = init_navalmap(map, size_map, game_info.nbJoueurs);

    /* Place ships */
    placeRemainingShipsAtRandom(sod_map);

    /* Draw Navalmap */
    draw_navalmap(sod_map);

    /* Threads */
    pthread_t players[game_info.nbJoueurs];
    pthread_attr_t attr;

    ship_t ships[game_info.nbJoueurs];

    /* Initialize and set thread detached attribute */
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    for (t = 0; t < game_info.nbJoueurs; t++)
    {
        /* Initialize Default Sihp */
        ships[t].id = t;
        ships[t].coque = game_info.Cmax;
        ships[t].kerosene = game_info.Kmax;
        ships[t].coord = sod_map->shipPosition[t];
        printf("[\x1b[32mServer\x1b[0m] : initialize ship #%ld\n", ships[t].id);
        rc = pthread_create(&players[t], &attr, playerjob, (void *)&ships[t]);
        if (rc)
        {
            printf("[\x1b[31mError\x1b[0m] : return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    /* Debug */
    /* Test Radar */
    s_radar_scn(&ships[0], sod_map);

    /* Free attribute and wait for the other threads */
    pthread_attr_destroy(&attr);
    for (t = 0; t < game_info.nbJoueurs; t++)
    {
        rc = pthread_join(players[t], &status);
        if (rc)
        {
            printf("[\x1b[31mError\x1b[0m] : return code from pthread_join() is %d\n", rc);
            exit(EXIT_FAILURE);
        }
        printf("[\x1b[32mServer\x1b[0m] : completed join with ship #%ld having a status of %ld\n", ships[t].id, (long)status);
    }

    /* End Routines */
    free_navalmap(sod_map);
    close_file(fichier);
    printf("[\x1b[32mServer\x1b[0m] : program completed. Exiting.\n");
    pthread_exit(NULL);
    return 0;
}
