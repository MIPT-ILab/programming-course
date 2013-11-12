main: main.o ../stack/stackLib.o
	gcc main.o ../stack/stackLib.o -o main

main.o: main.c
	gcc -c -std=c99 main.c -I"./" -I"../stack" -o main.o

../stack/stackLib.o: ../stack/stackLib.c
	cd ../stack/
	make stackLib.o
	cd ../assembler/
