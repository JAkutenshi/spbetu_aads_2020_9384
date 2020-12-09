all: goal
	./start

goal: main.o
	g++ main.o -o start

main.o: main.cpp BinaryTree.h
	g++ -c main.cpp

clean:
	rm -f *.o