const int OK = 1;
const int ERROR = 0;
struct Stack_t;
typedef double elem_t;
#define MAIN_INVITATION\
   "#There are such commands (without quotes):\n#\"push\" to push new value into stack,\n#\"pop\" to pop value and see it,\
   \n#\"add\" to addition,\n#\"sub\" to substraction,\n#\"mul\" to multiplication,\
   \n#\"div\" to division (value on top is the denominator),\n#\"dump\" to see stack dump,\
   \n#\"exit\" to correct exit.\n\n"
#define IS_ZERO(x) fabs(x)<DBL_EPSILON
enum actions {PUSH, POP, ADD, SUB, MUL, DIV, DUMP, EXIT, UNKNOWN, ZERO_DIV, NOT_ENOUGH};
int action(char *command);
