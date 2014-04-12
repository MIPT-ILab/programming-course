#include "vector.hpp"

Vector_t::Vector_t ( int dim, double * x )
  {
    dim_ = dim;
    x_ = new double[dim_];
    for ( int i = 0; i < dim_; i ++ )
      {
        x_[i] = x[i];
      }
    printf ( "Construction %p\n", this );
  }

Vector_t::Vector_t ( const Vector_t & that )
  {
    double * tmp = new double[that.dim_];
    for ( int i = 0; i < that.dim_; i ++ )
      {
        tmp[i] = that.x_[i];
      }
    Vector_t ( that.dim_, tmp );
  }

Vector_t::~Vector_t ( )
  {
    dim_ = 0;
    delete [] ( x_ );
    printf ( "Destruction %p\n", this );
  }

Vector_t & Vector_t::operator = ( const Vector_t & that )
  {
    if ( this == &that )
      {
        return *this;
      }
    dim_ = that.dim_;
    for ( int i = 0; i < dim_; i ++ )
      {
        x_[i] = that.x_[i];
      }
    return *this;
  }

void Vector_t::dump ( )
  {
    printf ( "Dim = %d\n", dim_ );
    for ( int i = 0; i < dim_; i ++ )
      {
        printf ( "%lg\n", x_[i] );
      }
  }

const Vector_t operator + ( const Vector_t & v1, const Vector_t & v2 )
  {
    try
      {
        if ( v1.dim_ != v2.dim_ ) throw 1; //! Dimensions don't match
        double * tmp = new double[v1.dim_];
        for ( int i = 0; i < v1.dim_; i ++ )
          {
            tmp[i] = v1.x_[i] + v2.x_[i];
          }
        return Vector_t ( v1.dim_, tmp );
      }
    catch ( int error )
      {
        if ( error == 1 )
          exit(1);
      } 
  }

const Vector_t operator - ( const Vector_t & v1, const Vector_t & v2 )
  {
    try
      {
        if ( v1.dim_ != v2.dim_ ) throw 1; //! Dimensions don't match
        double * tmp = new double[v1.dim_];
        for ( int i = 0; i < v1.dim_; i ++ )
          {
            tmp[i] = v1.x_[i] - v2.x_[i];
          }
        return Vector_t ( v1.dim_, tmp );
      }
    catch ( int error )
      {
        if ( error == 1 )
          exit(1);
      } 
  }
