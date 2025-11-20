/*------------------------------------------------------
* Filename: queens.c
* Description: solves the 8 queens problem
* Author: Golan Ziv & Amittai Kalisky [:-)]
-------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 8

int fill_spots(int mat[SIZE][SIZE], int x, int y, int change[SIZE][SIZE]);
int rec(int mat[SIZE][SIZE], int r, int q);
void print_mat(int mat[SIZE][SIZE]);


/*------------------------------------------------------
* Function Name - fill_spots
*
* Function Purpose - feel matrix in queen spots or aims with given mode
*
* Parameters –  [IN mat - matrix of integers] 
*               [IN x - row index] 
*               [IN y - column index] 
*               [IN change - int matrix to track what change, inorder to remove later] 
*
* Return Values - 0 if successfull, 1 for for failure
*
* Author - Golan Ziv [:-)] & Amittai Kalisky
-------------------------------------------------------*/
int fill_spots(int mat[SIZE][SIZE], int x, int y, int change[SIZE][SIZE]){
    if(!mat) return -1;

    mat[x][y] = 2;
    change[x][y] = 1;

    for(int i = 0; i < SIZE ; i++){
        if(!mat[i][y]) {
            change[i][y] = 1;
            mat[i][y] = 1;
        }if(!mat[x][i]) {
            change[x][i] = 1;
            mat[x][i] = 1;
        }
    }

    for(int i = 1; x - i >= 0 && y - i >= 0; i++){
        if(!mat[x - i][y - i]){ 
            mat[x - i][y - i] = 1; 
            change[x - i][y - i] = 1; 
        }
    }
    for(int i = 1; x + i < SIZE && y + i < SIZE; i++){
        if(!mat[x + i][y + i]){ 
            mat[x + i][y + i] = 1;
            change[x + i][y + i] = 1;
        }
    }
    for(int i = 1; x + i < SIZE && y - i >= 0; i++){
        if(!mat[x + i][y - i]){ 
            mat[x + i][y - i] = 1;
            change[x + i][y - i] = 1;
        }
    }
    for(int i = 1; x - i >= 0 && y + i < SIZE; i++){
        if(!mat[x - i][y + i]){ 
            mat[x - i][y + i] = 1;
            change[x - i][y + i] = 1;
        }
    }
    return 0;
}


/*------------------------------------------------------
* Function Name - rec
*
* Function Purpose - recursivley calculate the 8 queen problem
*
* Parameters –  [IN mat - matrix showing 0 for free spot, 1 for danger, 2 for placed queen] 
*		        [IN r  – row number]
*		        [IN q – number of queens we try to place]
*
* Return Values - 0 for success, -1 for failure
*
* Author - Golan Ziv & Amittai Kalisky [:-)] 
-------------------------------------------------------*/
int rec(int mat[SIZE][SIZE], int r, int q){
    if(q == 0)
        return 0;

    if(r == SIZE)
        return -1;

    for(int col = 0; col < SIZE; col++){
        if(!mat[r][col]){
            int change[SIZE][SIZE] = {0};
            fill_spots(mat, r, col, change);
            if(rec(mat, r+1, q-1) == 0)
                return 0;
            
            // reset queen placement.
            for(int i = 0; i < SIZE; i++)
                for(int j = 0; j < SIZE; j++)
                    if(change[i][j]) mat[i][j] = 0;
        }
    }
    return -1;
} 

/*------------------------------------------------------
* Function Name - print_mat 
*
* Function Purpose - print an int matrix in a formmated 
*
* Parameters –  [IN mat - an int matrix] 
*
* Return Values - void
*
* Author - Golan Ziv & Amittai Kalisky [:-)] 
-------------------------------------------------------*/
void print_mat(int mat[SIZE][SIZE]){
   for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            printf("%2d", mat[i][j]);
        }
        printf("\n");
    }
}

/*------------------------------------------------------
* Function Name - main
*
* Function Purpose - makes a matrix and runs the recurssion, then prints the final configuration.
*
* Return Values - 0 for success, -1 for failure
*
* Author - Golan Ziv & Amittai Kalisky [:-)] 
-------------------------------------------------------*/
int main() {
    int mat[SIZE][SIZE];

    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            mat[i][j] = 0;
        }
    }

    if(!rec(mat, 0, 8) == 0){
        printf("\nSolution NOT found");
        return 1;
    }
    
    printf("\nSolution found!");
    
    return 0;
}    
