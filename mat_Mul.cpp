#include "mat_Mul.h"

using namespace std;

/* First Procedure of the threads being created. a is the struct of information required for every thread.
This procedure is different for each thread. I have used POSIX threads for this Module. You can man the information for
creating POSIX threads (read the man pages).
pthread_create is used to create threads. pthread_create has 4 inputs/arguments :
1) address of thread ID.
2) attributes. If attributes == NULL then default attributes are used.
3) function pointer of first procedure.
4) this is the arguments for the first procedure.
*/
void * multiplication_Job_Thread(void *a){
    thread_info* obj = (thread_info *)a;
    int thread_Number = obj->thread_ID;
    int columns_of_Answer_Matrix = obj->col; // number of columns of the answer matrix
    int columns_of_MatrixA = obj->col_MatrixA; // number of columns of matrix A
    int **m1 = obj->matrix1_Add;
    int **m2 = obj->matrix2_Add;
    int **ansmat = obj->ans_Mat;

    int row = thread_Number; // I have the row number here
    int col;
    int i,t;

    for(col = 0;col < columns_of_Answer_Matrix;col++){
        t = 0;
        for(i = 0;i<columns_of_MatrixA;i++){
            t += m1[row][i] * m2[i][col];
        }
        ansmat[row][col] = t;
    }
    return NULL;
}// multiplication_Job_Thread()

/* This function returns the product of 2 matrices. The output type of this function is int**. The inputs for this function are:
 1) Matrix 1
 2) Matrix 2
 3) Number of rows of matrix 1
 4) Number of columns of matrix 1
 5) Number of rows of matrix 2
 6) Number of columns of matrix 2
 */
int** multiply_Dynamic_Matrices(int** matrix1,int** matrix2,int number_of_Rows_Matrix1,int number_of_Columns_Matrix1,int number_of_Rows_Matrix2,int number_of_Columns_Matrix2){
    //If the columns of Matrix 1 != rows of Matrix 2 then matrix multiplication is not possible
    if(number_of_Columns_Matrix1!=number_of_Rows_Matrix2){
       std::cout<<"Matrix Multiplication is not possible. The number of columns of matrix 1 is not equal to the number of rows of matrix 2."<<std::endl;
       exit(0);
    }// Exit the program if the condition is not met

    //setting up answer array (2D)
    int **ans_Matrix = new int*[number_of_Rows_Matrix1]; // get an array of Integer Pointers
    for(int i=0;i<number_of_Rows_Matrix1;i++){
       ans_Matrix[i] = new int[number_of_Columns_Matrix2]; // every pointer pointing to an array of integers of size columns_Matrix_B
    }

    int no_of_Threads = number_of_Rows_Matrix1; // number of threads = number of rows in Matrix A

    pthread_t thread_IDs[no_of_Threads];// Array for threads created
    thread_info thread_Data_Object[no_of_Threads];// Array for the thread information that we pass to the threads created

    int i;
    for(i=0;i<no_of_Threads;i++){
        thread_info info = {matrix1,matrix2,ans_Matrix,number_of_Rows_Matrix1,number_of_Columns_Matrix2,i,number_of_Rows_Matrix2,number_of_Columns_Matrix1};
        thread_Data_Object[i] = info;
        pthread_create(&thread_IDs[i],NULL,multiplication_Job_Thread,&thread_Data_Object[i]);
    }// Created threads

    int j;
    for(j=0;j<no_of_Threads;j++){
        pthread_join(thread_IDs[j],NULL);
    }// waiting for all the threads to finish work and return

    return ans_Matrix; // returning the multiplication answer
}// multiply_Dynamic_Matrices()

/* This Function computes the transpose of a matrix and returns the ans (which is the transpose of a given input). The inputs are:
1) A 2-D Matrix (int** type)
2) Number of Rows of Input Matrix
3) Number of Columns of Input Matrix
Note - You have to enter the dimensions correctly other wise you will get error.
*/
int** transpose_Matrix(int** matrix_Input,int rows_Input,int columns_Input){
    //Make the Output array
    int **matrix_Ans = new int*[columns_Input]; // get an array of Integer Pointers
    for(int i=0;i<columns_Input;i++){
        matrix_Ans[i] = new int[rows_Input]; // every pointer pointing to an array of integers of size columns_Matrix_A
    }// Setting up the correct dimensions of the output array

    int i, j;
    for (i = 0; i < columns_Input; i++){
        for (j = 0; j < rows_Input; j++){
            matrix_Ans[i][j] = matrix_Input[j][i];
        }
    } // Compute the transpose

    return matrix_Ans; // return the answer

}// transpose_Matrix