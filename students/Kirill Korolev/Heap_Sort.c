/** *********************************************************
 
 A program for sorting arrays.
 
 @file Heap_Sort.c
 @date October 7, 2013
 @author Kirill Korolev <kirill.korolef@gmail.com>
 @version 1.0 (October 7, 2013)
 
 ************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define ASSERT( cond )                 \
    if ( !( cond ) )                   \
    {                                  \
        printf ("Fatal error: %s, "    \
        "file: %s, line: %d \n",       \
        #cond, __FILE__, __LINE__);    \
        abort();                       \
    }

int const Ar_Size = 100000; /**< The maximal size of arrays */

/** **********************************************************************************
 
 Heap_S - a function for marshaling a heap in the array.
 
 @param      Parent  The number of the upper element in the ternary.
 @param[out] Array  The the array of numbers which need to be sorted.
 @param      Num  The number of the elements in the array.
 
 @return 0
 
 @note - The function work with three elements of the array (a ternary).
         It moves on the upper place the biggers (smallest) element from the ternary.
 
 *************************************************************************************/

int Heap_S(int Parent, double * Array, int Num);

/** ***********************************************************************************

 Move - a function for changing places of two elements.
 
 @param      El_1  The number of the first element of the array.
 @param      El_2  The number of the second element of the array.
 @param[out] Array  The the array of numbers which need to be sorted.
 
 @return 0

**************************************************************************************/

int Move(int El_1, int El_2, double * Array);

/** ***********************************************************************************
 
 main - a function for sorting the array using the Heap_Sort function.
 
 @return 0
 
 @note - This function uses Heap_Sort function and marshals a heap in the array, 
         sorts the array by taking each time an apper element of the heap.
 
**************************************************************************************/

int main()
{
    int i = 0, j = 0;   /**< Indexes */
    int Num_Ar = 0;     /**< The number of e arrays for sorting */
    int Check = 0;      /**< A variable for ASSERT define */
    
    printf("Please, enter the number of arrays wich you want to sort:\n");
    Check = scanf("%d", &Num_Ar);
    ASSERT(Check == 1);
    
    for (j = 0; j < Num_Ar; j++)     /** Sorting each array **/
    {
        double Array[Ar_Size] = {};  /**< The curent array for sorting */
        int Num = 0;                 /**< The number of the elements in the array */
        int Num_Copy = 0;            /**< A copy of Num */
        char Type = '0';             /**< A char variable for checking a tupe of sorting */
        
        printf("The array number %d:\n", j + 1);
        printf("Enter your array:\n");      /** Input the array without a exact number of elements */
        do
        {
            Num++;
            ASSERT((0 <= Num) && (Num <= Ar_Size));
            Check = 0;
            Check = scanf("%lf", &Array[Num]);
            ASSERT(Check == 1);
        } while (getc(stdin) != '\n');
        
        printf("Enter the type of sorting: with decresing/increasing (D/I):\n");
        Check = 0;
        Check = scanf("%c", &Type);    /** Checking the type */
        ASSERT(Check == 1);
    
        for (i = Num/2; i >= 1; i--)   /** Marshaling the heap in the array */
            Heap_S(i, Array, Num);
    
        Num_Copy = Num;
        for (i = 1; i < Num_Copy; i++) /** Sorting by taking the upper el. in the heap */
        {
            Move(1, Num, Array);
            Num--;
            Heap_S(1, Array, Num);
        }
    
        printf("A sorted array:\n");   /** Output the sorted array */
        if (Type == 'I')
        {
            for (i = 1; i <= Num_Copy; i++)
            {
                if (i == Num_Copy) printf("%lg", Array[i]);
                else printf("%lg ", Array[i]);
            }
        }
        if (Type == 'D')
        {
            for (i = Num_Copy; i >= 1; i--)
            {
                if (i == 0) printf("%lg", Array[i]);
                else printf("%lg ", Array[i]);
            }
        }
        printf("\n\n");
    }
    
    return 0;
}

int Heap_S(int Parent, double * Array, int Num)
{
    int Left = 2*Parent;                /**< The number of the left offspring in the ternary */
    int Right = Left + 1;               /**< The number of the right offspring in the ternary */
    
    if (Left > Num) return 0;           /** Checking the existing of two offsprings */
    if (Right > Num) Right = Left;
    
    int Unkn = Parent;                  /**< The number of the biggest el. in this ternary */
    if (Array[Left] > Array[Unkn]) Unkn = Left;
    if (Array[Right] > Array[Unkn]) Unkn = Right;
    if (Unkn == Parent) return 0;       /** Escaping, when no changes in the ternary are needed */
    
    Move(Unkn, Parent, Array);          /** Putting in the upper place the biggets element */
    Heap_S(Unkn, Array, Num);           /** Marshaling the heap in down elements */
    
    return 0;
}

int Move(int El_1, int El_2, double * Array)
{
    double Temp = Array[El_1];          /**< An intermediate variable for changing places */
    Array[El_1] = Array[El_2];
    Array[El_2] = Temp;
    
    return  0;
}