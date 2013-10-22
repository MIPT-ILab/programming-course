//{=============================================================================
//!  @file main.c
//!  @date 20.10.13
//!  @author Igor Yadrov Igor.Yadrov@frtk.ru
//!
//!  this program sorts array by ascending
//!  sorry, i bad know English
//}=============================================================================
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void sort_shell (float* array, int SIZE);

int main(int argc, char* argv[]) {
    int SIZE=0;
    SIZE=argc-1;
    float array[SIZE];
    int i;
    short int boolean=1;

    for (i=0; i<SIZE; i++) {
        array[i]=atof(argv[i+1]);
    }

    for (i=0; i<SIZE; i++) {
        if ((array[i]==0)&&(strcmp(argv[i+1], "0")!=0))
            boolean=0;
    }
           assert (boolean==1);
    sort_shell (array, SIZE);
    for (i=0; i<SIZE; i++) {
        printf("%f ", array[i]);
    }
    printf ("\n");
    return 0;
}
//{==============================================================================
//!
//!  @param array array of float
//!  @peram SIZE  of the array
//!
//!  this function use sort method by Shell
//!
//}==============================================================================
void sort_shell (float* array,int SIZE) {
    int step=0;
    int border=0;
    int i=0,j=0,k=0;
    float temp;

    step=SIZE;
    while (step>0) {
        step= step/2;
        border= SIZE-step;
        for (i=0; i<border; i++) {
            assert(i<SIZE);
            j=i+step;
            assert (j<SIZE);
            if (array[j]<array[i]) {
                temp=array[j];
                array[j]=array[i];
                array[i]=temp;

                k=i;
                while (k>0) {
                    if ((k-step)>=0)
                        if (array[k]<array[k-step]) {
                            temp=array[k];
                            array[k]=array[k-step];
                            array[k-step]=temp;
                        }
                    k=k-step;
                }
            }
        }
    }
}
