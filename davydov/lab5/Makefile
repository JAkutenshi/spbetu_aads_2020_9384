all: goal
	./start

goal: main.o
	g++ main.o -o start

main.0: main.cpp HashTable.h
	g++ -c main.cpp

clean:
	rm -f *.o
