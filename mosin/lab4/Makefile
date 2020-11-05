all: goal
	./a.out

goal: main.o
	g++ main.o

main.o: main.cpp stack.h
	g++ -c main.cpp

clean:
	rm -f *.o