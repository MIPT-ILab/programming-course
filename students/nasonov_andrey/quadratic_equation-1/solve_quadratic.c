//{============================================================================
//! solve_quadratic - solve a quadratic equation specified by its coefficients.
//!
//! @param      a       Equation a-coefficient
//! @param      b       Equation b-coefficient
//! @param      c       Equation c-coefficient
//! @param[out] x_base  1st root of equation, if exist (if not, value will be unchanged)
//! @param[out] x_ex    2nd root of equation, if exist (if not, value will be unchanged)
//!
//! @return             Number of roots
//!
//! @note               Function doesn't solve linear equations
//}============================================================================

//-------- Headers ------------------------------------------------------------
#include "equations.h"
//-----------------------------------------------------------------------------

int solve_quadratic ( double a, double b, double c, double* x_base, double* x_ex )
{

 //! Necessary safety	
 assert ( a      != 0    );
 assert ( x_base != NULL );
 assert ( x_ex   != NULL );
 assert ( x_base != x_ex );

 //! Discriminant
 double d = ( pow ( b, 2 ) ) - 4 * a * c;

 //! Analysis of three porssible cases
 if ( d < 0 )
 {
  return 0;
 }
 else
 {
  if ( d == 0 )
  {
   *x_base = - b / ( 2 * a );
   return 1;
  }
  else
  { 
   *x_base = ( - b + sqrt ( d ) ) / ( 2 * a );
   *x_ex = ( - b - sqrt ( d ) ) / ( 2 * a );
   return 2;
  }
 }

}
