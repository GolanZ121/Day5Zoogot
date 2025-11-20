/*------------------------------------------------------
* Filename: queens00.c
* Description: solves the 8 queens problem
* Author: Golan Ziv & Amittai Kalisky [:-)]
-------------------------------------------*/

#include "utils.h"

void rec(Point queens_points[QUEENS_AMOUNT], 
    size_t queens_left, // amount of queens left to place
    size_t row, // current row to place a queen (in recursion we try every column in that row)
    size_t size, // size of the board
    size_t *solutions, // a pointer to in to accumilate the number of successes
    Point result[QUEENS_AMOUNT]) // array to save postions of a solution to some solution
    {
    size_t next_queen_idx = QUEENS_AMOUNT - queens_left;

    if(queens_left > QUEENS_AMOUNT) return; // Invalid situation, just leave

    if(queens_left == 0){
        if((*solutions) < UINT_MAX) // make sure to not over flow (cap solutions count)
            (*solutions)++; // accumilate succuss
        for(int q = 0 ; q < QUEENS_AMOUNT; q++)
            result[q] = queens_points[q]; // save to result to outside variable
        return;
    }

    if(row == size)
        return;

    for(size_t col = 0; col < size; col++){
        Point curr = build_point(row, col, 1);

        if(!are_qs_killing(queens_points, curr)){ // if can be placed, try to place and make a recursive call
            queens_points[next_queen_idx] = curr;

            rec(queens_points, queens_left - 1, row + 1, size, solutions, result);

            queens_points[next_queen_idx].placed = 0; // we need to pick up the queen pieace to not interfere the next calls
        }
    }
}


int main(){
    Point queens[QUEENS_AMOUNT] = {0}; // init empty Point struct
    Point result[QUEENS_AMOUNT] = {0};
    size_t size; // size of board to be taken from use
    size_t solutions = 0; 

    printf("Enter board size: ");
    if(scanf("%zu", &size) != 1){
        printf("Bad Input!");
        return 1;
    }
    
    rec(queens, QUEENS_AMOUNT, 0, size, &solutions, result);
    if(solutions){
        printf("%d Solutions found! Here is One:\n", solutions);
        print_mat(result, size);
    }else
        printf("Solution NOT found!\n");

    return 0;

}