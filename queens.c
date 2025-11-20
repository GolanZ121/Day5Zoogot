#include <stdio.h>
#include <stdlib.h>


#define SIZE 8
int ** deep_copy(int **mat);
int fill_spots(int **mat, int x, int y);
int rec(int **mat, int r, int q, int***res);
void print_mat(int ** mat);
void free_matrix(int **mat);


int ** deep_copy(int **mat){
    int ** copy = malloc(SIZE * sizeof(int *));
    // 
    for (int i = 0; i < SIZE; i++){
        copy[i] = malloc(SIZE * sizeof(int));
        for (int j = 0; j < SIZE; j++){
            copy[i][j] = mat[i][j];
        }
    }
    return copy;
}

int fill_spots(int **mat, int x, int y){
    mat[x][y] = 2;

    for(int i = 0; i < SIZE ; i++){
        if(!mat[i][y]) mat[i][y] = 1;   
        if(!mat[x][i]) mat[x][i] = 1;
    }

    for(int i = 1; ((x - i) >= 0) && ((y - i) >= 0); i++){
        if(!mat[x - i][y - i]) 
            mat[x - i][y - i] = 1;  
    }

    for(int i = 1; ((x + i) < SIZE) && ((y + i) < SIZE); i++){
        if(!mat[x + i][y + i]) {
            mat[x + i][y + i] = 1;
            
        }
    }

    for(int i = 1; ((x + i) < SIZE) && ((y - i) >= 0); i++){
        if(!mat[x + i][y - i]) {
            mat[x + i][y - i] = 1;
            
        }
    }

    for(int i = 1; ((x - i) >= 0) && ((y + i) < SIZE); i++){
        if(!mat[x - i][y + i]) {
            mat[x - i][y + i] = 1;
        }
    }
    
    return 1;
}

int rec(int **mat, int r, int q, int***res){
    if(q == 0){
        *res = deep_copy(mat);
        return 0;
    }

    if(r == SIZE){
        return -1;
    }

    for(int col = 0; col < SIZE; col++){
        if(!mat[r][col]){
            int ** curr= deep_copy(mat);
            fill_spots(curr, r, col);
            if(rec(curr, r+1, q-1, res))
                return -1;
        }
    }
    return 0;
} 




void print_mat(int ** mat){
   for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            printf("%2d", mat[i][j]);
        }
        printf("\n");
    }
}


int main() {
    int **mat = malloc(SIZE * sizeof(int *));
    int **res = NULL;
    
    for (int i = 0; i < SIZE; i++){
        mat[i] = malloc(SIZE * sizeof(int));
        if (mat[i] == NULL){
            return -1;
        }
        for (int j = 0; j < SIZE; j++){
            mat[i][j] = 0;
        }
    }

    rec(mat, 0, 8, &res);

    if(!res){
        printf("no solution");
        return -1;
    }

    print_mat(res);
    
 
    // Your code here
    free(res);
    free(mat);
    return 0;
}    

void free_matrix(int **mat){
    for (int i = 0; i < SIZE; i++){
        free(mat[i]);
    }
    free(mat);
}






























































































































