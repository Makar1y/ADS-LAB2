main.exe : debug.exe main.c queens.o queens.h utils.o utils.h
	gcc -std=c99 -o main.exe main.c queens.o utils.o

debug.exe : main.c queens.o queens.h utils.o utils.h
	gcc -std=c99 -o debug.exe main.c queens.o utils.o -DDEBUG

queens.o : queens.c utils.c utils.h
	gcc -c -std=c99 queens.c utils.c

utils.o : utils.c
	gcc -c -std=c99 utils.c