//{=================================================================================
//! @file    sort.c
//! @date    2013-11-3 13:00
//! @author  Panov Vladimir <volodka.1995@gmail.com>
//!
//! Сортировка динамического массива елементов double
//!
//! @par     Условие задачи
//!          Вводится число элементов массива, а потом сами элементы.
//!			 Программа выводит отсортированный массив.
//}=================================================================================

#include <stdio.h>
#include <stdlib.h>

#define assert(cond) \
if (!(cond)) {\
    printf("All gone bad: %s, file: %s, line: %d\n", #cond, __FILE__, __LINE__);\
    abort();\
    }

#define DBL_EPSILON 1e-8
#define IS_BELOW_ZIRO(x) (x <  DBL_EPSILON)
#define IS_ZERO(a) (-DBL_EPSILON < a && a < DBL_EPSILON)
#define IS_AFTER_ZIRO(x) (x > -DBL_EPSILON)



//{=================================================================================
//! sort - sort elements.
//!
//! @param[OUT] array[]	dinamic array of double
//! @param      low		minimal number of sort elements
//! @param		high   	maximal number of sort elements
//!
//! @return         Return 0 if sort complite
//}=================================================================================
int sort( double array[], const int low, const int high){
	assert(array != NULL);
	assert(low >= 0);
	assert(high >= 0);
	assert(low <= high);
	int i = low;
	int j = high;
	float w = 0;
	float m = array[(i + j) / 2];
	do{
		while( array[i] < m && i < high) {
			assert(low <= i && i < high);
			i++;
		}
		while( array[j] > m && j > low) {
			assert(low < j && j <= high);
			j--;
		}
		if(i <= j) {
			assert(low <= i && i <= high);
			assert(low <=j && j <= high);
			w = array[i];
			array[i] = array[j];
			array[j] = w;
			i++;
			j--;
		}
	} while (i < j);
	if(low < j)
		sort(array , low, j );
	if(i   < high)
		sort(array , i  , high);
	return 0;
}

//{=================================================================================
//! read - Read number from string.
//!
//! @param[out]    *num	Number to read
//!
//! @note           Read strings while it isn't double.
//}=================================================================================
int read(double *num){
	assert(num != NULL);
	char s[100] = "";
	int Complite = 0;
	do{
		scanf("%s", s);
		Complite = sscanf(s, "%lf", num);
		if(Complite == 0)
			printf("\n#Input ERROR. Enter correct number!!!\n");
	}while(Complite == 0);
	return 0;
}

//{=================================================================================
//! read_int - Read number from string.
//!
//! @param[out]    *num	Number to read
//!
//! @note           Read strings while it isn't int.
//}=================================================================================
int read_int(int *num){
	assert(num != NULL);
	*num = 0;
	double dnum = 0;
	while(*num < 1) {
		read(&dnum);
		if(IS_ZERO(dnum - (int)dnum))
			*num = (int) dnum;
		else
			printf("\n# Input ERROR. Input correct number!!!\n");
	}
	return 0;
}

//{=================================================================================
//! inputData - Read elements of array.
//!
//! @param[out]    *array	Array to read
//! @param			n		Number of elements
//!
//! @note           Read elements or array.
//}=================================================================================
int inputData(double *array, const int n) {
	assert(array != 0);
	printf("#Input elements:\n");
	int i;
	for(i = 0; i < n; i++){
		read(array+i);
	}
	return 0;
}

//{=================================================================================
//! outputDATA - Print elements of array.
//!
//! @param	   *array	Array to print
//! @param	   	n		Number of elements
//!
//! @note           Print elements of array.
//}=================================================================================
int outputData(const double *array, const int n) {
	assert(array != NULL);
	int i;
	for(i = 0; i < n; i++) {
		assert(0 <= i && i < n);
		printf("%lf ", *(array+i));
	}
	return 0;
}

int main() {
	int n = 0;
	printf("# Input number of elements:\n");
	read_int( &n);
	double *DATA = (double *) calloc( n , sizeof( double ));
	inputData(DATA, n);
	sort( DATA, 0, n-1);
	printf("\n");
	outputData(DATA, n);
	free(DATA);
	return 0;
}
