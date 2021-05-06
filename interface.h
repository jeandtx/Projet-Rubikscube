#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include "pack.h"


void turn_interface_2(T_COLOR ***cube, char choice, char face){
    
    clear();
    initscr();

    int iX = 0, iY = 1;
    mvprintw(iY, iX, "choose your action: ");
    mvprintw(iY + 3, iX, "r: turn right\tl: turn left\tf: flip\tg: go back");
    // refreshes the screen to match what's in memory 
    refresh();

    switch (choice){
        case 'r':
            turn_face(cube, 1, face);
        case 'l':
            turn_face(cube, 3, face);
        case 'f':
            turn_face(cube, 2, face);

        default:
            turn_interface_2(cube, getch(), face);
            break;
    }
}

void turn_interface_1(T_COLOR ***cube, int side){
    clear();
    initscr();

    int iX = 0, iY = 1;
    mvprintw(iY, iX, "choose the face you want to turn: ");
    mvprintw(iY + 3, iX, "f: front\tb: back\tu: up\td: down\tr: right\tl: left\tg: go back");
    // refreshes the screen to match what's in memory 
    refresh();

    switch (side){
        case 'f':
            turn_interface_2(cube, 'o', side);
        case 'b':
            turn_interface_2(cube, 'o', side);
        case 'u':
            turn_interface_2(cube, 'o', side);
        case 'd':
            turn_interface_2(cube, 'o', side);
        case 'r':
            turn_interface_2(cube, 'o', side);
        case 'l':
            turn_interface_2(cube, 'o', side);
        default:
            turn_interface_1(cube, getch());
            break;
    }
}


void user_interface(T_COLOR ***cube, int a){
    clear();
    initscr();
    start_color();
    int iX = 0, iY = 1;
    init_pair(4, COLOR_WHITE, COLOR_BLACK);
    attron(COLOR_PAIR(select_color(4)));
    mvprintw(iY, iX, "What Do You Want TO DO: ");
    mvprintw(iY + 3, iX, "s: Scramble\tr: Reset\tb: Blank\t f: Fill\td: Display\tq: Quit\t\tt: turn face");
    // refreshes the screen to match what's in memory 
    refresh();

    switch (a){
        case 'r':
            init_rubiks(cube);
            user_interface(cube, 'd');
        case 'b':
            blank_rubiks(cube);
            user_interface(cube, 'd');
        case 'd':
            display_rubiks(cube);
            user_interface(cube, getch());
        case 'q':
            // could create a function for a good bye screen
            endwin();
            break;
        case 't':
            turn_interface_1(cube, 'o');
        case 'p':
            train(cube);
        default:
            user_interface(cube, getch());
    }
    
}
