#
# This is the Makefile that can be used to create the matrix multiplication executable
# To create "matrix multiplication" executable, do:
#	make
#
threading: threading.o mat_Mul.o
	g++ -o threading -g threading.o mat_Mul.o -lpthread -lm

threading.o: threading.cpp mat_Mul.h
	g++ -g -c -Wall threading.cpp

mat_Mul.o: mat_Mul.cpp mat_Mul.h
	g++ -g -c -Wall mat_Mul.cpp

clean:
	rm -f *.o threading