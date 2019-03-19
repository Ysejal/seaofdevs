#include "../lib/include/seaofdevs.h"
#include "../lib/include/file.h"

int main(int argc, char **argv)
{
    file_t fichier;

    fichier = open_file(argv[1], O_RDONLY);

    close_file(fichier);
    return 0;
}