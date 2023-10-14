CC = clang++
FLAGS = -std=c++11 -I include

multiplytest:
	$(CC) $(FLAGS) tests/multiplytest.cc src/vectormatrix.cc -o tests/multiplytest

clean:
	rm tests/multiplytest