# Francisco Javier Perez Martinez

COMP	= mpicc
OPT     = -O2 -w

all: contar run

contar: contar.c
	$(COMP)	$(OPT) -o contar contar.c

run:
	mpirun -np 8 ./contar

run6:
	mpirun -np 6 ./contar

run4:
	mpirun -np 4 ./contar

run2:
	mpirun -np 2 ./contar


clean:
		rm contar
