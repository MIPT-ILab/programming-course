#include <stdio.h>

const int MAX_SIZE = 10000;

void sort (int* data, int size);
void swap (int* a, int* b);

int main()
{
	int size, data[MAX_SIZE], i;
	printf ("# Array sort\n");
	printf ("# Enter number of array's elements:\n");
	scanf ("%d", &size);
	printf ("# Enter array's elements:\n");
	for (i = 0; i < size; i++) {
		scanf ("%d", &data[i]);
	}
	sort (data, size);
	printf ("# Sorted array:\n");
	for (i = 0; i < size; i++) {
		printf ("%d ", data[i]);
	}
	return 0;
}

void sort (int* data, int size)
{
	int j, i;
	for (j = 0; j < size - 1; j++) {
		for (i = 0; i < size - j - 1; i++) {
			if (data[i] > data[i + 1]) {
				swap (&data[i], &data[i + 1]);
			}
		}
	}
}

void swap (int* a, int* b)
{
    int c = *a;
    *a = *b;
    *b = c;
}
