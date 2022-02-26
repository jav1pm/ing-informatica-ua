OPTS = -Wall -O3 -std=c++0x

bubbleSort: bubbleSort.cc
	g++ ${OPTS} -o bubbleSort bubbleSort.cc	 

bubbleSort.CPUtimes: bubbleSort
	./bubbleSort > bubbleSort.CPUtimes

graphs: bubbleSort.CPUtimes bubbleSort.gnuplot
	gnuplot bubbleSort.gnuplot

all: bubbleSort bubbleSort.CPUtimes graphs

tar: bubbleSort.cc bubbleSort.gnuplot makefile
	tar cvfz mi_DNI-NIE.tar.gz bubbleSort.cc bubbleSort.gnuplot makefile

clean: 
	rm bubbleSort bubbleSort.CPUtimes fit.log bubbleSort*.png *~
 
