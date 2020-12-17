all: goal
        ./prog

goal: main.o
        g++ main.o -o prog

main.o: main.cpp

clean:
        rm -f *.o

