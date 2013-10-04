//{============================================================================
//! @file quadratic_equation.c
//! @author Nasonov Andrey <drnetzah@gmail.com>
//!
//! Solving quadratic equation.
//!
//! @par This program is purposed for solving quadratic equations.
//!      It receives three coefficients of given equation and analyzes it.
//}============================================================================

//-------- Headers ------------------------------------------------------------
#include "equations.h"
//-----------------------------------------------------------------------------

int main()
{

 double a = 0,
        b = 0,
        c = 0;
 printf ( "# Please, enter coefficients of quadratic equation"
          " (first coefficient doesn's equal zero)\n" );
 scanf ( "%lg %lg %lg", &a, &b, &c );

 double x_base          = 0,
        x_ex            = 0;
 int    number_of_roots = 0;

 if ( a == 0 )
 {
  number_of_roots = solve_linear ( b, c,  &x_base );
 }
 else
 {
  number_of_roots = solve_quadratic ( a, b, c, &x_base, &x_ex );
 }

 //! Analysis of possible cases
 switch ( number_of_roots )
 {
  case 0 :
            printf ( "# This equation doesn't have any roots\n" );
            break;
  case 1 :
            printf ( "# This equation has one root:\n"
                     "%8lg\n", x_base );
            break;
  case 2 :
            printf ( "# This equation has two roots:\n"
                     "%8lg %8lg\n", x_base, x_ex );
            break;
  default :
            printf ( "# I don't know, what's going on. And you?\n" );
            break;
 }

 return 0;

}
