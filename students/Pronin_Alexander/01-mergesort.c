//{=================================================================================
//! @file    01-mergesort.c
//! @date    2013-10-03 18:13
//! @author  Pronin Alexander <texhobeer95@gmail.com>
//!
//! Sorting array of integer elements, using merge sort
//}=================================================================================

#include <stdio.h>

const int MAX_SIZE = 10000;

void mergesort (int* data, int* memory, int size);
void swap (int* a, int* b);
void merge (int* data, int* memory, int size);

int main()
{
    int size, i, data[MAX_SIZE], memory[MAX_SIZE];
    printf ("# Array sort, using merge sort\n");
    printf ("# Author: Pronin Alexander\n");
    printf ("# E-mail: texhobeer95@gmail.com\n");
    printf ("# v. 1.0 date: 2013-10-03 18:13\n\n");
    printf ("# Minimal array size = 1, Maximal array size = %d, elements are integer\n", MAX_SIZE);
    printf ("# Enter number of array's elements:\n");
    scanf ("%d", &size);
    if (size < 1) {
        printf ("Entered array size < 1. Program stopped.\n");
        return 0;
    }
    else if (size > MAX_SIZE) {
        printf ("Entered array size > %d. Program stopped.\n", MAX_SIZE);
        return 0;
    }
    else {
    printf ("# Enter array's elements:\n");
    for (i=0; i<size; i++) {
        scanf ("%d", &data[i]);
        memory[i] = data[i];
    }
    mergesort (data, memory, size);
    printf ("# Sorted array:\n");
    for (i=0; i<size; i++) {
        printf ("%d ", data[i]);
    }
    printf ("\n");
    return 0;
    }
}

//{=================================================================================
//! mergesort - sorting array using merge sort
//!
//! @param      data    First element address (main array)
//! @param      memory  First element address (helping array)
//! @param      size    Size of those arrays
//}=================================================================================
void mergesort (int* data, int* memory, int size)
{
    if (size == 2) {
        if (data[0] > data[1]) {
            swap (&data[0], &data[1]);
            swap (&memory[0], &memory[1]);
        }
    }
    else if (size > 2) {
        mergesort (data, memory, size/2);
        mergesort (&data[size/2], &memory[size/2], size - size/2);
        merge(data, memory, size);
    }
}

//{=================================================================================
//! swap - swaping values of a ang b
//!
//! @param      a       Address of first element
//! @param      b       Address of second element
//}=================================================================================
void swap (int* a, int* b)
{
    int c = *a;
    *a = *b;
    *b = c;
}

//{=================================================================================
//! merge - connecting first part of array to second part
//!
//! @param      data    First element address (main array)
//! @param      memory  First element address (helping array)
//! @param      size    Size of those arrays
//}=================================================================================
void merge (int* data, int* memory, int size)
{
    int L = 0, R = size/2, i=0;
    while ((L != size/2) && (R != size)) {
        if (data[L] > data[R]) {
            memory[i] = data[R];
            R++;
            i++;
        }
        else if (data[L] < data[R]) {
            memory[i] = data[L];
            L++;
            i++;
        }
        else if (data[L] == data[R]) {
            memory[i] = data[L];
            i++;
            memory[i] = data[R];
            L++;
            R++;
            i++;
            }
    }
    if (L == size/2) {
        while (R != size) {
            memory[i] = data[R];
            R++;
            i++;
        }
    }
    else {
        while (L != size/2) {
            memory[i] = data[L];
            L++;
            i++;
        }
    }
    for (i=0; i<size; i++) {
        data[i] = memory[i];
    }
}
