/** *********************************************************
 
 A program for sorting arrays.
 
 @file Heap_Sort.c
 @date October 7, 2013
 @author Kirill Korolev <kirill.korolef@gmail.com>
 @version 1.0 (October 7, 2013)
 
 @note Ver. 1.01 (October 8, 2013)
    - deleted a documentation of the main function
    - added an output with 6 numbers after a point
    - added a discription for tha Heap_S function
    - mistakes in the documentation was rewriten
    - added a function Heap which uses Heap_S for sorting
    - added 'd' and 'i' as possible values for Type
    - a name od Move function changed to Swap
    - added a messege to the ASSERT define
 
 @note Ver. 1.02 (October 9, 2013)
    - some documentation mistakes fixed
    - added ASSERT for a output
    - added a comparison with EPS accurancy
 
 @note Ver. 1.03 (October 9, 2013)
    - Swap function fixed
    - More grammatical mistakes rewrited
    - Added an introduction
    - Adviced to Ivanychev Sergey to stay away from my
      programs
 
 ************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define EPS  0.000001
#define ASSERT( cond, messege )           \
    if ( !( cond ) )                      \
    {                                     \
        printf ("Fatal error: %s, "       \
        "file: %s, line: %d \n",          \
        #messege, __FILE__, __LINE__);    \
        abort();                          \
    }

int const Ar_Size = 100000; /**< The maximal size of arrays */

/** **********************************************************************************
 
 Heap_S - a recursive function which use for creating a heap from the array.
 
 @param      Parent  The number of the upper element in the ternary.
 @param[out] Array   The the array of numbers which need to be sorted.
 @param      Num     The number of the elements in the array.
 
 @return 0
 
 @note - The function work with the array like with a graph where each element 
         (starting with the first one) is connected only with two other elements
         (offsprings) (if there are enough elements in the array) which always have 
         bigger indexes. This graph called a heap if each offspring is
         smaller (bigger) than its parent or equal to it. The function takes 
         3 elements from the array (a ternary): a parent and its offsprings (if 
         there are any offsprings). It moves to the place of the parent the biggers
         (smallest) element in the ternary and check recursively down elements after 
         swapping. When this was made for each ternary, this array becomes
         a heap, and on the top of the heap there is the biggest (smallest) element.
 
 @note - A comparison is made with accuracy in 6 numbers after a point (the EPS
         const).
 
 *************************************************************************************/

int Heap_S(int Parent, double * Array, int Num);

/** ***********************************************************************************

 Swap - a function for changing places of two elements.
 
 @param      El_1   The index of the first element of the array.
 @param      El_2   The index of the second element of the array.
 @param[out] Array  The the array of numbers which need to be sorted.
 @param      Num    the number of the elements in the array.
 
 @return 0

**************************************************************************************/

int Swap(int El_1, int El_2, double * Array);

/** ***********************************************************************************
 
 Heap - a function which uses Heap_S for creating a heap in the array and sorts it.
 
 @param[out]  Array The array of numbers which need to be sorted.
 @param       Num   The number of the elements in the array.
 
 @note - The function looks though all the ternaries in the array and uses Heap_S 
         to them. When this was made for each ternary, this array becomes
         a heap, and on the top of the heap there is the biggest (smallest) element.
         Then the function sorts the array by taking the top element and recreating
         the heap while there are any elements in the array.

**************************************************************************************/

int Heap(double * Array, int Num);

int main()
{
    int i = 0, j = 0;   /**< Indexes */
    int Num_Ar = 0;     /**< The number of e arrays for sorting */
    int Check = 0;      /**< A variable for ASSERT define */
    
    printf("Program for sorting arrays of numbers using the Heap sort algorithm.\n"
           "Author: Kirill Korolev\n"
           "Date of creation: October 7, 2013\n\n");
    
    printf("Please, enter the number of arrays wich you want to sort:\n");
    Check = scanf("%d", &Num_Ar);
    ASSERT(Check == 1, "An inappropriate type for Num_Ar.");
    
    for (j = 0; j < Num_Ar; j++)     /** Sorting each array **/
    {
        double Array[Ar_Size] = {};  /**< The current array for sorting */
        int Num = 0;                 /**< The number of the elements in the array */
        char Type = '0';             /**< A char variable for checking a type of sorting */
        
        printf("The array number %d:\n", j + 1);
        printf("Enter your array:\n");      /** Input the array without a exact number of elements */
        do
        {
            Num++;
            ASSERT(((0 <= Num) && (Num <= Ar_Size)), "Num is inappropriate for the size of Array.");
            Check = 0;
            Check = scanf("%lf", &Array[Num]);
            ASSERT(Check == 1, "An inappropriate type for Array.");
        } while (getc(stdin) != '\n');
        
        printf("Enter the type of sorting: with decresing/increasing (D/I):\n");
        Check = 0;
        Check = scanf("%c", &Type);    /** Checking the type */
        ASSERT((Check == 1), "An inappropriate type for Type.");
        ASSERT(((Type == 'D')||(Type == 'd')||(Type == 'I')||(Type == 'i')), "An inappropriate value for Type.");
    
        Heap(Array, Num);
    
        printf("A sorted array:\n");   /** Output the sorted array */
        if ((Type == 'I') || (Type == 'i'))
        {
            for (i = 1; i <= Num; i++)
            {
                ASSERT(((1 <= i) && (i <= Num)), "i is inappropriate for an Array index.");
                if (i == Num) printf("%.6lg", Array[i]);
                else printf("%.6lg ", Array[i]);
            }
        }
        if ((Type == 'D') || (Type == 'd'))
        {
            for (i = Num; i >= 1; i--)
            {
                ASSERT(((1 <= i) && (i <= Num)), "i is inappropriate for an Array index.");
                if (i == 0) printf("%.6lg", Array[i]);
                else printf("%.6lg ", Array[i]);
            }
        }
        printf("\n\n");
    }
    
    return 0;
}

int Heap_S(int Parent, double * Array, int Num)
{
    ASSERT((Array != NULL), "Array[0] has a NULL address.");
    
    int Left = 2*Parent;                /**< The number of the left offspring in the ternary */
    int Right = Left + 1;               /**< The number of the right offspring in the ternary */
    
    if (Left > Num) return 0;           /** Checking the existing of two offsprings */
    if (Right > Num) Right = Left;
    
    int Unkn = Parent;                  /**< The number of the biggest el. in this ternary */
    
    ASSERT(( (1 <= Left) && (Left <= Num) ), "Left is inappropriate for an Array index.");
    ASSERT(( (1 <= Right) && (Right <= Num) ), "Right is inappropriate for an Array index.");
    ASSERT(( (1 <= Unkn) && (Unkn <= Num) ), "Unkn is inappropriate for an Array index.");
    ASSERT(( (1 <= Parent) && (Parent <= Num) ), "Left is inappropriate for an Array index.");
    
    if (Array[Left] - Array[Unkn] > EPS) Unkn = Left;
    if (Array[Right] - Array[Unkn] > EPS) Unkn = Right;
    if (Unkn == Parent) return 0;       /** Escaping, when no changes in the ternary are needed */
    
    Swap(Unkn, Parent, Array);     /** Putting in the upper place the biggets element */
    Heap_S(Unkn, Array, Num);           /** Marshaling the heap in down elements */
    
    return 0;
}

int Swap(int El_1, int El_2, double * Array)
{
    ASSERT(Array != NULL, "Array[0] has a NULL address.");
    
    double Temp = Array[El_1];          /**< An intermediate variable for changing places */
    Array[El_1] = Array[El_2];
    Array[El_2] = Temp;
    
    return  0;
}

int Heap(double * Array, int Num)
{
    ASSERT(Array != NULL, "Array[0] has a NULL address.");
    
    int i = 0;                     /**< An index */
    
    for (i = Num/2; i >= 1; i--)   /** Marshaling the heap in the array */
        Heap_S(i, Array, Num);
    
    int Num_Copy = Num;            /**< A copy of Num */
    
    for (i = 1; i < Num_Copy; i++) /** Sorting by taking the upper el. in the heap */
    {
        ASSERT( ( (0 <= Num) && (Num <= Ar_Size) ), "Num is inappropriate for an Array index.");
        ASSERT( (1 <= Num), "1 is inappropriate for an Array index.");
        Swap(1, Num, Array);
        Num--;
        Heap_S(1, Array, Num);
    }
    
    return 0;
}