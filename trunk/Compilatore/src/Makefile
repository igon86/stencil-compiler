

compila:
	python compilatore.py

worker:
	mpicc -g -lm -w -DDEBUG -DGENERATO ./testBench/compilato.c ./testBench/supporto.c ./testBench/algebric.c -o ./testBench/worker

testw:
	mpirun -np 4 ./testBench/worker

clean:
	rm -f sectionCalc*
	rm -f sectionComm*
	rm -f output
	rm -f ./testBench/PROCESSO*
	rm -f ./testBench/matrix*
	rm -f ./stepModel
	rm -f ./stepModelShift
	rm -f *.pyc
	rm -f ./UNIT_TEST/section*
