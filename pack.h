#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>

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

T_COLOR **create_2d_array(int s){
    int i, j;
    T_COLOR **array;
    array = (T_COLOR**) malloc(3 * sizeof(T_COLOR**));
    for (i = 0; i < s; i++){
        for (j = 0; j < s; j++)
            array[i] = (T_COLOR*) malloc(3 * sizeof(T_COLOR*));
    }
    return array;
}

T_COLOR ***create_rubiks(){
    T_COLOR ***cube;
    cube = (T_COLOR***) malloc(6 * sizeof(T_COLOR***));
    for (int i = 0; i < 6; i++){
        cube[i] = (T_COLOR**) create_2d_array(3);
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

char select_sides(T_SIDE side){
    int a = select_side(side);
    T_SIDE *sds;
    sds = (T_SIDE*) malloc(4*sizeof(T_SIDE));
    switch (a){
        // ORDRE: {UP, RIGHT, DOWN, LEFT}
        case 0: //COLOR NAME
            sds[0] = (T_SIDE) UP; sds[1] = (T_SIDE) RIGHT; sds[2] = (T_SIDE) DOWN; sds[3] = (T_SIDE) LEFT;
            return *sds;
            break;
        case 1:
            sds[0] = (T_SIDE) UP; sds[1] = (T_SIDE) LEFT; sds[2] = (T_SIDE) DOWN; sds[3] = (T_SIDE) RIGHT;
            return *sds;
            break;
        case 2:
            sds[0] = (T_SIDE) UP; sds[1] = (T_SIDE) LEFT; sds[2] = (T_SIDE) DOWN; sds[3] = (T_SIDE) RIGHT;
            return *sds;
            break;
        case 3:
            sds[0] = (T_SIDE) UP; sds[1] = (T_SIDE) RIGHT; sds[2] = (T_SIDE) DOWN; sds[3] = (T_SIDE) LEFT;
            return *sds;
            break;
        case 4:
            sds[0] = (T_SIDE) UP; sds[1] = (T_SIDE) RIGHT; sds[2] = (T_SIDE) DOWN; sds[3] = (T_SIDE) LEFT;
            return *sds;
            break;
        case 5:
            sds[0] = (T_SIDE) UP; sds[1] = (T_SIDE) RIGHT; sds[2] = (T_SIDE) DOWN; sds[3] = (T_SIDE) LEFT;
            return *sds;
            break;

        default:
            break;
    }
    return 'e';
}

char *get_char_color(T_COLOR input){
    // gets a T_COLOR type input, returns it as a character
    if (input == R){
        return "R ";}
    else if (input == B){
        return "B ";}
    else if (input == G){
        return "G ";}
    else if (input == W){
        return "W ";}
    else if (input == Y){
        return "Y ";}
    else if (input == O){
        return "O ";}
    else if (input == LG){
        return "\\";}
    else{
        printf("\nerror in function get_char_color\n\n");
        return "a";}
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
    int iX = LINES/10, iY = COLS/25, cx = 7, cy = 4;
    
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
                mvprintw(position_by_side[k][1] + i, position_by_side[k][0] + j*2, a);
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

void turn_top(T_COLOR ***cube, T_SIDE side){
    int sd = select_sides(side);
    T_COLOR old_values[4][4];

    // capturing old values, soft code
    /*
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            old_values[i][j] = cube[sd][i][j];
        }
    }
    */
    // capturing old values, hard code

    old_values[0][0] = cube[sd][0][0];
    old_values[0][1] = cube[sd][0][1];
    old_values[0][2] = cube[sd][0][2];

    old_values[1][0] = cube[sd][1][0];
    old_values[1][1] = cube[sd][1][1];
    old_values[1][2] = cube[sd][1][2];

    old_values[2][0] = cube[sd][2][0];
    old_values[2][1] = cube[sd][2][1];
    old_values[2][2] = cube[sd][2][2];

    // placements, soft code
    /*
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            old_values[i][j] = cube[sd][2-j][i];
        }
    }
    */
    // placements, hard code

    cube[sd][0][0] = old_values[2][0];
    cube[sd][0][1] = old_values[1][0];
    cube[sd][0][2] = old_values[0][0];

    cube[sd][1][0] = old_values[2][1];
    cube[sd][1][1] = old_values[1][1];
    cube[sd][1][2] = old_values[0][1];

    cube[sd][2][0] = old_values[2][2];
    cube[sd][2][1] = old_values[1][2];
    cube[sd][2][2] = old_values[0][2];
}



void turn_line(T_COLOR ***cube, T_SIDE side){

    // int a = select_side(side);
    // T_SIDE *sds;
    // sds = (T_SIDE*) malloc(4*sizeof(T_SIDE));
    // switch (a){
    //     // ORDRE: {UP, RIGHT, DOWN, LEFT}
    //     case 0: //COLOR NAME
    //         sds[0] = (T_SIDE) UP; sds[1] = (T_SIDE) RIGHT; sds[2] = (T_SIDE) DOWN; sds[3] = (T_SIDE) LEFT;
    //         break;
    //     case 1:
    //         sds[0] = (T_SIDE) UP; sds[1] = (T_SIDE) LEFT; sds[2] = (T_SIDE) DOWN; sds[3] = (T_SIDE) RIGHT;
    //         break;
    //     case 2:
    //         sds[0] = (T_SIDE) UP; sds[1] = (T_SIDE) LEFT; sds[2] = (T_SIDE) DOWN; sds[3] = (T_SIDE) RIGHT;
    //         break;
    //     case 3:
    //         sds[0] = (T_SIDE) UP; sds[1] = (T_SIDE) RIGHT; sds[2] = (T_SIDE) DOWN; sds[3] = (T_SIDE) LEFT;
    //         break;
    //     case 4:
    //         sds[0] = (T_SIDE) UP; sds[1] = (T_SIDE) RIGHT; sds[2] = (T_SIDE) DOWN; sds[3] = (T_SIDE) LEFT;
    //         break;
    //     case 5:
    //         sds[0] = (T_SIDE) UP; sds[1] = (T_SIDE) RIGHT; sds[2] = (T_SIDE) DOWN; sds[3] = (T_SIDE) LEFT;
    //         break;

    //     default:
    //         break;
    // }
    // T_COLOR old_values[10][10];

    // capturing old values, soft code

    /*
    for (int i=0; i<2; i++){
        int k = i*2;
        for (int j=0; j<3; j++){
            old_values[k][j] = cube[sds[k]][2-k][j];
        }
    }
    for (int i=0; i<2; i++){
        int k = i*2;
        for (int j=0; j<3; j++){
            old_values[k+1][j] = cube[sds[k+1]][j][k];
        }
    }
    */

    // capturing old values, soft code
    int sds[5] = {4, 2, 5, 3};
    T_COLOR **old_values;
    old_values = create_2d_array(4);


    old_values[0][0] = cube[sds[3]][0][0];
    old_values[0][1] = cube[sds[3]][0][1];
    old_values[0][2] = cube[sds[3]][0][2];
    
    old_values[1][0] = cube[sds[0]][1][0];
    old_values[1][1] = cube[sds[0]][1][1];
    old_values[1][2] = cube[sds[0]][1][2];
    
    old_values[2][0] = cube[sds[1]][2][0];
    old_values[2][1] = cube[sds[1]][2][1];
    old_values[2][2] = cube[sds[1]][2][2];

    

    // placements, version soft code

    /*
    int i,j,k,a;
    for (k=0; k<3; k++){
        if (k == 0){a = 3;}
        else{a = k;}
        
        if (k%2 == 0){
            i = 2-k;
            b = 2-j;
            for (j=0; j<3; j++){
                cube[sds[k]][i][j]  =   old_values[a][b];
            }
        }

        else{
            j = k-1;
            b = i;
            for (i=0; i<3; i++){
                cube[sds[k]][i][j]  =   old_values[a][b];
            }
        }
    }
    */

    // placements, version hard code

    cube[sds[0]][2][0]  =   old_values[3][2];
    cube[sds[0]][2][1]  =   old_values[3][1];
    cube[sds[0]][2][2]  =   old_values[3][0];

    cube[sds[1]][0][0]  =   old_values[0][0];
    cube[sds[1]][1][0]  =   old_values[0][1];
    cube[sds[1]][2][0]  =   old_values[0][2];

    cube[sds[2]][0][0]  =   old_values[1][2];
    cube[sds[2]][0][1]  =   old_values[1][1];
    cube[sds[2]][0][2]  =   old_values[1][0];

}

void turn_face(T_COLOR ***cube, int number_of_turns, T_SIDE side){
    for (int i = 0; i < number_of_turns; i++){
        turn_line(cube, side);
        // turn_top(cube, side);
    }
}

// ######################--#######################--###############################################
// ########################--------#####--------##################################################
// ################################################################################################
// #############################  ########  #######################################################
// #############################o ########o #######################################################
// ################################################################################################
// #########################/\#################/\###################################################
// ##########################/\###############/\####################################################
// ###########################/\/\###########/\/\####################################################
// #############################/\/\/\/\/\/\/\/\###################################################
// ################################################################################################

void turn_interface_2(T_COLOR ***cube, char choice, char face){
    
    clear();
    initscr();

    int iX = 0, iY = 1;
    mvprintw(iY, iX, "choose your action: ");

    mvprintw(iY, iX, "choose your action: ");
    mvprintw(iY + 3, iX, "r: turn right\tl: turn left\tf: flip\tq: quit");
    // refreshes the screen to match what's in memory 
    refresh();

    switch (choice){
        case 'r':
            turn_face(cube, 1, face);
        case 'l':
            turn_face(cube, 3, face);
        case 'f':
            turn_face(cube, 2, face);
        case 'q':
            endwin();
            clear();
            break;
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
    mvprintw(iY + 3, iX, "f: front\tb: back\tu: up\td: down\tr: right\tl: left\tq: quit");
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
        case 'q':
            endwin();
            clear();
            break;
        default:
            turn_interface_1(cube, getch());
            break;
    }
}

void user_interface(T_COLOR ***cube, int a){
    clear();
    initscr();

    int iX = 5, iY = LINES/2 - 5;
    mvprintw(iY - 1, iX, "----------------------------------------------------------------------------------------------------------------------------------------------");
    mvprintw(iY, iX, "What Do You Want TO DO:");
    mvprintw(iY + 3, iX, "s: Scramble\tr: Reset\tb: Blank\t f: Fill\td: Display\tq: Quit\t\tt: turn face");
    mvprintw(iY+5, iX, "----------------------------------------------------------------------------------------------------------------------------------------------");
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
            free_rubiks(cube);
            endwin();
            break;
        case 't':
            turn_face(cube, 1, FRONT);
            user_interface(cube, 'd');
            // turn_interface_1(cube, 'o');
        default:
            user_interface(cube, getch());
    }
}
