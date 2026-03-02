main.exe : main.c 5queens.o 5queens.h utils.o utils.h
	gcc -std=c99 -o main.exe main.c 5queens.o utils.o

5queens.o : 5queens.c utils.o
	gcc -c -std=c99 5queens.c utils.o

utils.o : utils.c
	gcc -c -std=c99 utils.c