/*------------------------------------------------------
* Filename: queens.c
* Description: solves the 8 queens problem
* Author: Golan Ziv & Amittai Kalisky [:-)]
-------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 8
int ** deep_copy(int **mat);
int fill_spots(int **mat, int x, int y);
int rec(int **mat, int r, int q, int***res, int* sum);
void print_mat(int ** mat);
void free_matrix(int **mat);


/*------------------------------------------------------
* Function Name - deep_copy
*
* Function Purpose - deep copies an int matrix
*
* Parameters –  [IN mat - matrix of integers] 
*
* Return Values - matrix of integers (in new memory block)
*
* Author - Golan Ziv [:-)] & Amittai Kalisky
-------------------------------------------------------*/
int ** deep_copy(int **mat){
    int ** copy = malloc(SIZE * sizeof(int *));

    if(!copy) return NULL;

    for (int i = 0; i < SIZE; i++){
        copy[i] = malloc(SIZE * sizeof(int));
        if(!copy[i]) {
            free_matrix(copy);
            return NULL;
        }
        for (int j = 0; j < SIZE; j++){
            copy[i][j] = mat[i][j];
        }
    }
    return copy;
}

/*------------------------------------------------------
* Function Name - fill_spots
*
* Function Purpose - fills spots of a matrix (in 1's and 2's) given a queen position
*
* Parameters – int **matrix - the matrix. int x, y - positions of the new queen.
*
* Return Values - -1 for failure, 0 for success
*
* Author - Golan Ziv [:-)] & Amittai Kalisky
-------------------------------------------------------*/
int fill_spots(int **mat, int x, int y){
    if(!mat) return -1;
    mat[x][y] = 2;

    for(int i = 0; i < SIZE ; i++){
        if(!mat[i][y]) mat[i][y] = 1;   
        if(!mat[x][i]) mat[x][i] = 1;
    }

    for(int i = 1; ((x - i) >= 0) && ((y - i) >= 0); i++)
        if(!mat[x - i][y - i]) mat[x - i][y - i] = 1;  
    

    for(int i = 1; ((x + i) < SIZE) && ((y + i) < SIZE); i++)
        if(!mat[x + i][y + i]) mat[x + i][y + i] = 1;
    

    for(int i = 1; ((x + i) < SIZE) && ((y - i) >= 0); i++)
        if(!mat[x + i][y - i]) mat[x + i][y - i] = 1;
    

    for(int i = 1; ((x - i) >= 0) && ((y + i) < SIZE); i++)
        if(!mat[x - i][y + i]) mat[x - i][y + i] = 1;
    
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
*		        [IN res – pointer to matrix where we save the result]
*
* Return Values - 0 for success, -1 for failure
*
* Author - Golan Ziv & Amittai Kalisky [:-)] 
-------------------------------------------------------*/
int rec(int **mat, int r, int q, int***res, int* sum){
    if(q == 0){
        *res = deep_copy(mat);
        (*sum)++;
        return 0;
    }

    if(r == SIZE){
        return -1;
    }

    for(int col = 0; col < SIZE; col++){
        if(!mat[r][col]){
            int ** curr= deep_copy(mat);
            if(!curr) return -1;
            
            fill_spots(curr, r, col);
            rec(curr, r+1, q-1, res, sum);
            free_matrix(curr);
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
void print_mat(int ** mat){
   for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            printf("%2d", mat[i][j]);
        }
        printf("\n");
    }
}

/*------------------------------------------------------
* Function Name - mai
*
* Function Purpose - makes a matrix and runs the recurssion, then prints the final configuration.
*
* Parameters –  void.
*
* Return Values - 0 for success, -1 for failure
*
* Author - Golan Ziv & Amittai Kalisky [:-)] 
-------------------------------------------------------*/
int main() {
    int **mat = malloc(SIZE * sizeof(int *));
    if (mat == NULL){
        return -1;
    }
    int **res = NULL;
    int sum = 0;
    for (int i = 0; i < SIZE; i++){
        mat[i] = malloc(SIZE * sizeof(int));
        if (mat[i] == NULL){
            return -1;
        }
        for (int j = 0; j < SIZE; j++){
            mat[i][j] = 0;
        }
    }

    rec(mat, 0, 8, &res, &sum);

    if(!res){
        printf("no solution");
        return -1;
    }

    print_mat(res);
    printf("\nTotal solutions found: %d", sum);
 
    // Your code here
    free_matrix(res);
    free_matrix(mat);
    return 0;
}    

/*------------------------------------------------------
* Function Name - free_matrix
*
* Function Purpose - frees matrix
*
* Parameters –  matrix
*
* Return Values - void
*
* Author - Golan Ziv [:-)] & Amittai Kalisky
-------------------------------------------------------*/
void free_matrix(int **mat){
    for (int i = 0; i < SIZE; i++){
        if (mat[i] != NULL){
            free(mat[i]);
        }
    }
    if (mat != NULL){
        free(mat);
    }
}