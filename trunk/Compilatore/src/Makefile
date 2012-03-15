	
compila:
	python compilatore.py

worker:
	mpicc -g -Wall -pedantic -lm -w -DDEBUG -DGENERATO ./testBench/compilato.c ./testBench/supporto.c ./testBench/algebric.c -o ./testBench/worker

all: clean compila worker

clean:
	rm -f sectionCalc*
	rm -f sectionComm*
	rm -f output
	rm -f ./testBench/PROCESSO*
	rm -f ./testBench/matrix*
	rm -f ./testBench/conf.h
	rm -f ./testBench/compilato.c
	rm -f ./stepModel
	rm -f ./stepModelShift
	rm -f *.pyc
	rm -f ./UNIT_TEST/section*
	rm -f ./testBench/outMPI
	rm -f ./UNIT_TEST/outputCompilatore
	rm -f ./UNIT_TEST/stepModel*