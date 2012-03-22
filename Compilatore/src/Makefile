FLAGS = -g -w -fopenmp -Wall -pedantic -lm -DDEBUG

compila:
	python compilatore.py

worker:
	mpicc $(FLAGS) ./testBench/compilato.c ./testBench/supporto.c ./testBench/algebric.c -o ./testBench/worker

all: clean compila worker

clean:
	rm -f sectionCalc*
	rm -f sectionComm*
	rm -f output
	rm -f ./benchmark
	rm -f ./testBench/PROCESSO*
	rm -f ./testBench/matrix*
	rm -f ./testBench/conf.h
	rm -f ./testBench/compilato.c
	rm -f ./stepModel
	rm -f ./stepModelShift
	rm -f *.pyc
	rm -f ./UNIT_TEST/section*
	rm -f ./UNIT_TEST/benchmark
	rm -f ./testBench/outMPI
	rm -f ./UNIT_TEST/outputCompilatore
	rm -f ./UNIT_TEST/stepModel*
	rm -f ./outputCompilatore