#pragma once
// FIXME It will be more accurate to hide this type inside stack, see below
// You can remove this line here
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
private:
	mytype *data_;
	int size_;
	int count_;
public:
  // FIXME typedef double mytype;
  // Now you can access this type everywhere, when you use your stack:
  // Stack::mytype x = 5.0;
  // Now it is very clear, what is mytype and where it is used a lot - in a stack.
	Stack(int size);
	~Stack();
	bool Push(mytype Value);
	bool OK() const;
	bool Pop(mytype *Value);
	void Dump() const;
};

