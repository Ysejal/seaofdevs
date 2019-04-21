#include "../lib/include/seaofdevs.h"
#include "../lib/include/navalmap.h"

/**
 * @brief Convert entity_t to char
 * 
 * @param e 
 * @return char 
 */
char entitytochar(entity_t e)
{
    if (e == ENT_SEA)
    {
        return '.';
    }
    else if (e == ENT_SHIP)
    {
        return '*';
    }
    else
    {
        perror("error : entity type");
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Draw navalmap
 * 
 * @param nm 
 */
void draw_navalmap(navalmap_t *nm)
{
    printf("mapsize %dx%d \n", nm->size.y, nm->size.x);

    for (int i = 0; i < nm->size.y; i++)
    {
        for (int j = 0; j < nm->size.x; j++)
        {
            printf("\x1B[37;7m %c \033[0m", entitytochar(nm->map[i][j].type));
        }
        printf("\n");
    }
}