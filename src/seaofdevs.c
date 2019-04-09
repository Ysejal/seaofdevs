#include "../lib/include/seaofdevs.h"
#include "../lib/include/file.h"

int main(int argc, char **argv)
{
    file_t fichier;
    game_t game_info;

    fichier = open_file(argv[1], O_RDONLY);

    game_info = read_game_info(fichier);
    close_file(fichier);
    return 0;
}
