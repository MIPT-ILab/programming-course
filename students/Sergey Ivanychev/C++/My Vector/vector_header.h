#ifndef VECTOR_HEADER_
#define VECTOR_HEADER_

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//								INCLUDED HEADERS
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>
#include <math.h>
#include <string.h>
#include <crtdbg.h>
#include <float.h>


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//								CLASS DESCRIPTION
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

class Vector
{
public:
		double*		data;
		int			append(double value);
		int			reset();
		double		module() const;
		int			remove(int index);
		void		print(FILE* stream = stdout);
		void		dump (FILE* stream = stdout);
		int			get_memory_size();
		int			get_size();
	
					Vector();
					Vector(const Vector& a);
					Vector(int size, double* array);
				   ~Vector();
		Vector		operator+(const Vector& second) const;
		Vector		operator-(const Vector& second) const;
		Vector		operator*(double value) const ;
 friend Vector		operator*(double value, const Vector& second);
		double		operator[](int index) const;
	

private:
	int			   _memory_size;
	int			   _realloc_memory(int new_memory_size);
	int			   _extend_data();
	int			   _cut_data();
	const int		MEMORY_BLOCK_SIZE = 10;
	int				check() const;
	int				size;

};

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//								CONSTANTS
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



enum Vector_constants
{
	VECTOR_OK			= 1001,
	VECTOR_NO_MEMORY	= 1002,
	VECTOR_CUT_FAILED	= 1003,
	VECTOR_INDEX_BAD	= 1004,
	VECTOR_THIS_NULL	= 1005,
	VECTOR_DATA_NULL	= 1006,
	VECTOR_DATA_LEAK	= 1007,
	VECTOR_NOT_EGH_MEM	= 1008,
	VECTOR_BAD			= 1009,
};

const int POISON = 0xDEADBABE;


#endif