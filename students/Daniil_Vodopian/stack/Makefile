main: main.o stackLib.o
	gcc main.o stackLib.o -I"./" -o main

main.o: main.c
	gcc -c -std=c99 main.c -I"./" -o main.o

stackLib.o: stackLib.c
	gcc -c -std=c99 stackLib.c -I"./" -o stackLib.o
