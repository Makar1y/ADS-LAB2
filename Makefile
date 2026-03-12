main.exe : main.c queens.o queens.h utils.o utils.h
	gcc -std=c99 -o queens.exe main.c queens.o utils.o

queens.o : queens.c utils.c utils.h
	gcc -c -std=c99 queens.c utils.c

utils.o : utils.c utils.h
	gcc -c -std=c99 utils.c