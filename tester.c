#include <curses.h>

int main()
{
    // top needed part 
    initscr();

    // working part 
    for (int i = 0; i < 7; ++i) addch('L');
    for (int i = 0; i < 7; ++i) addch('R');

    attron(A_NORMAL);
    printw("Texte sans mise en forme\n");

    attron(A_STANDOUT);
    printw("Texte en meilleur surlignement\n");
    attroff(A_STANDOUT);

    attron(A_REVERSE);
    printw("Texte en inversion video\n");
    attroff(A_REVERSE);

    attron(A_DIM);
    printw("Texte a moitie brillant\n");
    attroff(A_DIM);

    attron(A_BOLD);
    printw("Texte en gras\n");
    attroff(A_BOLD);

    attron(A_UNDERLINE);
    printw("Texte en souligne\n");
    attroff(A_UNDERLINE);

    attron(A_INVIS);
    printw("Texte invisible\n");
    attroff(A_INVIS);

    attron(A_UNDERLINE | A_BOLD); // Pour appliquer plusieurs type de mises en forme, on utilise l'opérateur unaire |
    printw("Texte en gras souligne\n");
    
    // end needed part 
    refresh();
    getch();
    endwin();
    return 0;
}


// To run for jean:
// cd "/Users/jeandtx/Documents/Projet-Rubikscube/" && gcc -lcurses tester.c -o tester && "/Users/jeandtx/Documents/Projet-Rubikscube/"tester

// To run for Oscar:
// cd "/home/oscar/Documents/Efrei/c_tries/Projet-Rubikscube/" && gcc -lcurses tester.c -o main && "/home/oscar/Documents/Efrei/c_tries/Projet-Rubikscube/"main
