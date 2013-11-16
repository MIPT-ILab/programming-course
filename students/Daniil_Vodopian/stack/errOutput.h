/** ********************************************************************
 @file		errOutput.h
 @date		2013-11-09 22:42
 @author	Daniil Vodopian <dgvodopyan@gmail.com>
 @version	1.01

 A short library for error output
***********************************************************************/
#ifndef _ERR_OUTPUT_H_ //_ERR_OUTPUT_H_
#define _ERR_OUTPUT_H_

#ifdef __cplusplus
extern "C" {
#endif 				//C++ compatibility
//----------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

#define printErr(mess)\
	printf("!# ERROR: %s  file: %s line: %d\n", mess, __FILE__, __LINE__) //print error massage
	
#ifndef UNDEBUG 	//UNDEBUG
#define assert(cond, mess) 					\
	if (!(cond)) {							\
		printErr(#mess ":: (" #cond ")");	\
		abort();							\
	}
	
#define ASSERT(cond)\
	assert(cond, "-?-")

#define struct_Assert(type, this_)			\
	if(!type ## _OK(this_)){ 					\
		type ## _Dump(this_); 						\
		printErr("broken " #type " '" #this_ "'");	\
		abort();								\
	}
	
#else 				//UNDEBUG

#define assert(cond, mess)
#define ASSERT(cond)
#define struct_Assert(type, this_)

#endif 				//UNDEBUG
//----------------------------------------------------------------------
#ifdef __cplusplus
}
#endif 				//C++ compatibility (end)

#endif 				//__ERR_OUTPUT_H_
