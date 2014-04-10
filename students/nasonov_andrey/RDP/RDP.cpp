#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

enum Type_t
{
  NUMBER,
  VARIABLE,
  SUM,
  PRODUCT,
  DIFFERENCE,
  DIVISION,
};

struct Item_t
{
  Type_t name_;
  const char * value_;
};

class Tree_t
{

  Item_t data_;
  Tree_t * left_;
  Tree_t * right_;

  public:
    Tree_t ( Item_t data, Tree_t * left, Tree_t * right )
    {
      data_ = data;
      left_ = left;
      right_ = right;
    }
    void dump ( int d )
    {
      for ( int i = 0; i < d; i ++ )
        printf ( " " );
      printf ( "%s\n", data_.value_ );
      if ( left_ != NULL )
      {
        left_->dump(d+1);
      }
      if ( right_ != NULL )
      {
        right_->dump(d+1);
      }
    }
    Item_t getData()
    { return data_; }
    Tree_t * getLeft()
    { return left_; }
    Tree_t * getRight()
    { return right_; }

  friend Tree_t * makeSum ( Tree_t * t1, Tree_t * t2 )
  {
    Item_t tmp = { SUM, "+" };
    Tree_t * t = new Tree_t ( tmp, t1, t2 );
    return t;
  }
  friend Tree_t * makeProduct ( Tree_t * t1, Tree_t * t2 )
  {
    Item_t tmp = { PRODUCT, "*" };
    Tree_t * t = new Tree_t ( tmp, t1, t2 );
    return t;
  }
  friend Tree_t * makeDifference ( Tree_t * t1, Tree_t * t2 )
  {
    Item_t tmp = { DIFFERENCE, "-" };
    Tree_t * t = new Tree_t ( tmp, t1, t2 );
    return t;
  }
  friend Tree_t * makeDivision ( Tree_t * t1, Tree_t * t2 )
  {
    Item_t tmp = { DIVISION, "/" };
    Tree_t * t = new Tree_t ( tmp, t1, t2 );
    return t;
  }

};

Tree_t * deriv ( Tree_t * t )
{
  Item_t x = t->getData();
  switch ( x.name_ )
  {
    case NUMBER :
    {
      Item_t q = { NUMBER, "0" };
      Tree_t * tmp = new Tree_t ( q, NULL, NULL );
      return tmp;
    }
    case VARIABLE :
    {
      Item_t q = { NUMBER, "1" };
      Tree_t * tmp = new Tree_t ( q, NULL, NULL );
      return tmp;
    }
    case SUM :
    {
      Tree_t * tmp = makeSum ( deriv(t->getLeft()), deriv(t->getRight()) );
      return tmp;
    }
    case PRODUCT :
    {
      Tree_t * tmp = makeSum ( makeProduct ( t->getLeft(), deriv(t->getRight()) ), makeProduct ( deriv(t->getLeft()), t->getRight() ) );
      return tmp;
    }
    case DIVISION :
    {
      Tree_t * tmp = makeDivision ( makeDifference ( makeProduct ( deriv(t->getLeft()), t->getRight() ), makeProduct ( t->getLeft(), deriv(t->getRight()) ) ), makeProduct ( t->getLeft(), t->getLeft() ) );
      return tmp;
    }
    case DIFFERENCE :
    {
      Tree_t * tmp = makeDifference ( deriv(t->getLeft()), deriv(t->getRight()) );
      return tmp;
    }
    default :
    { throw 1; }
  }
}

/*
G ::= E
E ::= T { [ - + ] T } *
T ::= P { [ * / ] P } *
P ::= ( E ) | N
N ::= [ 0 - 9 ] +
*/

Tree_t * getG ( char* str );
Tree_t * getE ();
Tree_t * getT ();
Tree_t * getN ();
Tree_t * getP ();

const char * str;
int i = 0;

Tree_t * getG ( const char * s )
{
  str = s;
  Tree_t * tmp = getE();
  assert ( str[i] == '\0' ); 
  return tmp;
}

Tree_t * getE()
{
  Tree_t * tmp = NULL;
  Tree_t * val1 = getT();
  while ( ( str[i] == '+' ) || ( str[i] == '-' ) )
  {
    char op = str[i];
    i++;
    Tree_t * val2 = getT();
    if ( op == '+' )
      Tree_t * tmp = makeSum ( val1, val2 );
    if ( op == '-' )
      Tree_t * tmp = makeDifference ( val1, val2 );
  }
  return tmp;
}

Tree_t * getT()
{
  Tree_t * tmp = NULL;
  Tree_t * val1 = getP();
  while ( ( str[i] == '*' ) || ( str[i] == '/' ) )
  {
    char op = str[i];
    i++;
    Tree_t * val2 = getP();
    if ( op == '*' )
      Tree_t * tmp = makeProduct ( val1, val2 );
    if ( op == '/' )
      Tree_t * tmp = makeDivision ( val1, val2 );
  }
  return tmp;
}

Tree_t * getP()
{
  Tree_t * tmp = NULL;
  if ( str[i] == '(' )
  {
    i++;
    Tree_t * tmp = getE();
    assert ( str[i] == ')' );
    i++;
  }
  else
  {
    Tree_t * tmp = getN();
  }
  return tmp;
}

Tree_t * getN()
{
  Item_t q;
  char * val = new char[16];
  int j = 0;
  if ( str[i] == 'x' )
  {
    q = { VARIABLE, "x" };
  }
  else
  {
    while ( ( '0' <= str[i] ) && ( str[i] <= '9' ) )
    {
      val[j] = str[i];
      i++;
      j++;
    }
    const char * nval = val;
    q = { NUMBER, nval };
  }
  Tree_t * tmp = new Tree_t ( q, NULL, NULL );
  return tmp;
}

int main ( )
{
  char * s;
  scanf ( "%s", s );
  const char * cs = s;
  Tree_t * t = getG ( cs );
  Tree_t * result = deriv ( t );
  return 0;
}
