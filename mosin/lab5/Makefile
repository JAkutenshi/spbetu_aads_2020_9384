all: goal
	./a.out

goal: main.o
	g++ main.o

main.o: main.cpp tree.h
	g++ -c main.cpp

clean:
	rm -f *.o
