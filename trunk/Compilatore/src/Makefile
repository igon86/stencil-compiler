compila:
	python compilatore.py

worker:
	mpicc -g -lm -w -DDEBUG -DGENERATO ./testBench/compilato.c ./testBench/supporto.c ./testBench/algebric.c -o worker

testw:
	mpirun -np 4 ./testBench/worker