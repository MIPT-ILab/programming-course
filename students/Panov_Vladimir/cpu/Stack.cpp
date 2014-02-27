#include "Stack.h"

Stack::Stack(const int size) {
	printf("Stack Construct.\n");
	data_ = new mytype[size];
	count_ = 0;
	size_ = size;
}


Stack::~Stack() {
	delete [] data_;
	count_ = -1;
	size_ = -1;
	printf("Stack Destruct\n");
}

bool Stack::OK() const {
	ASSERT(this);
	if ((0 <= count_ && count_ <= size_))
		return true;
	return false;
}

bool Stack::Push(mytype Value) {
	if (!OK())
		return false;
	if (count_ < size_) {
		data_[count_++] = Value;
	}
	else
		return false;
	return true;
}

bool Stack::Pop(mytype *Value) {
	ASSERT(Value);
	if (!OK())
		return false;
	if (count_ > 0) {
		*Value = data_[--count_];
	}
	else {
		return false;
	}
	return true;
}

void Stack::Dump() const {
	printf("DUMP Stack is ");
	if (OK()) {
		printf("ok\n");
		printf("size = %d ; counter = %d\n", size_, count_);
		for (int i = 0; i < count_; i++) {
			printf("%d : %lf\n", i, data_[i]);
		}
		printf("DUMP END.\n");
	}
	else {
		printf("BAD BAD BAD \n");
		printf("DUMP END.\n");
	}
}