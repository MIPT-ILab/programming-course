//{=================================================================================
//! @file    01-mergesort.c
//! @date    2013-10-10 13:20
//! @version 1.1
//! @author  Pronin Alexander <texhobeer95@gmail.com>
//!
//! Sort array of integer elements, using merge sort
//!
//! ChangeLog:
//! v. 1.0 (2013-10-03 18:13):  start working with project
//! v. 1.1 (2013-10-05 00:54):  added assert check for all addresses and
//!                             arrays, changed some function's arguments types
//! v. 1.2 (2013-10-10 13:20):  algorithm improved
//! v. 1.3 (2013-10-10 13:41):  added console arguments "-r" and "--reverse":
//!                             sort from up to down
//}=================================================================================

#include <stdio.h>
#include <assert.h>

const int MAX_SIZE = 10000;

void mergesort (int* data, const int size);
void swap (int* a, int* b);
void merge (int* data, int size);

int main(int argc, char* argv[])
{
    int size, i, data[MAX_SIZE];
    char s1[3] = {'-', 'r', '\0'}, s2[10] = {'-', '-', 'r', 'e', 'v', 'e', 'r', 's', 'e', '\0'};
    if (argc > 2) {
        printf ("To many arguments. Program stopped.");
        return 0;
    }
    else {
        if (argc == 2) {
            if (strcmp(argv[1], s1) && strcmp(argv[1], s2)) {
                printf ("Wrong argument. Program stopped.");
                return 0;
            }
        }
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
        for (i = 0; i < size; i++) {
            assert (0 <= i && i < size);
            scanf ("%d", &data[i]);
        }
        mergesort (data, size);
        if (argc == 1) {
            for (i = 0; i < size; i++) {
                assert (0 <= i && i < size);
                printf ("%d ", data[i]);
            }
        }
        else {
            for (i = size - 1; i >= 0; i--) {
                printf ("%d ", data[i]);
            }
        }
        printf ("\n");
        return 0;
        }
    }
}

//{=================================================================================
//! mergesort - sort array using merge sort
//!
//! @param      data    First element address (main array)
//! @param      size    Size of this array
//}=================================================================================
void mergesort (int* data, const int size)
{
    assert (data != NULL);
    int memory[size], i;
    for (i = 0; i < size; i++) {
        memory[i] = data[i];
    }
    if (size >= 2) {
        mergesort (data, size/2);
        mergesort (&data[size/2], size - size/2);
        merge(data, size);
    }
}

//{=================================================================================
//! swap - swap values of a ang b
//!
//! @param      a       Address of first element
//! @param      b       Address of second element
//}=================================================================================
void swap (int* a, int* b)
{
    assert (a != NULL);
    assert (b != NULL);
    int c = *a;
    *a = *b;
    *b = c;
}

//{=================================================================================
//! merge - connect first part of array to second part
//!
//! @param      data    First element address (main array)
//! @param      size    Size of this array
//}=================================================================================
void merge (int* data, const int size)
{
    assert (data != NULL);
    int memory[size];
    int left = 0, right = size/2, i;
    for (i = 0; i < size; i++) {
        memory[i] = data[i];
    }
    i = 0;
    while ((left != size/2) && (right != size)) {
        assert (0 <= left && left < size/2);
        assert (size/2 <= right && right < size);
        assert (0 <= i && i < size);
        if (data[left] > data[right]) {
            memory[i] = data[right];
            right++;
            i++;
        }
        else if (data[left] <= data[right]) {
            memory[i] = data[left];
            left++;
            i++;
        }
    }
    if (left == size/2) {
        while (right != size) {
            assert (size/2 <= right && right < size);
            assert (0 <= i && i < size);
            memory[i] = data[right];
            right++;
            i++;
        }
    }
    else {
        while (left != size/2) {
            assert (0 <= left && left < size/2);
            assert (0 <= i && i < size);
            memory[i] = data[left];
            left++;
            i++;
        }
    }
    for (i=0; i<size; i++) {
        assert (0 <= i && i < size);
        data[i] = memory[i];
    }
}
