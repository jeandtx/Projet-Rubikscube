#include <stdio.h>
#include <stdlib.h>
#include "pack.h"


int main(){
    T_COLOR ***cube;
    cube = create_rubiks();
    init_rubiks(cube, "blank");
    display_rubiks(cube, 'o');
    return 0;
}


/*
To run for jean:
cd "/Users/jeandtx/Documents/Projet-Rubikscube/" && gcc -lcurses main.c -o main && "/Users/jeandtx/Documents/Projet-Rubikscube/"main

To run for Oscar:
cd "/home/oscar/Documents/Efrei/c_tries/Projet-Rubikscube/" && gcc main.c -o main -lncurses && "/home/oscar/Documents/Efrei/c_tries/Projet-Rubikscube/"main&& gcc main.c -o main -lncurses && main 

For you teacher, 
You can try by taking example of the code above Jean is on mac and Oscar is on linux
If you are on windows, good luck ;)
*/
