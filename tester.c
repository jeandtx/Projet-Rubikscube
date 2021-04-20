#include <curses.h>

int main()
{
    int count = 7;
    initscr();
    for (int i = 0; i < count; ++i) addch('L');
    for (int i = 0; i < count; ++i) addch('R');
    refresh();
    getch();
    endwin();
    return 0;
}

// To run this program past the following command in the terminal:
// cd "/Users/jeandtx/Documents/Projet-Rubikscube/" && gcc -lcurses tester.c -o tester && "/Users/jeandtx/Documents/Projet-Rubikscube/"tester