hey : quadratic_equation.o libequations.a
	gcc -o hey quadratic_equation.o -L. -lequations -lm

quadratic_equation.o : quadratic_equation.c
	gcc -c quadratic_equation.c

libequations.a : solve_linear.o solve_quadratic.o
	ar cr libequations.a solve_linear.o solve_quadratic.o

solve_linear.o : solve_linear.c
	gcc -c solve_linear.c

solve_quadratic.o : solve_quadratic.c
	gcc -c solve_quadratic.c

clean:
	rm -f *~ *.o *.a hey
