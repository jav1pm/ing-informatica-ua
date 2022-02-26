#FRANCISCO JAVIER PEREZ MARTINEZ  DNI: 74384305M

OPTS = -Wall -O3 -std=c++11

maxsum-bb: maxsum-bb.cc
	g++ ${OPTS} -o maxsum-bb maxsum-bb.cc

filter: filter.cc
	g++ ${OPTS} -o filter filter.cc

tar: maxsum-bb.cc makefile memoria.pdf
	tar cvfz 74384305M.tar.gz maxsum-bb.cc makefile memoria.pdf

all: maxsum-bb filter

clean:
	rm filter maxsum-bb
