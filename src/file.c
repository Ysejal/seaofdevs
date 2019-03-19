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

int close_file(file_t file)
{
    return close(file.descriptor);
}

map_t read_map(file_t f)
{
    map_t infomap;

    return infomap;
}
