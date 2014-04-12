#include <stdio.h>

//======== Class ==============================================================
//-------- Exceptions ---------------------------------------------------------
enum Vector_Ex
{
  FORBIDDEN_SIZE,
  SELF_ASSIGNMENT,
  OUT_OF_RANGE,
  MISMATCHED_DIMENSIONS,
  INVALID_OPERATION,
};
//-----------------------------------------------------------------------------

//-------- General case -------------------------------------------------------
template < class item_T >
class Vector_t
{
  item_T * array_;
  int dim_;

  public:
    Vector_t ( int dim ); // Constructor
    Vector_t ( const Vector_t<item_T> & that ); // Copy constructor
    ~Vector_t ( ); // Destructor
    Vector_t<item_T> & operator = ( const Vector_t<item_T> & that ); // Assignment operator
    item_T & operator [] ( int index );

  friend Vector_t operator + ( const Vector_t<item_T> & V1, const Vector_t<item_T> & V2 );
  friend Vector_t operator - ( const Vector_t<item_T> & V1, const Vector_t<item_T> & V2 );
};
//-----------------------------------------------------------------------------

//-------- Special case(s) ----------------------------------------------------
template < >
class Vector_t < bool >
{
  bool * array_;
  int dim_;

  public:
    Vector_t<bool> ( int dim ) // Constructor
    {
      if ( dim <= 0 ) throw FORBIDDEN_SIZE;
      dim_ = dim;
      array_ = new bool[(dim/32)+1];
    }
    Vector_t<bool> ( const Vector_t<bool> & that ) // Copy constructor
    {
      dim_ = that.dim_;
      array_ = that.array_;
    }
    ~Vector_t ( ) // Destructor
    {
      dim_ = -1;
      delete [] array_;
    }
    Vector_t<bool> & operator = ( const Vector_t<bool> & that ) // Assignment operator
    {
      if ( &that == this ) throw SELF_ASSIGNMENT;
      dim_ = that.dim_;
      array_ = that.array_;
      return *this;
    }

//!!!! Wrong !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    bool & operator [] ( int index ) // Indexing
    {
      throw INVALID_OPERATION;
      /*
      if ( ( index < 0 ) || ( index > dim_ ) ) throw OUT_OF_RANGE;
      int slide = sizeof(int) - (index%sizeof(int)) + 1;
      int ind = index/sizeof(int);
      return ( ( ( (array_[ind]) >> slide ) % 2 ) == 1 );
      */
    }
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    friend Vector_t<bool> operator + ( const Vector_t<bool> & V1, const Vector_t<bool> & V2 )
    {
      if ( V1.dim_ != V2.dim_ ) throw MISMATCHED_DIMENSIONS;
      throw INVALID_OPERATION;
      /*
      Vector_t < bool > V ( V1.dim_ );
      for ( int i = 0; i < V.dim_; i ++ )
      {
        V[i] = V1[i] ^ V2[i];
      }
      return V;
      */
    }
    friend Vector_t<bool> operator - ( const Vector_t<bool> & V1, const Vector_t<bool> & V2 )
    {
      if ( V1.dim_ != V2.dim_ ) throw MISMATCHED_DIMENSIONS;
      throw INVALID_OPERATION;
      /*
      Vector_t < bool > V ( V1.dim_ );
      for ( int i = 0; i < V.dim_; i ++ )
      {
        V[i] = ( V1[i] ^ V2[i] ) & V1[i];
      }
      return V;
      */
    }
};
//-----------------------------------------------------------------------------
//=============================================================================

//======== Methods ============================================================
//-------- Constructor --------------------------------------------------------
template < class item_T >
Vector_t<item_T>::Vector_t ( int dim )
{
  if ( dim <= 0 ) throw FORBIDDEN_SIZE;
  dim_ = dim;
  array_ = new item_T[dim_];
}
//-----------------------------------------------------------------------------

//-------- Copy constructor ---------------------------------------------------
template < class item_T >
Vector_t<item_T>::Vector_t ( const Vector_t<item_T> & that )
{
  dim_ = that.dim_;
  array_ = that.array_;
}
//-----------------------------------------------------------------------------

//-------- Destructor ---------------------------------------------------------
template < class item_T >
Vector_t<item_T>::~Vector_t ( )
{
  dim_ = -1;
  delete [] array_;
}
//-----------------------------------------------------------------------------

//-------- Assignment operator ------------------------------------------------
template < class item_T >
Vector_t<item_T> & Vector_t<item_T>::operator = ( const Vector_t<item_T> & that )
{
  if ( &that == this ) throw SELF_ASSIGNMENT;
  dim_ = that.dim_;
  array_ = that.array_;
  return *this;
}
//-----------------------------------------------------------------------------

//-------- Indexing -----------------------------------------------------------
template < class item_T >
item_T & Vector_t<item_T>::operator [] ( int index )
{
  if ( ( index < 0 ) || ( index > dim_ ) ) throw OUT_OF_RANGE;
  return array_[index];
}
//-----------------------------------------------------------------------------

//-------- Overloaded operators -----------------------------------------------
template < class item_T >
Vector_t<item_T> operator + ( const Vector_t<item_T> & V1, const Vector_t<item_T> & V2 )
{
  if ( V1.dim_ != V2.dim_ ) throw MISMATCHED_DIMENSIONS;
  Vector_t < item_T > V ( V1.dim_ );
  for ( int i = 0; i < V.dim_; i ++ )
  {
    V[i] = V1[i] + V2[i];
  }
  return V;
}

template < class item_T >
Vector_t<item_T> operator - ( const Vector_t<item_T> & V1, const Vector_t<item_T> & V2 )
{
  if ( V1.dim_ != V2.dim_ ) throw MISMATCHED_DIMENSIONS;
  Vector_t < item_T > V ( V1.dim_ );
  for ( int i = 0; i < V.dim_; i ++ )
  {
    V[i] = V1[i] - V2[i];
  }
  return V;
}
//-----------------------------------------------------------------------------
//=============================================================================


int main ( )
{
  try
  {
  }
  catch ( Vector_Ex ex )
  {
    printf ( "%d", ex );
  }
  return 0;
}
