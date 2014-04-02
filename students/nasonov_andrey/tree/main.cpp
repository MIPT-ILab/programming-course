#include "tree.hpp"
#include <stdio.h>
#include <stdlib.h>

int main ( )
  {
    const char * x;
    x = "asdf";
    Tree_t t ( x );
    const char * y = "qwer";
    Tree_t q ( y );
    t.dump ( );
    q.dump ( );
    t = q;
    t.dump ( );
    t = t + q;
    t.dump ( );
    return 0;
  }
