/*------------------------------------------------------
* Filename: queens.c
* Description: solves the 8 queens problem
* Author: Golan Ziv & Amittai Kalisky [:-)]
-------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

void allocate_n_mat(int ***mat, int n);
int fill_spots(int **mat, int x, int y, int n, int **change);
int rec(int **mat, int r, int q, int *sum, int n);

/*------------------------------------------------------
* Function Name - allocate_n_matrix
*
* Function Purpose - allocate matrix of size nXn, if failed, free memory and point to NULL
*
* Parameters –  [IN mat - matrix of integers] 
*               [IN n - matrix size] 
*
* Return Values - void
*
* Author - Golan Ziv [:-)] & Amittai Kalisky
-------------------------------------------------------*/

void allocate_n_mat(int ***mat, int n){
    int good = n;

    *mat = calloc(n, sizeof(int *));
    if(!*mat){
        printf("\nallocation failed");
        return;
    }

    for (int i = 0; i < n; i++){
        (*mat)[i] = calloc(n, sizeof(int));
        if(!(*mat)[i]){
            good = i;
            break;
        }
        for (int j = 0; j < n; j++)
            (*mat)[i][j] = 0;
    }

    if(good != n){
        for(int i = 0; i < good; i++)
            free((*mat)[i]);
        
        free((*mat));
        printf("\nallocation failed");
        mat = NULL;
    }
}
/*------------------------------------------------------
* Function Name - fill_spots
*
* Function Purpose - fill matrix in queen spots or aims with given mode
*
* Parameters –  [IN mat - matrix of integers] 
*               [IN x - row index] 
*               [IN y - column index] 
*               [IN n - matrix size] 
*               [IN change - int matrix to track what change, inorder to remove later] 
*
* Return Values - 0 if successfull, 1 for for failure
*
* Author - Golan Ziv [:-)] & Amittai Kalisky
-------------------------------------------------------*/
int fill_spots(int **mat, int x, int y, int n, int **change){
    if(!mat) return -1;

    mat[x][y] = 2;
    change[x][y] = 1;

    for(int i = 0; i < n ; i++){
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
    for(int i = 1; x + i < n && y + i < n; i++){
        if(!mat[x + i][y + i]){ 
            mat[x + i][y + i] = 1;
            change[x + i][y + i] = 1;
        }
    }
    for(int i = 1; x + i < n && y - i >= 0; i++){
        if(!mat[x + i][y - i]){ 
            mat[x + i][y - i] = 1;
            change[x + i][y - i] = 1;
        }
    }
    for(int i = 1; x - i >= 0 && y + i < n; i++){
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
*		        [IN sum – integer pointer to accumliate correct paths]
*		        [IN n – size of the matrix]
*
* Return Values - 0 for success, -1 for failure
*
* Author - Golan Ziv & Amittai Kalisky [:-)] 
-------------------------------------------------------*/
int rec(int **mat, int r, int q, int *sum, int n){
    int **change = NULL;
    if(q == 0){
        (*sum)++;
        return 0;
    }

    if(r == n)
        return -1;

    for(int col = 0; col < n; col++){
        if(!mat[r][col]){
            allocate_n_mat(&change, n);
            if(!change) return -1;
            
            fill_spots(mat, r, col, n, change);
            rec(mat, r+1, q-1, sum, n); 
        
            // reset queen placement.
            for(int i = 0; i < n; i++)
                for(int j = 0; j < n; j++)
                    if(change[i][j]) mat[i][j] = 0;

            for(int i = 0; i < n; i++)
                free(change[i]);
            free(change);
        }
    }
    return -1;
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
    int **mat = NULL;
    int n, sum = 0; 

    printf("please enter n for the queens problem: ");
    scanf(" %d", &n);
    
    allocate_n_mat(&mat, n);
    if(!mat) return -1;

    rec(mat, 0, 8, &sum, n);
    
    printf("\n found %d Ways to solve", sum);
    
    return 0;
}    
