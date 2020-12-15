all: goal
	./start

goal: main.o
	g++ main.o -o start

main.o: main.cpp Coder.h List.h
	g++ -c main.cpp

clean:
	rm -f *.o