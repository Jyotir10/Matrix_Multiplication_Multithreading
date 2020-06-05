#include <iostream>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mat_Mul.h"

using namespace std;

//this function takes in the 2-D matrix and its dimensions and fills it with random numbers
void fill_Matrix(int** matrix,int R,int C){
    srand (time(NULL));
    // assign values to allocated memory
	for (int i = 0; i < R; i++){
	    for (int j = 0; j < C; j++){
			matrix[i][j] = rand()%10;
	    }
	}
}// fill_Matrix()

// This function takes in the 2-D matrix and its dimensions. It prints out the matrix
void print_Matrix(int** matrix,int R,int C,string identifier){
    std::cout<<"Matrix "<<identifier<<" is:"<<std::endl;
    for (int i = 0; i < R; i++){
        cout<<"[";
        for (int j = 0; j < C; j++){
            std::cout<<matrix[i][j]<<",";
        }
        std::cout<<"],"<<std::endl;
    }
}//print_Matrix()

int main(){
    int row_Matrix_A;
    int columns_Matrix_A;
    int row_Matrix_B;
    int columns_Matrix_B;
    cout<<"Enter the number of rows of matrix 1 : ";
	cin>>row_Matrix_A;
	cout<<"Enter the number of columns of matrix 1 : ";
	cin>>columns_Matrix_A;
	cout<<"Enter the number of rows of matrix 2 : ";
	cin>>row_Matrix_B;
	cout<<"Enter the number of columns of matrix 2 : ";
	cin>>columns_Matrix_B;

    // Initializing 2-D Matrices
    int **matrixA = new int*[row_Matrix_A]; // get an array of Integer Pointers
    int **matrixB = new int*[row_Matrix_B]; // get an array of Integer Pointers
    for(int i=0;i<row_Matrix_A;i++){
        matrixA[i] = new int[columns_Matrix_A]; // every pointer pointing to an array of integers of size columns_Matrix_A
    }
    for(int i=0;i<row_Matrix_B;i++){
        matrixB[i] = new int[columns_Matrix_B]; // every pointer pointing to an array of integers of size columns_Matrix_B
    }// Done initializing my 2-D Matrices

    // Fill the 2 matrices with random numbers
    fill_Matrix(matrixA,row_Matrix_A,columns_Matrix_A);
    fill_Matrix(matrixB,row_Matrix_B,columns_Matrix_B);

    // To print the matrices. This function is just used to print the matrix and checking the values.
    print_Matrix(matrixA,row_Matrix_A,columns_Matrix_A,"A");
    print_Matrix(matrixB,row_Matrix_B,columns_Matrix_B,"B");

    int** ans = multiply_Dynamic_Matrices(matrixA,matrixB,row_Matrix_A,columns_Matrix_A,row_Matrix_B,columns_Matrix_B);// getting the multiplication of two matrices
    print_Matrix(ans,row_Matrix_A,columns_Matrix_B,"Multiplication");// printing out the answer

    int** transposeans  = transpose_Matrix(matrixB,row_Matrix_B,columns_Matrix_B); // getting the transpose of a matrix (Matrix B)
    print_Matrix(transposeans,columns_Matrix_B,row_Matrix_B,"Transpose"); // printing out the answer of transpose

    return 0;
}// main()