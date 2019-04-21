#include "../lib/include/seaofdevs.h"
#include "../lib/include/file.h"
#include "../lib/include/navalmap.h"
#include "../lib/include/board.h"

void *shipjob(void *arg)
{
    long tid;
    tid = (long)arg;
    printf("[Player] : shipid #%ld!\n", tid);
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

    /* File Parse */
    fichier = open_file(argv[1], O_RDONLY);
    game_info = read_game_info(fichier);

    /* Navalmap */
    map_t map = getmap_t(game_info);
    coord_t size_map = getcoord_t(game_info);
    sod_map = init_navalmap(map, size_map, game_info.nbJoueurs);

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
        printf("[Server] : init ship #%ld\n", t);
        rc = pthread_create(&ships[t], &attr, shipjob, (void *)t);
        if (rc)
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
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
            printf("ERROR; return code from pthread_join() is %d\n", rc);
            exit(-1);
        }
        printf("[Server] : completed join with player %ld having a status of %ld\n", t, (long)status);
    }

    /* End Routines */
    free_navalmap(sod_map);
    close_file(fichier);
    pthread_exit(NULL);
    return 0;
}
