#ifndef SVS_MAIN_H
#define SVS_MAIN_H

#include "../cmds/add.c"
#include "../cmds/init.c"

typedef struct {
    char* name;
    void (*fn)(int, char**);
} Command;

static Command cmds[] = {{"init", &cmd_init}, {"add", &cmd_add}};

#endif
