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

// char select_sides(T_SIDE side){
//     int a = select_side(side);
//     switch (a){
//         // ORDRE: {UP, RIGHT, DOWN, LEFT}
//         case 0:
//             T_SIDE **faces_list = {UP, RIGHT, DOWN, LEFT};
//             return faces_list;
//             break;
//         case 1:
//             T_SIDE **faces_list = {UP, LEFT, DOWN, RIGHT};
//             return faces_list;
//             break;
        
//         default:
//             break;
//     }
// }

// void turn_line(T_COLOR ***cube, int line){
//     for (int i = 0; i < 3; i++){
//         for (int j = 0; j < 5; j++){
//             if (!(j == 3 ||j == 2)){

//                 T_COLOR mem = cube[j][line][i];
//                 cube[j][line][i] = cube[j+1][line][i];
//                 cube[j+1][line][i] = mem;
//             }
//         }
//     }
// }
    
// void turn_top(T_COLOR ***cube, T_SIDE side){
// //     1 get to cube side
    

// //     2 get cube side values in third-party create_2d_array
    
    
// //     3 fill new cube side with values IN THE RIGHT PLACES

// }

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

    T_SIDE list_of_sides[10] =  {FRONT, BACK, UP, DOWN, RIGHT, LEFT};
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

void free_rubiks(T_COLOR ***cube){
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 3; j++){
            free(cube[i][j]);
        }
        free(cube[i]);
    }
    free(cube);
}

void turn_interface_2(T_COLOR ***cube, int choice, char face){
    
    clear();
    initscr();

    int iX = 0, iY = 1;
    mvprintw(iY, iX, "choose your action: ");
    mvprintw(iY + 3, iX, "r: turn right\tl: turn left\tf: flip");
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

void turn_face(T_COLOR ***cube, int number_of_turns, char face){
    for (int i = 0; i < number_of_turns; i++){
        int iX = 0, iY = 1;
        mvprintw(iY, iX, "it works??? really???");
        //T_SIDE *list_of_sides = select_sides(face);
        //turn_line(cube, 1);
        //turn_top(cube, face);   
    }
}

void turn_interface_1(T_COLOR ***cube, int side){
    clear();
    initscr();

    int iX = 0, iY = 1;
    mvprintw(iY, iX, "choose the face you want to turn: ");
    mvprintw(iY + 3, iX, "f: front\tb: back\tu: up\td: down\tr: right\tl: left");
    // refreshes the screen to match what's in memory 
    refresh();

    switch (side){
        case 'f':
            turn_interface_2(cube, "o", side);
        case 'b':
            turn_interface_2(cube, "o", side);
        case 'u':
            turn_interface_2(cube, "o", side);
        case 'd':
            turn_interface_2(cube, "o", side);
        case 'r':
            turn_interface_2(cube, "o", side);
        case 'l':
            turn_interface_2(cube, "o", side);
        default:
            turn_interface_1(cube, getch());
            break;
    }
}

void user_interface(T_COLOR ***cube, int a){
    clear();
    initscr();

    int iX = 0, iY = 1;
    mvprintw(iY, iX, "What Do You Want TO DO: ");
    mvprintw(iY + 3, iX, "s: Scramble\tr: Reset\tb: Blank\t f: Fill\td: Display\tq: Quit\tt: turn face");
    // refreshes the screen to match what's in memory 
    refresh();

    switch (a){
        case 'r':
            init_rubiks(cube);
            user_interface(cube, '6');
        case 'b':
            blank_rubiks(cube);
            user_interface(cube, '6');
        case 'd':
            display_rubiks(cube);
            user_interface(cube, getch());
        case 'q':
            // could create a function for a good bye screen
            endwin();
            break;
        case 't':
            turn_interface_1(cube, 'o');
        default:
            user_interface(cube, getch());
    }
    
}
