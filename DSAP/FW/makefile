#Francisco Javier Perez Martinez

COMP	= mpicc
OPT     = -O3 -w

all: fw run

fw: fw.c
	$(COMP)	$(OPT) -o fw fw.c -lm

run:
	mpirun -np 3 ./fw

sec-comp:
	gcc -o secFW secFloyd_Warshall.c -lm

sec-run:
	./secFW

clean:
		rm fw secFW
