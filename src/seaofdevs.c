#include "../lib/include/seaofdevs.h"
#include "../lib/include/file.h"
#include "../lib/include/navalmap.h"
#include "../lib/include/board.h"

void *shipjob(void *arg)
{
    long tid;
    tid = (long)arg;
    printf("[\x1b[33mPlayer\x1b[0m] : ship id #%ld\n", tid);
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
    long t;
    void *status;

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
    pthread_t ships[game_info.nbJoueurs];
    pthread_attr_t attr;

    /* Initialize and set thread detached attribute */
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    for (t = 0; t < game_info.nbJoueurs; t++)
    {
        printf("[\x1b[32mServer\x1b[0m] : initialize ship #%ld\n", t);
        rc = pthread_create(&ships[t], &attr, shipjob, (void *)t);
        if (rc)
        {
            printf("[\x1b[31mError\x1b[0m] : return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    /* Free attribute and wait for the other threads */
    pthread_attr_destroy(&attr);
    for (t = 0; t < game_info.nbJoueurs; t++)
    {
        rc = pthread_join(ships[t], &status);
        if (rc)
        {
            printf("[\x1b[31mError\x1b[0m] : return code from pthread_join() is %d\n", rc);
            exit(-1);
        }
        printf("[\x1b[32mServer\x1b[0m] : completed join with ship #%ld having a status of %ld\n", t, (long)status);
    }

    /* End Routines */
    free_navalmap(sod_map);
    close_file(fichier);
    pthread_exit(NULL);
    return 0;
}
