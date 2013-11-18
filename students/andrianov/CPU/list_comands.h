

#define SET_CMD_(name, num, code) CMD_##name = (num),

enum
{
    #include "commands.h"
};

#undef SET_CMD_




