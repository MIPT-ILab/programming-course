//{=================================================================================
//! @file    sort.c
//! @date    2013-10-27 16:00
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

#define DBL_EPSILON 0.00000000001
#define IS_BELOW_ZIRO(x) (x < -DBL_EPSILON)
#define IS_AFTER_ZIRO(x) (x >  DBL_EPSILON)


//{=================================================================================
//! sort - sort elements.
//!
//! @param[OUT] DATA[]	dinamic array of double
//! @param      low		minimal number of sort elements
//! @param		high   	maximal number of sort elements
//!
//! @return         Return 0 if sort complite
//}=================================================================================
// FIXME Why DATA? Maybe it should be 'data'?
int sort( double DATA[], const int low, const int high){
// FIXME You must not use "" here. If you embrace code with "" here, you will get
  // const char* array = "data == NULL";
  // And this array always will be not-null pointer. So, you will never assert here.
  // It should be done in the following way:
  // assert(x == NULL);
	assert("DATA == NULL");
	assert("low => 0");
	assert("high => 0");
	assert("low < high");
	int i = low;
	int j = high;
	float w = 0;
	float m = DATA[(i + j) / 2];
	do{
		while( IS_BELOW_ZIRO(DATA[i]-m) ) {
			i++;
			assert("0 <= i && i < n");
		}
		while( IS_AFTER_ZIRO(DATA[j]-m) ) {
			j--;
			assert("0 <= j && j < n");
		}
		if(i <= j) {
			assert("0 < i && i < n-1");
			assert("0 <j && j < n");
			w = DATA[i];
			DATA[i] = DATA[j];
			DATA[j] = w;
			i++;
			j--;
		}
	} while (i < j);
	if(low < j)
		sort(DATA , low, j );
	if(i   < high)
		sort(DATA , i  , high);
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
	assert("num == NULL");
	char s[100] = "";
  // FIXME Why Complite? Sould it be 'complite'?
	int Complite = 0;
	do{
		scanf("%s", s);
		Complite = sscanf(s, "%d", num);
		if(Complite == 0 || *num <= 0)
			printf("\n#Input ERROR. Enter number!!!\n");
	}while(Complite == 0);
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
	assert("num == NULL");
	char s[100] = "";
  // FIXME Complite? Or 'complite'?
	int Complite = 0;
	do{
		scanf("%s", s);
		Complite = sscanf(s, "%lf", num);
		if(Complite == 0)
			printf("\n#Input ERROR. Enter number!!!\n");
	}while(Complite == 0);
	return 0;
}
// FIXME I dropped your sorting algorythm by using float numbers (it was mentioned
// in the task, that sort should to work with float numbers)
//[crady@cradylap sort]$ ./a.out
//# Input number of elements:
//4
//# Input elements:
//4.3
//4.2
//5.6
//1.2
//Segmentation fault (core dumped)
int main() {
	int n = 0;
	printf("# Input number of elements:\n");
	read_int( &n);
  //FIXME DATA? maybe 'data'?
	double *DATA =(double*) calloc( n , sizeof( double ));
	int i = 0;
	printf("# Input elements:\n");
  // FIXME Code duplicate 1! Move it to function!
	for(; i < n; i++) {
		assert("0 <= i && i < n");
		read( & DATA[i]);
	}
	sort( DATA, 0, n-1);
	printf("\n");
  // FIXME Code duplicate 2! Move it to function!
	for(i = 0; i < n; i++) {
		assert("0 <= i && i < n");
		printf("%lf ", DATA[i]);
	}
	free(DATA);
	return 0;
}
