#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 21;
#define COLS 11;
#define TRUE 1;
#define FALSE 0;

typedef struct {
    int **data;
    int width, row, col;
} tetromino;

const tetromino shapes[6] = {
    {(int *[])
        {(int []){0,1,1}
        ,(int []){1,1,0}
        ,(int []){0,0,0}}, 3}, 

    {(int *[])
        {(int []){1,1,0}
        ,(int []){0,1,1}
        ,(int []){0,0,0}}, 3},   

    {(int *[])
        {(int []){0,1,0}
        ,(int []){1,1,1}
        ,(int []){0,0,0}}, 3},  

    {(int *[])
        {(int []){0,0,1}
        ,(int []){1,1,1}
        ,(int []){0,0,0}}, 3},            

    {(int *[])
        {(int []){1,1}
        ,(int []){1,1}}, 2}, 

    {(int *[])
        {(int []){0,0,0,0}
        ,(int []){1,1,1,1}
        ,(int []){0,0,0,0}
        ,(int []){0,0,0,0}}, 4}
};

tetromino CopyMino(tetromino tetro){
    tetromino temp = tetro;
    int **copyData = tetro.data;

    temp.data = (int**)malloc(temp.width*sizeof(int*));

    int i, j;
    for(i = 0; i < temp.width; i++){
        temp.data[i] = (int*)malloc(temp.width*sizeof(int));
        for(j = 0; j < temp.width; j++){
            temp.data[i][j] = copyData[i][j];
        }
    }

    return temp;
}

void DeleteMino(tetromino tetro){
    int i;

    for(i = 0; i < tetro.width; i++){
        free(tetro.data[i]);
    }
    free(tetro.data);
}

void RotateMino(tetromino tetro){
    tetromino temp = CopyMino(tetro);
    int swapCol, elem, swapRow, width;

    width = tetro.width;
    for(swapCol = 0; swapCol < width; swapCol++){
        for(elem = 0, swapRow = width-1; elem < width; elem++, swapRow--){
            tetro.data[swapCol][elem] = temp.data[swapRow][swapCol];
        }
    }

    DeleteMino(temp);
}


typedef struct {
    //Game variables
    int row;
    int col;
    int score;
    int running;
    int time;

    //Current and next block
    tetromino current;
    tetromino next;


    int *board;
} game;

