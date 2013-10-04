//{============================================================================
//! solve_linear - solve a linear equation specified by its coefficients.
//!
//! @param      b       Equation b-coefficient
//! @param      c       Equation c-coefficient
//! @param[out] x_base  Root of equation
//!
//! @return             Number of roots (always 1)
//!
//! @note               Program doesn't consider case b = 0
//}============================================================================

//-------- Headers ------------------------------------------------------------
#include "equations.h"
//-----------------------------------------------------------------------------

int solve_linear ( double b, double c, double* x_base )
{

  //! Necessary safety
  assert ( b      != 0    );
  assert ( x_base != NULL );

  *x_base = - c / b;

  return 1;

}
