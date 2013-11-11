
//{====================================================================================
//! @file sort_mass.c
//! @date    2013-10-26 23:00
//! @author Ryabykh Alexey <immanueltrue@gmail.com>
//! @version 1.0.1
//! Program by the bubble sort the array in ascending or descending order, or any user-created array
//!
//}====================================================================================

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define SWAP(A,B){ double k=A;A=B;B=k; }


//{=================================================================================
//! write - Prints an array.
//! @param  N   number of array elements
//! @param  data[] array
//}=================================================================================

void write (int N, double data[])
    {

    assert ( (" Write received a non-null pointer ", data != NULL));

    int i=0;

    for (i = 0; i < N; i++)
        {
        assert ( 0 <= i && i <= N);
        printf ("%lg ", data[i]);
        }
    printf ("\n");
    }

//{=================================================================================
//! initRandomArray - initializes an array of random numbers
//! @param      data[]   array
//}=================================================================================

void initRandomArray (double data[])
    {
    assert ( (" initRandomArray received a non-null pointer ", data != NULL));
    srand (time (NULL));

    int i = 0;
    double min = 0, max = 0;
    printf ("Enter the range of values\n"
            "Minimum value : ");
    scanf ("%lg", &min);
    printf ("Maximum value : ");
    scanf ("%lg", &max);

    while (min>max)
        {
        printf("\nYou made a mistake!\n\n");
        printf ("Enter the range of values\n"
                "Minimum value : ");
        scanf ("%lg", &min);
        printf ("Maximum value : ");
        scanf ("%lg", &max);
        }
    max-=min;
    max/=3;
    for (i = 0; i < 10000; i++)
        {
        assert ( 0 <= i && i <= 10000);
        data[i] =(rand() / 10000)* max + min;
        }
    }
//{=================================================================================
//! Sort_bubble - Sorts an array of a certain algorithm.
//! @param      N   number of array elements
//! @param      data array
//}=================================================================================

void sort_bubble (int N, double data[], int p)
    {
    int j = 0, f = 0;
    double k = 0;

    assert ( (" Sort_bubble received a non-null pointer ", data != NULL));

    printf( "If you want to sort the array in ascending enter 1, if the descending enter 2\n"
            "Enter value :");
    scanf("%lg",&k);

    if (k==1)
        {
        if (p!=1 && p!=3)
            {
            for (j = 0; j < N - 1; j++)
                for (f = 0; f < N - 1 - j; f++)
                    {
                    assert ( 0 <= f && f <= N-j);
                    if (data[f] > data[f + 1])
                        SWAP (data[f], data[f + 1]);
                    }
            }
        }
        else if (k==2)
        {
        if (p!=2 && p!=3)
            {
            for (j = 0; j < N - 1; j++)
                for (f = 0; f < N - 1 - j; f++)
                    {
                    assert ( 0 <= f && f <= N-j);
                    if (data[f] < data[f + 1])
                        SWAP (data[f], data[f + 1]);
                    }
            }
        }
        else
        {
        printf("\nYou made a mistake!\n\n");
        sort_bubble(N,data,p);
        }
    }

//{=================================================================================
//! readArrFromKeaboard -       Reading array from the keyboard.
//! @param      data array
//! @return     number of array elements
//}=================================================================================
int readArrFromKeaboard (double data[])
    {
    int N = 0, i = 0, z=3;

    assert ( (" readArrFromKeaboard received a non-null pointer ", data != NULL));

    printf ("Enter numbers of elements of the array : ");
    scanf ("%d", &N);
    printf ("Enter values of elements of the array : \n");

    if (N>1)
        {
        scanf("%lg",&data[0]);
        scanf("%lg",&data[1]);
        double x1=data[0],x2=data[1];
        if (x1>x2) z=2;
            else if (x2>x1) z=1;
        for (i = 2; i < N; i++)
            {
            x1=data[i-1];
            scanf ("%lg", &data[i]);
            x2=data[i];
            if (z==3 && x2<x1) z=2;
            if (z==3 && x1<x2) z=1;
            if (z==1 && x1>x2) z=0;
            if (z==2 && x2>x1) z=0;
            }
        }
        else scanf("%lg",&data[0]);
    sort_bubble(N,data,z);
    return N;
    }

//{=================================================================================
//! functchoice - function provides the user a choice
//}=================================================================================
void functchoice()
    {
    double m=0;
    printf (
        "If you want to create and sort by increase the random array from 10000 elements,enter 0. \n"
        "If you want to choose the size of the array and to enter value of its elements, enter 1. \n"
        "Enter value : ");
    scanf ("%lg", &m);

    if (m == 0)
        {
        double data[10001];
        initRandomArray (data);
        sort_bubble (10000, data, 0);
        write (10000, data);
        }
    else if (m == 1)
        {
        double data[10001];
        int Kol = readArrFromKeaboard (data);
        write (Kol, data);
        }
    else
        {
        printf ("\nValue isn't initialized! \n\n");
        functchoice();
        }
    }

int main()
    {
    printf ("PROGRAM: Sorting an array\n");
    printf ("AUTHOR: Ryabykh Alexey, v 1.0 \n");
    functchoice();
    return 0;
    }
