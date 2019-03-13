#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../lib/include/file.h"

file_t open_file(const char *chemin, int acces)
{
    file_t file_1;

    file_1.dir = chemin;
    file_1.acces = acces;
    file_1.descriptor = open(chemin, acces | S_IRWXU);

    return file_1;
}