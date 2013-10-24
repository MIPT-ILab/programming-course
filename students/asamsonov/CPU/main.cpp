//{-------------head----------------------------------
//
//! @file    main.cpp
//! @mainpage
//! @brief   Now first full CPU is done!!
//!			 But still this table of squares is not 
//!			 so cool as i thought it would be.
//!
//!          $Version: 1.00, Revision: 1 $
//!          $Date: 2013-10-19 20:008 $
//!
//!          - Now all great improvements will be here.
//!			 - and all versions and dates and etc. 
//!
//! @todo	 write:
//!			 - write all todo-s first.
//!
//}-------------head---------------------------------

#include "CPUwork.h"

#define N 100

int main ( int argc, const char *argv[] )
{
	FILE *fi = fopen ( INPUT, "r" );
	FILE *fo = fopen ( MC, "w" );

	CPU *myCPU = CPU_create ( 10 );
	int x = assemble ( fi, fo );
	if ( x ) { printf ( "ERROR AS: line # %d\n", x ); return 1; }

	fclose ( fi );
	fclose ( fo );

	int i = 0;
	for ( i = 1; i <= N; i++ ) {
		myCPU->ax = i;
		x = CPU_do_file ( myCPU );
		if ( x ) { printf ( "ERROR CPU: line # %d\n", x ); return 1; }
		printf ( "%d^2 = %d\n", i, myCPU->ax );
	}

	CPU_delete ( myCPU );
	return 0;
}