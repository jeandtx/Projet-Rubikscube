#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>
#include <math.h>
#include <string.h>

typedef enum{/*0*/FRONT, /*1*/BACK, /*2*/UP, /*3*/DOWN, /*4*/RIGHT, /*5*/LEFT}T_SIDE;
typedef enum{G, B, W, Y, R, O, LG}T_COLOR;

int select_color(T_COLOR color){
    // returns a number associated with the given T_COLOR
    // not sure if its necessary though
    // but we'll take no chances with that damned compilator
    T_COLOR a = color;
    return (int) a;
}

int select_side(T_SIDE side){
    /* This is one asked function wich take side as argument and return the side's number
    However the compilator is already doing this job when we put a type side as index of a list
    So this function is sometimes used and sometimes we forgot to did it*/
    T_SIDE a = side;
    return (int) a;
}

T_COLOR **create_2d_array(int s){
    // This function is used to get a 2D array
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
    // By using the create_2d_array multiple times we get a 3D array
    T_COLOR ***cube;
    cube = (T_COLOR***) malloc(6 * sizeof(T_COLOR***));
    for (int i = 0; i < 6; i++){
        cube[i] = (T_COLOR**) create_2d_array(3);
    }
    return cube;
}

void init_rubiks(T_COLOR ***cube, char *color){
    T_COLOR a = LG;
    for (int i = 0; i < 6; i++){
        if (strcmp(color, "color") == 0){a = (T_COLOR) i;}
        for (int j = 0; j < 3; j++){
            for (int k = 0; k < 3; k++){
                cube[i][j][k] = a;
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
    else if (input == LG){return "+";}
    else{printf("\nerror in function get_char_color\n\n");return "a";}
}

void free_rubiks(T_COLOR ***cube){
    // this frees all memory used by the cube
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 3; j++){
            free(cube[i][j]);
        }
        free(cube[i]);
    }
    free(cube);
}

void pivot_face(T_COLOR ***cube, T_SIDE side){
    // makes the front face rotate clockwise by a quarter of a turn
    
    T_COLOR **old_val;
    old_val = create_2d_array(4);

    // capturing old values
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            old_val[i][j] = cube[side][i][j];
        }
    }

    // placements
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            cube[side][i][j] = old_val[2-i][j];
        }
    }
}

void turn_line(T_COLOR ***cube){
    /* For this function we didn't find an opimize algorithm because of the time.
    So it save each lines of the 4 around face from front. And copy them to their new location
    This function is working only at her first call. After it, it either forget some or add more colors 
    As explained in Issue #4 in our github.*/

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
    /* This function was created to make clockwise and anti clockwise by turning either 1 time or 3 times*/
    for (int i = 0; i < number_of_turns; i++){
        turn_line(cube);
        pivot_face(cube, FRONT);
    }
}

void vertical_rotation(T_COLOR ***cube){
    /* This function is mooving the hole cube horizontaly by copying the first face in some memory. After
    that it move the next one in the first one and so on. At the end the saved face is put on the last face
    But the last one is inversed on vertical plane because back is inversed in the display*/
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
    /* This function is mooving the hole cube horizontaly by copying the first face in some memory. After
    that it move the next one in the first one and so on. At the end the saved face is put on the last face*/
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

int aleatoire(int min, int max){
    srand((unsigned)time(NULL));  // Initialization, should only be called once.
    int a = rand()%(max-min) + min;
    return a;
}

void scramble(T_COLOR ***cube){
    /* This function is calling some function to moove the cube a randomly number of time
    This actions can simulate what if someone scramble the cub*/
    for (int i = 0; i < aleatoire(4, 8); i++){
        vertical_rotation(cube);
        pivot_face(cube, FRONT); // Unfortunately this function is causing troubles
        horizontal_rotation(cube);
    }
}

int color_to_int(char* color){
    if (strcmp(color, "green")      == 0){return 1;}
    if (strcmp(color, "blue")       == 0){return 2;}
    if (strcmp(color, "white")      == 0){return 3;} 
    if (strcmp(color, "yellow")     == 0){return 4;}
    if (strcmp(color, "red")        == 0){return 5;}
    if (strcmp(color, "magenta")    == 0){return 6;}
    return 0;
}

void check_fill(T_COLOR ***cube){
    int occ[7] = {0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
                occ[cube[i][j][k]]++;
    int max = occ[0];
    for (int i = 0; i < 6; i++)
        if (max < occ[i])
            max = occ[i];
    if (max >= 10)
        init_rubiks(cube, "color");
}

void fill(T_COLOR ***cube){
    
    /* The function fill is quite identic to the function display. 
    But before each display we ask the user to fill
    then we come back to the global menu with what he filled
    */
    clear();
    initscr();
    start_color();
    init_pair(7, COLOR_BLACK, COLOR_WHITE);
    int x = LINES/10, y = COLS/25, cx = 7, cy = 4;
    
    int position_by_side[10][5] = {
        {x+1*cx, y}, // FRONT <- GREEN
        {x+3*cx, y}, // BACK <- BLUE
        {x+1*cx, y-1*cy}, // UP <- WHITE
        {x+1*cx, y+1*cy}, // DOWN <- YELLOW 
        {x+2*cx, y}, // RIGHT <- RED
        {x, y} // LEFT <- ORANGE
    };

    x += 30;
    y -= 3;
    attron(COLOR_PAIR(3));
    mvprintw(y-1, x,    " __________________________________________________________________________" );
    mvprintw(y+0, x,    "@                                                                          @");
    mvprintw(y+1, x,    "|                        Pleas fill the RubiksCube                         |");
    mvprintw(y+2, x,    "|                                                                          |");
    mvprintw(y+3, x,    "|             r: Red             b: Blue         g: Green                  |");
    mvprintw(y+4, x,    "|             o: Orange          w: White        y: Yellow                 |");
    mvprintw(y+5, x,    "|                                                                          |");
    mvprintw(y+6, x,    "|                      Don't press enter or blank                          |");
    mvprintw(y+7, x,    "@__________________________________________________________________________@");

    T_SIDE list_of_sides[10] =  {FRONT, BACK, UP, DOWN, RIGHT, LEFT};
    // We choose the side to display in a variable
    for (int k = 0; k < 6; k++){
        T_SIDE side = list_of_sides[k];
        // Then we can display that side
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                mvprintw(position_by_side[k][1] + i, position_by_side[k][0] + j*2, "");
                char *a = get_char_color(cube[select_side(side)][i][j]);
                attron(COLOR_PAIR(select_color(cube[select_side(side)][i][j]) + 1 ));
                switch (getch()){
                    case 'r': cube[select_side(side)][i][j] = (T_COLOR) R; break;
                    case 'b': cube[select_side(side)][i][j] = (T_COLOR) B; break;
                    case 'g':
                        cube[select_side(side)][i][j] = (T_COLOR) G;
                        break;
                    case 'o':
                        cube[select_side(side)][i][j] = (T_COLOR) O;
                        break;
                    case 'w':
                        cube[select_side(side)][i][j] = (T_COLOR) W;
                        break;
                    case 'y':
                        cube[select_side(side)][i][j] = (T_COLOR) Y;
                        break;
                    default:
                        cube[select_side(side)][i][j] = (T_COLOR) LG;
                        break;
                }
            }
        }
    }
    check_fill(cube);
}

void resolve_rubiks(T_COLOR ***cube){
    
}

void display_rubiks(T_COLOR ***cube, int a){
    /*
    This function is the display function for the rubiks and the menu. In the diplay function we use the librairy
    curses.h which use the terminal as a window. 
    This allow us to get colors for each letter. And we diplay the menu which is a switch
    with getch as variable. Getch is a function from curses to get the pressed key board
    */
    clear();
    initscr();
    start_color();
    init_pair(1, COLOR_GREEN,   COLOR_BLACK);
    init_pair(2, COLOR_BLUE,    COLOR_BLACK);
    init_pair(3, COLOR_WHITE,   COLOR_BLACK);
    init_pair(4, COLOR_YELLOW,  COLOR_BLACK);
    init_pair(5, COLOR_RED,     COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(7, COLOR_BLACK, COLOR_WHITE);
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
    mvprintw(y-1, x,    " __________________________________________________________________________" );
    mvprintw(y+0, x,    "@                                                                          @");
    mvprintw(y+1, x,    "|                      What Do You Want to do ??????????                   |");
    mvprintw(y+2, x,    "|                                                                          |");
    mvprintw(y+3, x,    "|             s: Scramble        b: Blank        f: Fill                   |");
    mvprintw(y+4, x,    "|             q: Quit            r: Reset        t: pivot front face       |");
    mvprintw(y+5, x,    "|             turn cube :        h: Horizontally v: Vertically             |");
    mvprintw(y+6, x,    "|                                                                          |");
    mvprintw(y+7, x,    "|                 press enter after choosing the wright cmd                |");
    mvprintw(y+8, x,    "@__________________________________________________________________________@");

    switch (a){
        case 'r':
            init_rubiks(cube, "color");
            display_rubiks(cube, getch());
        case 'b':
            init_rubiks(cube, "blank");
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
        case 'f':
            init_rubiks(cube, "blank");
            fill(cube);
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