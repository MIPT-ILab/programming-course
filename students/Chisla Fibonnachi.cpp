#include <stdio.h>

int Recurs(int k)
{                                                                  // Realizacija funkcii
 if (k == 1 || k == 2) return 1;                                   // poiska n-ogo chisla Fibonachchi
 return (Recurs(k-1) + Recurs(k-2));                               // rekursivnym metodom
}

int Iterat(int k)  
{                                                                  //
 k -= 2;                                                           //
 int a = 1, b = 1, c;                                              // Realizacija funkcii
 for (int i=1; i<=k; i++)                                          // poiska n-ogo chisla Fibonachchi
 {                                                                 // iterativnym metodom
  c=a; a+=b; b=c;                                                  //
 };                                                                //
 return a;                                                         //
}

int main()
{
  int n;                                                                   //
  printf("Vvedite nomer iskomovo chisla Fibonachchi\n");                   //
  scanf ("%d", &n);                                                        //
  while (n < 1 || n > 40)                                                  // Vvod chisla n
   {                                                                       //
    printf("Vvedite nomer iskomovo chisla Fibonachchi, n>=1 and n<=40\n"); //
    scanf ("%d", &n);                                                      //
   };

  printf("Vvedite metod poiska etovo chisla Fibonachchi:\n");      //
  printf("  1.iterativnuy\n  2.rekursivnuy\n");                    // Vybor metoda poiska
  int b=0;                                                         // iterativnyj ili rekursivnyj
  while (b<1 || b>2)                                               //
   {                                                               //
    printf("Vvedite tolko chislo 1 ili 2\n");                      //
    scanf("%d", &b);                                               //
   }

  if (b==1)                                                        //
   {                                                               //
    printf("vybran iterativnyj metod\n");                          //
    printf("F(%d) = %d\n", n, Iterat(n));                          //
   }                                                               // Podschet i vyvod iskomogo chisla
  else                                                             //
   {                                                               //
    printf("vybran rekursivnyj metod\n");                          //
    printf("F(%d) = %d\n", n, Recurs(n));                          //
  }
}