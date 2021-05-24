#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>
#include <math.h>

typedef enum{/*0*/FRONT, /*1*/BACK, /*2*/UP, /*3*/DOWN, /*4*/RIGHT, /*5*/LEFT}T_SIDE;
typedef enum{G, B, W, Y, R, O, LG}T_COLOR;

int select_color(T_COLOR color){
    /* This function take a color as input a return the integer position of this color */
    T_COLOR a = color;
    return (int) a;
}

int select_side(T_SIDE side){
    T_SIDE a = side;
    return (int) a;
}

T_COLOR **create_2d_array(int s){
    /* This function is used to get a 2D array */
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
    /* By using the create_2d_array multiple times we get a 3D array */
    T_COLOR ***cube;
    cube = (T_COLOR***) malloc(6 * sizeof(T_COLOR***));
    for (int i = 0; i < 6; i++){
        cube[i] = (T_COLOR**) create_2d_array(3);
    }
    return cube;
}

void init_rubiks(T_COLOR ***cube){
    /* This function take a cube as parameter and fill each side with each color */
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
        return "R ";}
    else if (input == B){return "B ";}
    else if (input == G){return "G ";}
    else if (input == W){return "W ";}
    else if (input == Y){return "Y ";}
    else if (input == O){return "O ";}
    else if (input == LG){return "\\";}
    else{printf("\nerror in function get_char_color\n\n");return "a";}
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

void pivot_face(T_COLOR ***cube, T_SIDE side){
    
    T_COLOR **old_val;
    old_val = create_2d_array(4);

    // capturing old values, hard code

    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            old_val[i][j] = cube[side][i][j];
        }
    }

    // placements, hard code


    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            cube[side][i][j] = old_val[2-i][j];
        }
    }
}

void turn_line(T_COLOR ***cube){

    T_COLOR **old_val;
    old_val = create_2d_array(4);

    // getting the cube's values

    old_val[0][0] = cube[UP][0][0];
    old_val[0][1] = cube[UP][0][1];
    old_val[0][2] = cube[UP][0][2];
    
    old_val[1][0] = cube[RIGHT][0][1];
    old_val[1][1] = cube[RIGHT][1][1];
    old_val[1][2] = cube[RIGHT][2][1];
    
    old_val[2][0] = cube[DOWN][2][0];
    old_val[2][1] = cube[DOWN][2][1];
    old_val[2][2] = cube[DOWN][2][2];

    old_val[3][0] = cube[LEFT][2][0];
    old_val[3][1] = cube[LEFT][2][1];
    old_val[3][2] = cube[LEFT][2][2];

    // placements

    cube[UP][2][0]    = old_val[3][2];
    cube[UP][2][1]    = old_val[3][1];
    cube[UP][2][2]    = old_val[3][0];

    cube[RIGHT][0][0] = old_val[0][0];
    cube[RIGHT][1][0] = old_val[0][1];
    cube[RIGHT][2][0] = old_val[0][2];

    cube[DOWN][0][0]  = old_val[1][2];
    cube[DOWN][0][1]  = old_val[1][1];
    cube[DOWN][0][2]  = old_val[1][0];

    cube[LEFT][0][2]  = old_val[2][0];
    cube[LEFT][1][2]  = old_val[2][1];
    cube[LEFT][2][2]  = old_val[2][2];

}

void turn_face_and_line(T_COLOR ***cube, int number_of_turns){
    for (int i = 0; i < number_of_turns; i++){
        turn_line(cube);
        pivot_face(cube, FRONT);
    }
}

void vertical_rotation(T_COLOR ***cube){
    for (int i=0; i<3; i++){pivot_face(cube, LEFT);}
    pivot_face(cube, RIGHT);
    
    T_COLOR **storage_side;
    storage_side = create_2d_array(3);

    int list_of_sides[5] = {2, 0, 3, 1};
    
    // we store the first side
    for (int j = 0; j < 3; j++){
        for (int k = 0; k < 3; k++){
            storage_side[j][k] = cube[list_of_sides[0]][j][k];
        }
    }
    // we transfer each side in the previous one
    for(int side = 0; side < 3; side++){
        for (int j = 0; j < 3; j++){
            for (int k = 0; k < 3; k++){
                cube[list_of_sides[side]][j][k] = cube[list_of_sides[side+1]][j][k];
            }
        }
    }
    // we transfer the last side from the storage
    for (int j = 0; j < 3; j++){
        for (int k = 0; k < 3; k++){
            cube[list_of_sides[3]][j][k] = storage_side[2-j][k];
        }
    }
}

void horizontal_rotation(T_COLOR ***cube){
    
    T_COLOR **storage_side;
    storage_side = create_2d_array(3);

    for (int i=0; i<3; i++){pivot_face(cube, UP);}
    pivot_face(cube, DOWN);

    int list_sds[5] = {5, 1, 4, 0};
    // we store the first side
    for (int j = 0; j < 3; j++){
        for (int k = 0; k < 3; k++){
            storage_side[j][k] = cube[list_sds[0]][j][k];
        }
    }

    // we transfer each side in the previous one
    for(int side = 0; side < 3; side++){
        for (int j = 0; j < 3; j++){
            for (int k = 0; k < 3; k++){
                cube[list_sds[side]][j][k] = cube[list_sds[side+1]][j][k];
            }
        }
    }

    // we transfer the last side from the storage
    for (int j = 0; j < 3; j++){
        for (int k = 0; k < 3; k++){
            cube[list_sds[3]][j][k] = storage_side[2-j][k];
        }
    }
}

void scramble(T_COLOR ***cube){
    srand((unsigned)time(NULL)); // Initialization, should only be called once.
    int k = rand()%8 + 4;

    for (int i = 0; i < k; i++){
        vertical_rotation(cube);
        pivot_face(cube, FRONT);
        horizontal_rotation(cube);
    }
}

void display_rubiks(T_COLOR ***cube, int a){
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
    int x = LINES/10, y = COLS/25, cx = 7, cy = 4;
    
    int position_by_side[10][5] = {
        {x+1*cx, y}, // FRONT <- GREEN
        {x+3*cx, y}, // BACK <- BLUE
        {x+1*cx, y-1*cy}, // UP <- WHITE
        {x+1*cx, y+1*cy}, // DOWN <- YELLOW 
        {x+2*cx, y}, // RIGHT <- RED
        {x, y} // LEFT <- ORANGE
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
    x += 30;
    y -= 3;
    attron(COLOR_PAIR(3));
    mvprintw(y-1, x,    " __________________________________________________________________________");
    mvprintw(y+0, x,    "@                                                                          @");
    mvprintw(y+1, x,    "︴                      What Do You Want to do ??????????                  ︴");
    mvprintw(y+2, x,    "︴                                                                         ︴");
    mvprintw(y+3, x,    "︴             s: Scramble        b: Blank        f: Fill                  ︴");
    mvprintw(y+4, x,    "︴             q: Quit            r: Reset        t: pivot front face      ︴");
    mvprintw(y+5, x,    "︴             turn cube :        h: Horizontaly  v: Verticaly             ︴");
    mvprintw(y+6, x,    "︴                                                                         ︴");
    mvprintw(y+7, x,    "︴                 press enter after choosing the wright cmd               ︴");
    mvprintw(y+8, x,    "@__________________________________________________________________________@");
    switch (a){
        case 'r':
            init_rubiks(cube);
            display_rubiks(cube, getch());
        case 'b':
            blank_rubiks(cube);
            display_rubiks(cube, getch());
        case 'q':
            free_rubiks(cube);
            endwin();
            break;
        case 't':
            turn_face_and_line(cube, 1);
            display_rubiks(cube, getch());
        case 'h':
            horizontal_rotation(cube);
            display_rubiks(cube, getch());
        case 'v':
            vertical_rotation(cube);
            display_rubiks(cube, getch());
        case 's':
            scramble(cube);
            display_rubiks(cube, getch());
        default:
            display_rubiks(cube, getch());
    }
    // refreshes the screen to match what's in memory 
    refresh();
    getch();
    // what's for user input, returns 
    endwin();
}