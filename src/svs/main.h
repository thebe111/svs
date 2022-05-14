#ifndef SVS_MAIN_H
#define SVS_MAIN_H

#include "../cmds/init.c"
#include "../cmds/add.c"

typedef struct {
    char* name;
    void (*fn)(int, char**);
} Command;

static Command 
cmds[] = {
    {"init", &cmd_init},
    {"add", &cmd_add}
};

#endif
