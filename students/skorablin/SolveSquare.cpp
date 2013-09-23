diff --git a/students/s_korablin/SolveSquare.cpp b/students/s_korablin/SolveSquare.cpp
new file mode 100644
index 0000000..102bd99
--- /dev/null
+++ b/students/s_korablin/SolveSquare.cpp
@@ -0,0 +1,188 @@
+//{=================================================================================
+//! @file    SolveSquare.cpp
+//! @date    2013-09-23 18:27
+//! @author  Sergey Korablin <ogneej@gmail.com>
+//!
+//! Solving Quadratic Equations
+//!
+//! @par     Statement
+//!          Solving quadratic equations
+//}=================================================================================
+
+#include <stdio.h>
+#include <cmath>
+#include <assert.h>
+
+using namespace std;
+
+//! Approximation to zero
+const double EPS = 0.00000001;
+
+//! SolveSquare returned value in case of infinite number of solutions.
+const int SS_INFINITE_ROOTS = -1;
+
+
+//{=================================================================================
+//! IsZero - check double value equality to zero.
+//!
+//! @param      x    Input value
+//!
+//! @return          true, if offset between x and zero is less then EPS.
+//}=================================================================================
+bool IsZero ( const double x );
+
+//{=================================================================================
+//! SquareSol - solve a square or linear equation specified by its coefficients.
+//!
+//! @param      a    Equation a-coefficient
+//! @param      b    Equation b-coefficient
+//! @param      c    Equation c-coefficient
+//! @param[out] x1   Min. root of equation, if exist (if not, value will be unchanged)
+//! @param[out] x2   Max. root of equation, if exist (if not, value will be unchanged)
+//!
+//! @return          Number of roots or zero if none, -1 if infinite number of roots
+//!
+//! @note            Calculation precision is considered to be DBL_EPSILON.
+//}=================================================================================
+int SquareSol ( const double a,
+                const double b,
+                const double c,
+                double *x1,
+                double *x2 );
+
+//{=================================================================================
+//! PrintSols - print the roots of a square or linear equation.
+//!
+//! @param      Num  Number of roots
+//! @param      x1   Min. root of equation, if exist (if not, value will not be used)
+//! @param      x2   Min. root of equation, if exist (if not, value will not be used)
+//}=================================================================================
+void PrintSols ( const int Num,
+                 const double x1,
+                 const double x2 );
+
+int main () {
+    double a = 0,
+           b = 0,
+           c = 0,
+           x1 = 0,
+           x2 = 0;
+    int NumSol = 0;
+    bool CorrectInput = false;
+    printf ( "# Solve a square or linear equation specified by its coefficients\n"
+             "# Author: Korablin S.\n" );
+    while (!CorrectInput) {
+        printf ( "# Please, enter the coefficients of equation (A, B, C)\n" );
+        CorrectInput = scanf ( "%lf %lf %lf", &a, &b, &c ) == 3;
+    }
+    NumSol = SquareSol ( a, b, c, &x1, &x2 );
+    PrintSols ( NumSol, x1, x2 );
+    return 0; // GR: программа должна возвращать  ноль, только если она завершилась успехом
+              // GR: Если NumSol < 0 , то это вряд ли успех, надо вернуть что-то другое.
+              // ANS: Считаю, что отсутствие решений - тоже успех для функции main
+}
+
+bool IsZero ( const double x ) {
+    return ( abs ( x ) <= EPS );
+}
+
+int SquareSol ( const double a,
+                const double b,
+                const double c, 
+                double *x1,
+                double *x2 ) {
+    if ( IsZero ( a ) ) {
+        if ( IsZero ( b ) ) {
+            if ( IsZero ( c ) ) {
+                return SS_INFINITE_ROOTS;
+            }
+            else {
+                return 0;
+            }
+        }
+        else {
+            if ( IsZero ( c ) ) {
+                *x1 = 0.0;
+                return 1;
+            }
+            else {
+                *x1 = -c / b;
+                return 1;
+            }
+        }
+    }
+    else {
+        if ( IsZero ( c ) ) {
+            if ( IsZero ( b ) ) {
+                *x1 = 0.0;
+                return 1;
+            }
+            else {
+                if ( 0.0 < ( -b / a ) ) {
+                    *x1 = 0.0;
+                    *x2 = -b / a;
+                    return 2;
+                }
+                else {
+                    *x1 = -b / a;
+                    *x2 = 0.0;
+                    return 2;
+                }
+            }
+        }
+        else {
+            double D = b * b - 4 * a * c ;
+            if ( IsZero ( D ) ) {
+                *x1 = - b / ( 2 * a );
+                return 1;
+            }
+            else {
+                if ( D < 0.0 ) {
+                    return 0;
+                }
+                else {
+                    if ( a > 0.0 ) {
+                        *x1 = ( -b - sqrt ( D ) ) / ( 2 * a );
+                        *x2 = ( -b + sqrt ( D ) ) / ( 2 * a );
+                        return 2;
+                    }
+                    else {
+                        *x1 = ( -b + sqrt ( D ) ) / ( 2 * a );
+                        *x2 = ( -b - sqrt ( D ) ) / ( 2 * a );
+                        return 2;
+                    }
+                }
+            }
+        }
+    }
+} 
+
+void PrintSols ( const int Num,
+                 const double x1,
+                 const double x2 ) {
+    switch ( Num ) {
+    case 0:
+        printf ( "# There are no real roots (number of roots:)\n"
+                 "%d\n", Num );
+        break;
+    case 1:
+        printf ( "# There is one real root (number of roots:)\n"
+                 "%d\n", Num );
+        printf ( "# Root:\n"
+                 "%lf\n", x1 );
+        break;
+    case 2:
+        printf ( "# There are two real roots (number of roots:)\n"
+                 "%d\n", Num );
+        printf ( "# Roots:\n"
+                 "%lf\n"
+                 "%lf\n", x1, x2 );
+        break;
+    case SS_INFINITE_ROOTS:
+        printf ( "# There is infinite number of roots\n" );
+        break;
+    default:
+        assert ( Num < 0 || Num > 2 );
+        break;
+    }
+}
