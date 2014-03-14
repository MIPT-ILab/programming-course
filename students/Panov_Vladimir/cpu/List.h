#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

class List
{
private:
	struct Elem {
	public:
		Elem *prev_;
		char *key_;
		int pos_;
		int num_;
		Elem *next_;
		Elem(char *key, int pos, int num);
		~Elem();
	};
	Elem *head_;
public:
	List();
	~List();
	bool add(char *key, int pos, int num);
	int search(char *key);
	int search(char *key, int *num);
	char *search(int pos);
	bool dump();
};

