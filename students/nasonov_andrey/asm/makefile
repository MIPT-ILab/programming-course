prn : main.o stack.o CPU.o parser.o translator.o
	gcc -o prn main.o stack.o CPU.o parser.o translator.o -lm
main.o : main.c
	gcc -c -std=c99 main.c
stack.o : stack.c
	gcc -c -std=c99 stack.c
CPU.o : CPU.c
	gcc -c -std=c99 CPU.c
parser.o : parser.c
	gcc -c -std=c99 parser.c
translator.o : translator.c
	gcc -c -std=c99 translator.c
clean :
	rm -r *~ *o
