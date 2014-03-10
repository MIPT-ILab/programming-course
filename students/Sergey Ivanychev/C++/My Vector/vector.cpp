#include "vector_header.h"
#include "debug.h"


#undef PRECOND
#define PRECOND																		\
																					\
	int _check_vector = check();													\
	VERIFY(_check_vector != VECTOR_OK, _check_vector, "Vector check failed");		\

#undef POSTCOND
#define POSTCOND																	\
																					\
	_check_vector = check();														\
	VERIFY(_check_vector != VECTOR_OK, _check_vector, "Vector check failed");		\


#define POISON_DATA assert(data != NULL); for (int i = 0; i < size; ++i) data[i] = POISON;

extern FILE* strerr;
extern FILE* strlog;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


Vector::Vector()
{
	size = 0;
	data = (double*) calloc(MEMORY_BLOCK_SIZE, sizeof(double));
	_memory_size = MEMORY_BLOCK_SIZE;

	printf("Vector constructed\n");

	MVERIFY(data == NULL, "Vector:Vector: no memory established\n");
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


Vector::~Vector()
{
	
	POISON_DATA;
	size = POISON;
	_memory_size = MEMORY_BLOCK_SIZE;

	printf("Vector destructed\n");
	free(data);
	data = NULL;	
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


int Vector::append(double value)
{
	PRECOND;
	if (size % MEMORY_BLOCK_SIZE == 0 && size != 0)
	{
		int check_extend = _extend_data();
		VERIFY(check_extend != VECTOR_OK, VECTOR_NO_MEMORY, "Data extending failed");
	}
	data[size++] = value;
	
	
	POSTCOND;
	return VECTOR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


int Vector::reset()
{
	if (data != NULL)
	{
		POISON_DATA;
		free(data);
	}
	data = (double*) calloc(MEMORY_BLOCK_SIZE, sizeof(double));
	
	_memory_size = MEMORY_BLOCK_SIZE;
	size = 0;

	PRECOND;
	return VECTOR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

double Vector::module() const
{
	PRECOND;

	long double square_sum = 0;
	for (int i = 0; i < size; ++i) square_sum += data[i] * data[i];

	POSTCOND;

	return sqrt(square_sum);
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


int Vector::remove(int index)
{
	PRECOND;
	if (index >= size) return VECTOR_OK;
	
	if (index < 0) index += size;							// negative are allowed, numerating values of vector from the end
	VERIFY(index < 0, VECTOR_INDEX_BAD, "Bad index, the range is [-SIZE , SIZE - 1]");

	for (int i = index + 1; i < size; ++i) data[i - 1] = data[i];
	size--;

	if (_memory_size - size >= MEMORY_BLOCK_SIZE)
	{
		int check_cut = _cut_data();
		VERIFY(check_cut != VECTOR_OK, VECTOR_CUT_FAILED, "Failed to cut vector data");
	}

	POSTCOND;
	return VECTOR_OK;
}

/*
#define CHANGE_DATA(name, sign)														\
																					\
int Vector::##name()																\
{																					\
	int requesting = _memory_size ##sign MEMORY_BLOCK_SIZE;							\
	double* next_data = (double*) calloc(requesting, sizeof(double));				\
	VERIFY1(next_data != NULL, VECTOR_NO_MEMORY, "Calloc failed in %s", #name);		\																				\
	memcpy((void*)next_data, (void*)data, size * sizeof(double));					\																	\
	POISON_DATA;																	\
	free(data);																		\
	_memory_size = requesting;														\
																					\
	data = next_data;																\
																					\
	return VECTOR_OK;																\
}																					\

CHANGE_DATA(_extend_data, +);
CHANGE_DATA(_cut_data, -);
*/

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int Vector::check() const
{
	if (this == NULL)			return VECTOR_THIS_NULL;
	if (data == NULL)			return VECTOR_DATA_NULL;
	if (size > _memory_size)	return VECTOR_DATA_LEAK;
	return VECTOR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


void Vector::print(FILE* stream)
{
	fputc('[', stream);
	for (int i = 0; i < size-1; ++i) fprintf(stream, "%lg, ", data[i]);
	if (size - 1 >= 0) fprintf(stream, "%lg", data[size - 1]);
	fputc(']', stream);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


int Vector::_extend_data()
{
	int requesting = _memory_size + MEMORY_BLOCK_SIZE;
	double* next_data = (double*) calloc(requesting, sizeof(double));
	VERIFY(next_data == NULL, VECTOR_NO_MEMORY, "Calloc failed in EXTEND_DATA");

	memcpy((void*)next_data, (void*)data, size * sizeof(double));
	
	POISON_DATA;
	free(data);
	_memory_size += MEMORY_BLOCK_SIZE;

	data = next_data;

	return VECTOR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


int Vector::_cut_data()
{
	int requesting = _memory_size + MEMORY_BLOCK_SIZE;
	double* next_data = (double*) calloc(requesting, sizeof(double));
	VERIFY(next_data == NULL, VECTOR_NO_MEMORY, "Calloc failed in EXTEND_DATA");

	memcpy((void*)next_data, (void*)data, size * sizeof(double));
	
	POISON_DATA;
	free(data);
	_memory_size += MEMORY_BLOCK_SIZE;

	data = next_data;

	return VECTOR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


Vector::Vector(const Vector& second)
{
	MVERIFY(second.check() != VECTOR_OK, "VECTOR(const Vector&): Argument is corrupted");

	if (data != NULL)
	{
		for (int i = 1; i < size; ++i) data[i] = POISON;
		free(data);
	}
	data = (double*) calloc(second._memory_size, sizeof(double));
	MVERIFY(data == NULL, "VECTOR(const Vector&): Calloc failed");

	memcpy((void*)data, (void*)second.data, second._memory_size*sizeof(double));
	size			= second.size;
	_memory_size	= second._memory_size;
	for (int i = 1; i < size; ++i) data[i] = second.data[i];
	
	printf("Vector contructed\n");
	MVERIFY(check() != VECTOR_OK, "VECTOR(const Vector&): Postcondition failed");
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


Vector::Vector(int array_size, double* array)
{

	int reset_check = reset();
	MVERIFY(reset_check != VECTOR_OK, "Vector(int size, double* array): Reset failed");

	int realloc_check = _realloc_memory(MEMORY_BLOCK_SIZE * ((size / MEMORY_BLOCK_SIZE) + 1));
	MVERIFY(realloc_check != VECTOR_OK, "Vector(int size, double* array): Realloc failed");

	for (int i = 0; i < array_size; ++i) data[i] = array[i];

	size = array_size;

	check();
	
	printf("Vector contructed\n");

	MVERIFY(check() != VECTOR_OK, "VECTOR(int array_size, double* array): Postcondition failed");
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

Vector Vector::operator+(const Vector& second) const
{
	MVERIFY(second.check() != VECTOR_OK, "VECTOR::operator+(const Vector&): Argument is corrupted");
	MVERIFY(check() != VECTOR_OK, "VECTOR::operator+(const Vector&): Current is corrupted");

	Vector out = *this;

	if (second._memory_size > _memory_size)
	{
		int check_realloc = out._realloc_memory(second._memory_size);
		MVERIFY(check_realloc != VECTOR_OK, "VECTOR::operator+: reallocation failed");
	}

	for (int i = 0; i < second._memory_size; ++i) out.data[i] += second.data[i];
	if (second.size > out.size) out.size = second.size;

	MVERIFY(out.check() != VECTOR_OK, "VECTOR::operator+(const Vector&): Construction failed");
	return out;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


Vector Vector::operator-(const Vector& second) const
{
	MVERIFY(second.check() != VECTOR_OK, "VECTOR::operator-(const Vector&): Argument is corrupted");
	MVERIFY(check() != VECTOR_OK, "VECTOR::operator-(const Vector&): Current is corrupted");

	Vector second_copy = second;
	for (int i = 0; i < second_copy.size; ++i) second_copy.data[i] *= -1;

	Vector out = (second_copy + *this);

	MVERIFY(out.check() != VECTOR_OK, "VECTOR::operator-(const Vector&): Construction failed");
	return out;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


Vector Vector::operator*(double value) const
{
	MVERIFY(check() != VECTOR_OK, "VECTOR::operator*(double value): Current is corrupted");
	
	Vector out = *this;
	for (int i = 0; i < size; ++i) out.data[i] *= value;

	MVERIFY(out.check() != VECTOR_OK, "VECTOR::operator*(double value): Construction failed");
	return out;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


Vector operator*(double value, const Vector& second)
{
	MVERIFY(second.check() != VECTOR_OK, "Vector operator*(double value, const Vector& second): Second is corrupted");
	Vector out = second * value;

	MVERIFY(out.check() != VECTOR_OK, "Vector operator*(double value, const Vector& second): Construction failed");
	return out;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


double Vector::operator[](int index) const
{
	MVERIFY(check() != VECTOR_OK, "Vector::operator*[]: Current is corrupted");
	if (index < 0) index += size;
	if (index < 0) index = index;							// TODO!!!!!!!
	return data[index];
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


int Vector::_realloc_memory(int new_memory_size)
{
	PRECOND;
	VERIFY(new_memory_size < size, VECTOR_NOT_EGH_MEM, "VECTOR::_realloc_memory: not enough memoty for current data");
	double* new_data = (double*) calloc(new_memory_size, sizeof(double));
	VERIFY(new_data == NULL, VECTOR_NO_MEMORY, "VECTOR::_realloc_memory: calloc failed");
	memcpy((void*) new_data, (void*)data, size * sizeof(double));

	POISON_DATA;
	free(data);
	data = new_data;
	_memory_size = new_memory_size;

	POSTCOND;
	return VECTOR_OK;
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void Vector::dump(FILE* stream)
{
	fprintf(stream, "I'm vector [%08x]. I'm %s [%d]\n"
			"Size = %d, Memory = %d\n",
			this, (check() == VECTOR_OK)? "OK":"BAD", check(), size, _memory_size);

	for (int i = 0; i < size; ++i) fprintf(stream, "%dth: %lg\n", i, data[i]);
	putc('\n', stream);
	fprintf(stream, "Vector. End of dump\n");
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int Vector::get_memory_size()
{
	assert(this);
	return _memory_size;
}

int Vector::get_size()
{
	assert(this);
	return size;
}