OPTS=-Wall -g -std=c++11
OBJS=prac3.o Chatbot.o Intent.o Example.o Util.o
CC=g++

prac3: $(OBJS)
	$(CC) $(OPTS) $(OBJS) converter.o -o prac3

prac3.o: prac3.cc Chatbot.h Intent.h Util.h
	$(CC) $(OPTS) -c prac3.cc

Chatbot.o: Chatbot.cc Chatbot.h Intent.h Example.h Util.h
	$(CC) $(OPTS) -c Chatbot.cc

Intent.o: Intent.cc Intent.h Example.h Util.h
	$(CC) $(OPTS) -c Intent.cc

Example.o: Example.cc Example.h Util.h
	$(CC) $(OPTS) -c Example.cc

Util.o: Util.cc Util.h
	$(CC) $(OPTS) -c Util.cc

clean:
	rm $(OBJS)
