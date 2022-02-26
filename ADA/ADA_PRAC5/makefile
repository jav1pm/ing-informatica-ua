#FRANCISCO JAVIER PEREZ MARTINEZ  DNI: 74384305M
OPTS = -Wall -O3 -std=c++0x

all: pow2 pow2.llamadasRecursivas graphs

pow2: pow2.cc
	g++ ${OPTS} -o pow2 pow2.cc

pow2.llamadasRecursivas: pow2
	./pow2 > pow2.llamadasRecursivas

graphs: pow2.llamadasRecursivas pow2.gnuplot
	gnuplot pow2.gnuplot

tar: pow2.cc pow2.gnuplot makefile
	tar cvfz 74384305M.tar.gz pow2.cc pow2.gnuplot makefile
