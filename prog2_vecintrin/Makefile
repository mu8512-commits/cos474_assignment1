all: myexp

logger.o: logger.cpp logger.h prog2_intrin.h prog2_intrin.cpp
	g++ -c logger.cpp

prog2_intrin.o: prog2_intrin.cpp prog2_intrin.h logger.cpp logger.h
	g++ -c prog2_intrin.cpp

myexp: prog2_intrin.o logger.o main.cpp prog2.cpp
	g++ -I../common logger.o prog2_intrin.o main.cpp prog2.cpp -o myexp

clean:
	rm -f *.o myexp *~
