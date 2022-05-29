#include "svs/main.h"

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main(int argc, char** argv) {
    if (!argv[1]) {
        fprintf(stderr, "invalid command\n");
    }

    for (int i = 0; i < sizeof(cmds) / sizeof(Command); i++) {
        if (strcmp(argv[1], cmds[i].name) == 0) {
            cmds[i].fn(1, argv);
        }
    }
}
