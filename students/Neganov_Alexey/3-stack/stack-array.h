#include "stack.h"
// FIXME Common name will be 'constructor'
struct Stack_t * Stack_Construct(int size);
// FIXME 'destructor'
int Stack_Destruct(struct Stack_t *st);
int Stack_OK(const struct Stack_t *st);
int Stack_Dump(const struct Stack_t *st);
int Stack_Assert(const struct Stack_t *st);
int Stack_Push(struct Stack_t *st, const elem_t value);
elem_t Stack_Pop(struct Stack_t *st);
int Stack_Arithmetic(struct Stack_t *st, const int action);
int Stack_Interface(struct Stack_t *st);
