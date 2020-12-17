all: goal
	./start

goal: main.o
	g++ main.o -o start

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm -f *.o
