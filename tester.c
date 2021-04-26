#include <curses.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    initscr();
    
    move(LINES - 1, COLS - 1);  // Déplace le curseur tout en bas à droite de l'écran
    addch('.');                 // Écrit le caractère . au nouvel emplacement
    
    /** est équivalent à : **/
    //mvaddch(LINES - 1, COLS - 1, '.');
    
    /** ou encore à : **/
    //mvprintw(LINES - 1, COLS - 1, ".");

    getch();
    endwin();
}


// To run for jean:
// cd "/Users/jeandtx/Documents/Projet-Rubikscube/" && gcc -lcurses tester.c -o tester && "/Users/jeandtx/Documents/Projet-Rubikscube/"tester

// To run for Oscar:
// cd "/home/oscar/Documents/Efrei/c_tries/Projet-Rubikscube/" && gcc -lcurses tester.c -o tester && "/home/oscar/Documents/Efrei/c_tries/Projet-Rubikscube/"tester



// for (i=0; i<3; i++){
//         char *a = get_char_color(cube[1][i][1]);
//         mvprintw(startX + i, startY, a);
//     }