#include "../lib/include/seaofdevs.h"

int s_radar_scn(ship_t *source, navalmap_t *nm)
{
    coord_t c;
    int min = 0;
    int res = nm->size.x * nm->size.y;
    int i;
    int shipid;

    for (i = 0; i < nm->nbShips; i++)
    {
        /* Calcule de la distance min pour chaque entité */
        if (i != source->id)
        {
            min = sqrt(pow(nm->shipPosition[i].y - source->coord.y, 2) + pow(nm->shipPosition[i].x - source->coord.x, 2));
            if (min < res)
            {
                res = min;
                c.x = nm->shipPosition[i].x;
                c.y = nm->shipPosition[i].y;
                shipid = i;
            }
        }
    }
    /* Print Info */
    printf("[\x1b[33mPlayer\x1b[0m] : le proche de ship #%ld est ship #%d en (%d;%d) avec une distance de %d\n", source->id, shipid, c.x, c.y, res);
    return res;
}