#include <stdio.h>
#include <stdlib.h>

typedef enum{ 
    FRONT, 
    BACK, 
    UP, 
    DOWN, 
    RIGHT, 
    LEFT 
}T_SIDE;

typedef enum{
    R,
    B,
    G,
    W,
    Y,
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
    for (T_COLOR i = 0; i < 6; i++){
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
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 3; j++){
            printf("\n");
            for (int k = 0; k < 3; k++){
                printf("%s", get_char_color(cube[i][j][k]));
            }
        }
        printf("\n");
    }
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

void fill_rubiks(T_COLOR ***cube){
    
}

int main(){
    T_COLOR ***cube;
    cube = create_rubiks();
    init_rubiks(cube);
    display_rubiks(cube);


    return 0;
}
    