#ifndef H_VECTOR
#define H_VECTOR

//!-------- Headers -----------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
//!----------------------------------------------------------------------------

//!-------- Classes -----------------------------------------------------------
class Vector_t
  {
    public :
      Vector_t ( int dim, double * x ); //! Constructor
      Vector_t ( const Vector_t & that ); //! Copy constructor
      ~Vector_t ( ); //! Destructor
      Vector_t & operator = ( const Vector_t & that ); //! Assignment operator
      void dump ( );

      friend const Vector_t operator + ( const Vector_t & v1, const Vector_t & v2 );
      friend const Vector_t operator - ( const Vector_t & v1, const Vector_t & v2 );

    private :
      int dim_;
      double * x_;
  };
//!----------------------------------------------------------------------------

#endif
