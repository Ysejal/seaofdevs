#include "../lib/include/seaofdevs.h"

coord_t s_radar_scn(ship_t *source, navalmap_t *nm)
{
    coord_t pos;
    int min = 0;
    int dist = nm->size.x * nm->size.y;
    int i;
    int shipid;

    for (i = 0; i < nm->nbShips; i++)
    {
        if (i != source->id)
        {
            min = sqrt(pow(nm->shipPosition[i].y - source->coord.y, 2) + pow(nm->shipPosition[i].x - source->coord.x, 2));
            if (min < dist)
            {
                dist = min;
                pos.x = nm->shipPosition[i].x;
                pos.y = nm->shipPosition[i].y;
                shipid = i;
            }
        }
    }
    printf("[\x1b[33mRadar\x1b[0m] : ship #%d is near ship #%d at (%d;%d) dist %d\n", source->id, shipid, pos.x, pos.y, dist);
    return pos;
}

int a_attaque_atk(ship_t *source, ship_t *cible)
{
    if (source->id == cible->id)
    {
        printf("[\x1b[31mError\x1b[0m] : can't attack urself !\n");
        exit(EXIT_FAILURE);
    }
    if (source->kerosene < 5)
    {
        printf("[\x1b[33mAttack\x1b[0m] : ship #%d can't attack ship #%d\n", source->id, cible->id);
        return -1;
    }
    else if (cible->coque <= 40)
    {
        printf("[\x1b[33mAttack\x1b[0m] : ship #%d destroy ship #%d\n", source->id, cible->id);
        cible->coque = 0;
        return 1;
    }
    else
    {
        printf("[\x1b[33mAttack\x1b[0m] : ship #%d -5K ship #%d -40C\n", source->id, cible->id);
        source->kerosene -= 5;
        cible->coque -= 40;
        printf("[\x1b[33mPlayer\x1b[0m] : ship #%d %dK ship #%d %dC\n", source->id, source->kerosene, cible->id, cible->coque);
        return 2;
    }
}

void m_deplacer_mov(ship_t *source, navalmap_t *nm, direction_t dir)
{
    if (dir == HAUT)
    {
    }
    else if (dir == BAS)
    {
        /* code */
    }
    else if (dir == GAUCHE)
    {
        /* code */
    }
    else if (dir == DROITE)
    {
        /* code */
    }
    else
    {
        printf("[\x1b[31mError\x1b[0m] : incorrect !\n");
        exit(EXIT_FAILURE);
    }
}