# Francisco Javier Perez Martinez

COMP	= mpicc
OPT     = -O3 -w

all: anillo run

anillo: anillo.c
	$(COMP)	$(OPT) -o anillo anillo.c

run:
	mpirun -np 2 ./anillo

clean:
		rm anillo