#include "stdio.h"

// just useless broken echo
int main( int argc, char* argv[ ])
{
    if ( argc == 2)
    {
        printf( "%s", argv[ 1]);
    }
    else
    {
        return 1;
    }
    return 0;
}
