#ifndef H_TREE
#define H_TREE

//!-------- Headers -----------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//!----------------------------------------------------------------------------

//!-------- Classes -----------------------------------------------------------
class Tree_t
  {
    public :
      char * data_;
      Tree_t * left_;
      Tree_t * right_;
      Tree_t ( const char * data ); //! Constructor
      ~Tree_t ( ); //! Destructor
      Tree_t ( const Tree_t & that ); //! Copy constructor
      Tree_t & operator = ( const Tree_t & that ); //! Assignment operator
      Tree_t & operator [] ( int x );
      void dump ( );

      friend const Tree_t operator + ( const Tree_t & t1, const Tree_t & t2 );
      friend const Tree_t & operator - ( const Tree_t & t1, const Tree_t & t2 );
      friend const Tree_t & operator / ( const Tree_t & t1, const Tree_t & t2 );
      friend const Tree_t & operator * ( const Tree_t & t1, const Tree_t & t2 );
  };
//!----------------------------------------------------------------------------

#endif
