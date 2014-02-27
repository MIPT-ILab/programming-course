#pragma once
typedef double mytype;

#include <stdio.h>
#include <stdlib.h>

#define ASSERT(cond) \
	if(!cond) {\
	printf("%s, file: %s, line: %d", #cond, __FILE__, __LINE__);\
	abort();\
	};


class Stack
{
public:
	mytype *data_;
	int size_;
	int count_;
	Stack(int size);
	~Stack();
	bool Push(mytype Value);
	bool OK() const;
	bool Pop(mytype *Value);
	void Dump() const;
};

