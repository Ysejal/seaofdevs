#include "../lib/include/seaofdevs.h"

WINDOW *board;

void draw_game_board(game_t g)
{
    /* Initialisation de Ncurses */
    initscr();
    /* On desactive le curseur */
    curs_set(0);
    /* Initialisation de la grille de Jeu */
    board = newwin(g.tailleX * 3, g.tailleY * 6, 0, 0);
    box(board, 0, 0);
    /* On affiche la grille */
    wrefresh(board);
    /* On attend la touche d'arret */
    wgetch(board);
    /* Fin de Ncurses */
    endwin();
}