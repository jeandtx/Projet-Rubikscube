#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

typedef enum{ 
    FRONT, 
    BACK, 
    UP, 
    DOWN, 
    RIGHT, 
    LEFT 
}T_SIDE;

typedef enum{
    G,
    B,
    W,
    Y,
    R,
    O,
    LG
}T_COLOR;

int select_color(T_COLOR color){
    T_COLOR a = color;
    return (int) a;
}

int select_side(T_SIDE side){
    T_SIDE a = side;
    return (int) a;
}

T_COLOR **create_2d_array(){
    int i, j;
    T_COLOR **array;
    array = (T_COLOR**) calloc(3, sizeof(T_COLOR**));
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++)
            array[i] = (T_COLOR*) calloc(3, sizeof(T_COLOR*));
    }
    return array;
}

T_COLOR ***create_rubiks(){
    T_COLOR ***cube;
    cube = (T_COLOR***) calloc(6, sizeof(T_COLOR***));
    for (int i = 0; i < 6; i++){
        cube[i] = (T_COLOR**) create_2d_array();
    }
    return cube;
}

void init_rubiks(T_COLOR ***cube){
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 3; j++){
            for (int k = 0; k < 3; k++){
                cube[i][j][k] = (T_COLOR) i;
            }
        }
    }
}

char *get_char_color(T_COLOR input){
    // gets a T_COLOR type input, returns it as a character
    if (input == R){
        return "R";
    }
    else if (input == B){
        return "B";
    }
    else if (input == G){
        return "G";
    }
    else if (input == W){
        return "W";
    }
    else if (input == Y){
        return "Y";
    }
    else if (input == O){
        return "O";
    }
    else if (input == LG){
        return "LG";
    }
    else{
        printf("\nerror in function get_char_color\n\n");
        return "a";
    }
}

void display_rubiks(T_COLOR ***cube){
    clear();
    initscr();
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_RED, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(7, COLOR_BLACK, COLOR_WHITE); // This added color is only for the blanks rubikscube
    int iX = LINES/10, iY = COLS/25, cx = 5, cy = 4;
    
    int position_by_side[10][5] = {
        {iX+1*cx, iY}, // FRONT <- GREEN
        {iX+3*cx, iY}, // BACK <- BLUE
        {iX+1*cx, iY-1*cy}, // UP <- WHITE
        {iX+1*cx, iY+1*cy}, // DOWN <- YELLOW 
        {iX+2*cx, iY}, // RIGHT <- RED
        {iX, iY} // LEFT <- ORANGE
    };

    T_SIDE list_of_sides[10] =  {FRONT, BACK, UP, DOWN, RIGHT, LEFT };
    // We choose the side to display in a variable
    for (int k = 0; k < 6; k++){
        T_SIDE side = list_of_sides[k];
        // Then we can display that side
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                char *a = get_char_color(cube[select_side(side)][i][j]);
                attron(COLOR_PAIR(select_color(cube[select_side(side)][i][j]) + 1 ));
                mvprintw(position_by_side[k][1] + i, position_by_side[k][0] + j, a);
            }
        }
    }
    // refreshes the screen to match what's in memory 
    refresh();
    getch();
    // what's for user input, returns 
    endwin();
}

void blank_rubiks(T_COLOR ***cube){
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 3; j++){
            for (int k = 0; k < 3; k++){
                cube[i][j][k] = LG;
            }
        }
    }
}

void scramble_rubiks(T_COLOR ***cube){
    
}

void free_rubiks(T_COLOR ***cube){
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 3; j++){
            free(cube[i][j]);
        }
        free(cube[i]);
    }
    free(cube);
}

void user_interface(T_COLOR ***cube, int a){
    clear();
    initscr();
    
    int iX = 0, iY = 1;
    mvprintw(iY, iX, "What Do You Want TO DO: ");
    mvprintw(iY + 3, iX, "1: Scramble\t2: Reset\t3: Blank\t 5: Fill\t6: Display\t7: Quit");
    mvprintw(iY + 6, iX, "OUTPUT : ");
    // refreshes the screen to match what's in memory 
    refresh();

    switch (a){
        case '7':
            // could create a function for a good bye screen
            endwin();
            break;
        case '6':
            display_rubiks(cube);
            fill_rubiks(cube, getch());
            break;
        case '3':
            blank_rubiks(cube);
        
        default:
            fill_rubiks(cube, getch());
            break;
    }
    
}
