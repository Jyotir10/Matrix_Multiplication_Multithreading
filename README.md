# Matrix_Multiplicstion_Multithreading
Matrix Multiplication Library Implementation

To run the program just type make and then ./threading. Steps : 1) open the terminal in a directory where all the 4 files (Make, threading.cpp, mat_Mul.cpp and mat_Mul.h are present). Then type in make and press enter. Then type ./threading.

You need to have mat_Mul.cpp and mat_Mul.h in the same directory to use the matrix multiplication and transpose functionalities. Just include mat_Mul.h in your main file (threading.cpp in my case). 
	#include "mat_Mul.h"
Threading.cpp is the main file that is needed to test all the functionalities. I just include the mat_Mul.h in it and then use make command.

Files submitted and description -
1) threading.cpp - contains the main function. The matrices are dynamically initialized here. The User gives in the dimensions of the Matrices. The functions for transpose and matrix multiplication are called here.
Functions defined here are :
	a) fill_Matrix - This functions fills the matrix with random numbers. I use rand() and srand() to implement this function. It returns
	nothing and takes in the address of the 2d array.
	/* 
	void fill_Matrix(int** matrix,int R,int C){
    		srand (time(NULL));
    		// assign values to allocated memory
		for (int i = 0; i < R; i++){
	    		for (int j = 0; j < C; j++){
				matrix[i][j] = rand()%10;
	    		}
		}
	}
	*/
	b) print_Matrix - this function is used to print the matrix so that we can check whether our answer is right for the corresponding input. 	Inputs for this function are the matrix and its dimensions. You have to correctly provide the dimensions of the matrix to this function 	otherwise you will get an error.
	// Code Snippet
	/* 
	void print_Matrix(int** matrix,int R,int C,string identifier){
    		std::cout<<"Matrix "<<identifier<<" is:"<<std::endl;
    		for (int i = 0; i < R; i++){
        		cout<<"[";
        		for (int j = 0; j < C; j++){
            			std::cout<<matrix[i][j]<<",";
        		}
        		std::cout<<"],"<<std::endl;
    		}
	}
	*/
	c) main function - calls all the function.
		
2) mat_Mul.cpp - This is the file where code for multiplication and transpose are implemented. Functions defined in this file are -
	a)  multiply_Dynamic_Matrices :
		This function returns the product of 2 matrices. The output type of this function is int**. The inputs for this function are:
 		1) Matrix 1
 		2) Matrix 2
 		3) Number of rows of matrix 1
 		4) Number of columns of matrix 1
 		5) Number of rows of matrix 2
 		6) Number of columns of matrix 2
		I have used Multi-threading for multiplying the 2 threads. This is the parent thread and it calls the children thread to do the work 		without stepping on each others toes (Without interfering with each others work).
	
	b) multiplication_Job_Thread :
		First Procedure of the threads being created. a is the struct of information required for every thread.
		This procedure is different for each thread. I have used POSIX threads for this Module. You can man the information for
		creating POSIX threads (read the man pages).
		pthread_create is used to create threads. pthread_create has 4 inputs/arguments :
		1) address of thread ID.
		2) attributes. If attributes == NULL then default attributes are used.
		3) function pointer of first procedure.
		4) this is the arguments for the first procedure.
		
		// a code snippet that is doing the actual multiplication.
		/* 
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
		*/
	
	c) transpose_Matrix :
		This Function computes the transpose of a matrix and returns the anwers (which is the transpose of a given input). The inputs are:
		1) A 2-D Matrix (int** type)
		2) Number of Rows of Input Matrix
		3) Number of Columns of Input Matrix
		Note - You have to enter the dimensions correctly other wise you will get error.
	
3) mat_Mul.h - contains the function definition of multiply_Dynamic_Matrices and transpose_Matrix. It also has a struct of thread_info. Every thread wants the number of rows and columns of both the matrices and the thread number. As you cannot pass more than 4 arguments in pthread create you will have to pass a struct (or I could have created a class). These struct will contain all the important and necessary information require by the thread. MAtrix 1 and 2 and also the answer matrix is passed via this struct.
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
