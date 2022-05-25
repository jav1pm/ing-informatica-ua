#Francisco Javier Perez Martinez

COMP	= mpicc
OPT     = -O2 -w

all: mvcl run

mvcl: mvcl.c
	$(COMP)	$(OPT) -o mvcl mvcl.c

run:
	mpirun -np 4 ./mvcl

clean:
		rm mvcl
