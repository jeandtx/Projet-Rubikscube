#include <stdio.h>
#include <stdlib.h>
#include "pack.h"


int main(){
    T_COLOR ***cube;
    cube = create_rubiks();
    init_rubiks(cube);
    user_interface(cube, 'o');
    return 0;
}



/*
To run for jean:
cd "/Users/jeandtx/Documents/Projet-Rubikscube/" && gcc -lcurses main.c -o main && "/Users/jeandtx/Documents/Projet-Rubikscube/"main

To run for Oscar:
cd "/home/oscar/Documents/Efrei/c_tries/Projet-Rubikscube/" && gcc main.c -o main -lncurses && "/home/oscar/Documents/Efrei/c_tries/Projet-Rubikscube/"main&& gcc main.c -o main -lncurses && main 
*/