#include <stdio.h>
#include <stdlib.h>
#include "pack.h"


int main(){
    T_COLOR ***cube;
    cube = create_rubiks();
    init_rubiks(cube);
    display_rubiks(cube);


    return 0;
}
    