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

typedef enum {
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

T_SIDE ***create_rubiks(){
    T_SIDE ***cube;
    cube = (T_SIDE***) calloc(6, sizeof(T_SIDE***));
    for (T_SIDE i = 0; i < 6; i++){
        cube[i] = (T_SIDE**) create_2d_array();
    }
    return cube;
}   

void init_rubiks(T_SIDE ***cube){
    char current_color_array[6] = "RBGWYO";
    for (int i = 0; i < 6; i++){
        char current_color = current_color_array[i];
        for (int j = 0; j < 3; j++){
            for (int k = 0; k < 3; k++){
                cube[i][j][k] = (T_COLOR) current_color;
            }
        }
    }
}

void display_rubiks(T_SIDE ***cube){
    for (int i = 0; i < 6; i++){
        
        for (int j = 0; j < 3; j++){
            printf("\n");
            for (int k = 0; k < 3; k++){
                printf("%c", (T_COLOR) cube[i][j][k]);
            }
        }
        printf("\n\n");
    }
}



int main(){
    T_SIDE ***cube;
    cube = create_rubiks();
    init_rubiks(cube);
    display_rubiks(cube);

    return 0;
}
