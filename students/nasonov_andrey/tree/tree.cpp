#include "tree.hpp"

Tree_t::Tree_t ( const char * data )
  {
    data_ = new char[16];
    strncpy ( data_, data, 16 );
    right_ = NULL;
    left_  = NULL;
  }

Tree_t::~Tree_t ( )
  {
    delete [] data_;
    if ( right_ != NULL )
      right_->~Tree_t ( );
    if ( left_ != NULL )
      left_->~Tree_t ( );
  }

Tree_t::Tree_t ( const Tree_t & that )
  {
    Tree_t tmp ( that.data_ );
  }

Tree_t & Tree_t::operator = ( const Tree_t & that )
  {
    if ( this == &that )
      {
        return *this;
      }
    strncpy ( data_, that.data_, 16 );
    right_ = that.right_;
    left_ = that.left_;
    return *this;
  }

void Tree_t::dump ( )
  {
    if (right_!=NULL)
      right_->dump ( );
    printf ( "%s\n", data_ );
    if (left_!=NULL)
      left_->dump ( );
  }

const Tree_t operator + ( const Tree_t & t1, const Tree_t & t2 )
  {
    Tree_t tmp ( "+" );
    tmp.left_ = new Tree_t ( t1.data_ );
    tmp.right_ = new Tree_t ( t2.data_ );
    return tmp;
  }

/*
const Tree_t & operator - ( const Tree_t & t1, const Tree_t & t2 );
const Tree_t & operator / ( const Tree_t & t1, const Tree_t & t2 );
const Tree_t & operator * ( const Tree_t & t1, const Tree_t & t2 );
*/
