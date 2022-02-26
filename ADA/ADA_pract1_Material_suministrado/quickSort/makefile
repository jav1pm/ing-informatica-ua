#FRANCISCO JAVIER PEREZ MARTINEZ  DNI: 74384305M
OPTS = -Wall -O3 -std=c++0x

quickSort: quickSort.cc
	g++ ${OPTS} -o quickSort quickSort.cc	 

quickSort.CPUtimes: quickSort
	./quickSort > quickSort.CPUtimes

graphs: quickSort.CPUtimes quickSort.gnuplot
	gnuplot quickSort.gnuplot

all: quickSort quickSort.CPUtimes graphs

tar: quickSort.cc quickSort.gnuplot makefile
	tar cvfz 74384305M.tar.gz quickSort.cc quickSort.gnuplot makefile

clean: 
	rm quickSort quickSort.CPUtimes fit.log quickSort*.png *~
 
