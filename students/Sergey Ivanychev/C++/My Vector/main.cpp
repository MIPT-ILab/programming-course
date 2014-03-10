/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	
	@file		main.cpp
	@author		Sergey Ivanychev, sergeyivanychev@gmail.com, MIPT DCAM, 376 group

	@mainpage
	@par		There's a prototype vector realization. 
				-  The size of vector is automatically changing during append
				-  Support of		vector + vector (even if sizes are different), 
									double * vector, 
									vector * double, 
									vector[index], 
									vector = vector operators
				-  There are MODULE methon inside
	
	@par		Main function is a complex of vector testing.

	@par		This realization wasn't copied from anywhere and inspired by C++ standard vector class,
				which was used by me few years ago. Theory by Ilya Ruydolphovych and Stephen Pratha.

	@version	V 1.0

	@todo		Write detailed documentation

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
*/

#define DEBUG_MODE
#define _CRT_SECURE_NO_WARNINGS

#ifdef DEBUG_MODE
#include "debug.h"
#endif

#include "vector_header.h"

FILE* strerr = NULL;
FILE* strlog = NULL;

const int RANDOM_RANGE = 20;


int main()
{
	strerr = stdout;
	strlog = stdout;
	
	FILE* strout = fopen("output.txt", "w");
	assert(strout != NULL);

	Vector a;
	
	for (int i = 1; i < 20; ++i) a.append(i);

	a.print(strout);
	printf("\n%lg - module\n", a.module());

	a.reset();
	printf("Resetting...\n");
	a.print(strout);

	fputc('\n', strout);

	fprintf(strout, "Checking memory autoallocating...\n");
	for (int i = 0; i < 10; ++i)
	{
		a.append(rand() % RANDOM_RANGE);
		putc('\n', strout);
		printf("Size = %d, Memory = %d\n", a.get_size(), a.get_memory_size());
	}
	fprintf(strout, "\nDone\nResetting...\n\n");
	fprintf(strout, "Creating another vector. Testing copying \n");

	Vector b = a;
	a.dump(strout);
	putc('\n', strout);
	b.dump(strout);


	fprintf(strout, "Test done. Resetting and generating random vectors\n");
	a.reset();
	b.reset();
	
	for (int i = 0; i < 3; ++i) 
	{ 
		a.append(rand() % RANDOM_RANGE);
		b.append(rand() % RANDOM_RANGE);
	}
	b.append(rand() % RANDOM_RANGE);

	fprintf(strout, "Dumping first...\n\n");
	a.dump(strout);
	fprintf(strout, "Dumping second...\n\n");
	b.dump(strout);

	Vector c = a + b;
	fprintf(strout, "\nDumping sum...\n\n");
	c.dump(strout);
	
	Vector d = a - b;
	fprintf(strout, "\nDumping difference...\n\n");
	d.dump(strout);
	
	Vector e = a * 10;
	fprintf(strout, "\nDumping first * 10...\n\n");
	e.dump(strout);
	
	Vector f = (1/10.0) * e;
	fprintf(strout, "\nDumping (1/10) * last result...\n\n");
	f.dump(strout);

	double temp_data[] = {1, 2, 3, 4, 5};
	Vector g = {5, temp_data};
	fprintf(strout, "\nTesting creating vector from {1, 2, 3, 4, 5} array\n\n");
	g.dump(strout);

	fprintf(strout, "\nPrinting data using [] operands...\n\n");
	for (int i = 0; i < g.get_size(); ++i) fprintf(strout, "%lg\n", g[i]);

	system("PAUSE");
	return 0;
}