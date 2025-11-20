/*------------------------------------------------------
* Filename: utils.c
* Description: implements Point structure and important functions
* Author: Golan Ziv & Amittai Kalisky [:-)]
-------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define QUEENS_AMOUNT 8

typedef struct{
    size_t x; // row position on board
    size_t y; // row position on board
    uint8_t placed; // 0 for not placed, 1 for placed
} Point;

Point build_point(size_t x, size_t y, uint8_t placed){
    Point p = {x, y, placed};
    return p;
}

// check if by given queen pos, and pawn pos, will the pawn be killed by the queen.
uint8_t is_q_killing(Point queen, Point pawn){
    long long dx, dy;
    
    if(!(queen.placed)) return 0; // if the queen is not place the pawn wont be killed

    if((queen.x == pawn.x)|| queen.y == pawn.y) return 1; // if the pawn on the same column or row it will be killed

    // to be in any diagonal of the queen, the difference of their xs and ys should be equal
    // like the linear function f(x) = x, any x1, x2 are in diagonal iff |f(x1) - f(x2)| == |x1 - x2| 
    dx = (long long)queen.x - (long long)pawn.x;
    dy = (long long)queen.y - (long long)pawn.y;

    // uses long long int to preven integer overflow with size_t turning to int!

    if(llabs(dx) == llabs(dy)) return 1; // if they are in the same diagonal the pawn will be killed

    return 0; // pawn will live
}

// checks if pawn will not be killed against multiple queens.
uint8_t are_qs_killing(Point queens[QUEENS_AMOUNT], Point pawn){
    for(int i = 0; i < QUEENS_AMOUNT; i++)
        if(is_q_killing(queens[i], pawn)) return 1; // if any queen kills pawn, he is dead

    return 0;
}

// given any array of points (no matter if placed) it will print the board marking empty
// cells in O and queens in X
void print_mat(Point queens[QUEENS_AMOUNT], size_t size){
    int has_queen = 0;
    for(size_t i = 0; i < size; i++){
        for(size_t j = 0; j < size; j++){
            has_queen = 0;
            for(int q = 0; q < QUEENS_AMOUNT; q++){
                if(queens[q].x == i && queens[q].y == j){
                    has_queen = 1;
                    break;
                }
            }
            printf("%-2s", has_queen ? "X" : "O");
        }
        printf("\n");
    
    }
}
