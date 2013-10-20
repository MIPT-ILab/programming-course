#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int MyStrlen (char str[ ]);
char* MyStrCopy ( char str1[], char str2[] );

//---------------------------------------------------
//---------------------------------------------------
//---------------------------------------------------

int main ()
{
    int i, lenstr;
    char str1[10] = "gadsjj", str2[9] = "ass";

    printf("%s", MyStrCopy(str1,str2));

    return 0;
}

//---------------------------------------------------
//---------------------------------------------------
//---------------------------------------------------

char* MyStrCopy ( char str1[], char str2[] )
{
    int i, lenstr;
    char* p;
    lenstr = MyStrlen(str1)+MyStrlen (str2);
    p = calloc (MyStrlen (str1)+MyStrlen (str2), sizeof(char));

    for (i = 0; i < lenstr; i++)
        {
         if ( i < MyStrlen (str1) )
              p[i] = str1[i];
         else
              p[i] = str2[i - MyStrlen (str1)];
        }
	return p;

}

//---------------------------------------------------
//---------------------------------------------------
//---------------------------------------------------

int MyStrlen (char str[ ])
{
    int i = 0;
    while ( str[i] )
          i++;
	return i;

}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1000

..................................................................
int main ()
{
    int triangle[N][N];
    int n = 0, i = 0, j = 0 , l = 0;
    l = 1;

    scanf ("%i", &n);

    for (i = 0; i <= n; i++)
        {
         for (j = 0; j < i; j++)
             {
              triangle[i][j] = triangle[i-1][j-1]+triangle[i-1][j];
             }
        }
    for (i = 0; i <= n; i++)
        {
         for (j = 0; j < i; j++)
             {
              printf ("%i",triangle[i][j]);
             }
         printf("\n");
        }
  return 0;
 }

.........................................................................
//в квадрат четырех
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

int issqr ( int n);


int main ()
{
    int temp;
    int n, i, j, k;
    scanf("%i", &n);

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            for (k = 0; k < n; k++)
                {
                    temp = n-i*i-j*j-k*k;
                    //printf(" '%i %i %i %d ", i*i, j*j, k*k, (int)temp);
                  if ( issqr (temp) )
                    {
                     //  printf(" =%i= ", isint (temp));
                      printf("%i %i %i %d", i*i, j*j, k*k, (int)temp);
                      return 0;
                    }
                }
//printf("  \n - %i %i %i %d", i*i, j*j, k*k, temp*temp);
    return 0;

}


int issqr ( int n)
{
  int i;
  for (i = 0; i<n; i++)
        if (i*i == n)
            return 1;

  return 0;
}
