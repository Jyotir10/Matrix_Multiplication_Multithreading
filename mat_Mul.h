#include <pthread.h>
#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <iostream>

// thread_info contains all the information required  for the thread to make the necessary calculations
typedef struct {
    int** matrix1_Add;
    int** matrix2_Add;
    int** ans_Mat;
    int row;
    int col;
    int thread_ID;
    int row_MatrixB;
    int col_MatrixA;
} thread_info;

int** multiply_Dynamic_Matrices(int** matrix1,int** matrix2,int number_of_Rows_Matrix1,int number_of_Columns_Matrix1,int number_of_Rows_Matrix2,int number_of_Columns_Matrix2);

int** transpose_Matrix(int** matrix_Input,int rows_Input,int columns_Input);