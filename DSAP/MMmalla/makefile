#Francisco Javier Perez Martinez

COMP	= mpicc
OPT     = -O3 -w

all: matriz run

matriz: matriz.c
	$(COMP)	$(OPT) -o matriz matriz.c -lm

run:
	mpirun --oversubscribe -np 9 ./matriz

clean:
		rm matriz
