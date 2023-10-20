CC = clang++
FLAGS = -std=c++11 -I include

multiplytest:
	$(CC) $(FLAGS) tests/multiplytest.cc src/vectormatrix.cc -o tests/multiplytest

activationtest:
	$(CC) $(FLAGS) tests/activationtest.cc src/activation.cc -o tests/activationtest

modeltest:
	$(CC) $(FLAGS) tests/modeltest.cc src/model.cc src/activation.cc src/initializer.cc src/vectormatrix.cc -o tests/modeltest

trainingdatatest:
	$(CC) $(FLAGS) tests/trainingdatatest.cc src/trainingdata.cc src/vectormatrix.cc -o tests/trainingdatatest

traintest:
	$(CC) $(FLAGS) tests/traintest.cc src/activation.cc src/cost.cc src/initializer.cc src/model.cc src/train.cc src/trainingdata.cc src/vectormatrix.cc -o tests/traintest

clean:
	rm tests/multiplytest tests/activationtest tests/modeltest tests/trainingdatatest