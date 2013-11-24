#include "stack.h"
// FIXME Where is constructor?
int Stack_Destruct(struct Stack_t **st);
// FIXME Where is Stack_OK?
int Stack_Dump(const struct Stack_t *st);
// FIXME Where is Stack_Assert?
int Stack_Push(struct Stack_t **st, const elem_t value);
elem_t Stack_Pop(struct Stack_t **st);
int Stack_Arithmetic(struct Stack_t **st, const int action);
int Stack_Interface();
