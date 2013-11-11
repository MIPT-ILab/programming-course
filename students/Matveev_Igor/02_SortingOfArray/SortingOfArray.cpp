//{================================================================================================
//! @file SortingOfArray.cpp
//! @date 2013-11-05
//! @author Igor Matveev <science.creation96@gmail.com>, 312 group, DREC MIPT
//! @version 1.01
//! @note V1.01
//!     - created main which
//!     -- requires an array and it's size
//!     -- induces the function Sorting
//!     -- handles the output
//!     - created the function Sorting

//}================================================================================================
//-------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#define ASSERT(cond)                        \
if (!(cond)) {                              \
      printf("\nAll is bad:\n"              \
             " %s is FALSE!!!11\n"          \
             "File: %s\nLine: %d\n",        \
             #cond, __FILE__, __LINE__);    \
      abort();                              \
      }

#define SORTED   1
#define UNSORTED 0

int Sorting(int Size, float *Data);

/**
main - Requires an array, allocates the necessery memory(and free it after work),
        print the sorting array

      @param Data     - the injected array
      @param DataSize - the size of this array
      @param proof    - verifying parameter
      @param i        - counter

      @return main: Standart return
**/
//-------------------------------------------------------------------------------------------------
int main()
{
      char proof = 0;
      float *Data = NULL;
      int DataSize = 0;

      printf("Hi! Give me an array and I sort it!\n\n"
             "How many numbers are there in your array?\n");
      proof = scanf("%d", &DataSize);
      ASSERT(proof);
      Data = (float*) calloc( DataSize, sizeof(float) );
      ASSERT(Data);
      printf("OK. Give me the numbers over space.\n");
      for (int i = 0; i < DataSize; i++)
      {
            ASSERT( 0 <= i && i < DataSize );
            proof = scanf("%f", &Data[i]);
            ASSERT(proof);
      }
      if (Sorting(DataSize, Data))
      {
            printf("\nAll is OK. Your sorted array:\n");
            for (int i = 0; i < DataSize; i++)
            {
                  printf("%g ", Data[i]);
            }
      }
      else
      {
            printf("Something goes wrong! Check the algorithm!\n");
      }
      free(Data);
      return 0;
}
//-------------------------------------------------------------------------------------------------

/**
Sorting - Sorts the array

      @param Data  - injected array
      @param Size  - size of the array
      @param order - status of the array
      @param stop  - cell of the array after which array is sorted
      @param lsch  - 'last change'
      @param tmp   - temporary parameter

      @return   the status of the array

      @note Algorithm - From the begining of an injected array to it's end function compares
                        two neighbouring values and if they are not sorted,function transpose
                        them. The number of right cell in transposition is put down in 'lsch'
                        (last change). When cycle is passed one time last 'lsch' is put down
                        in 'stop', after which the array is sorted. And so on until all array
                        becames sorted.
**/
int Sorting(int Size, float *Data)
{
      char order = UNSORTED;
      int stop = Size - 1, lsch = 0, i = 0;
      float tmp = 0;
      while ( order == UNSORTED )
      {
            order = SORTED;
            while ( i < stop )
            {
                  ASSERT( 0 <= (i + 1) && (i + 1) < Size );
                  if ( Data[i] > Data[i + 1] )
                  {
                        order = UNSORTED;
                        tmp = Data[i + 1];
                        Data[i + 1] = Data[i];
                        Data[i] = tmp;
                        lsch = ++i;
                  }
                  else
                  {
                        ++i;
                  }
            }
            i = 0;
            stop = lsch;
      }
      return order;
}
