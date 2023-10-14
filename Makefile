CC = clang++
FLAGS = -std=c++11 -I include

multiplytest:
	$(CC) $(FLAGS) tests/multiplytest.cc src/vectormatrix.cc -o tests/multiplytest

activationtest:
	$(CC) $(FLAGS) tests/activationtest.cc src/activation.cc -o tests/activationtest

modeltest:
	$(CC) $(FLAGS) tests/modeltest.cc src/model.cc src/activation.cc src/initializer.cc src/vectormatrix.cc -o tests/modeltest

clean:
	rm tests/multiplytest tests/activationtest tests/modeltest