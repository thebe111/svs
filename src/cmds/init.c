#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

typedef struct {
    char* path;
    mode_t mode;
    char* content;
} InitFileTemplate;

static InitFileTemplate 
init_template[] = {
    {".svs", S_IFDIR, 0},
    {".svs/branches", S_IFDIR, 0},
    {".svs/objects", S_IFDIR, 0},
    {".svs/refs", S_IFDIR, 0},
    {".svs/refs/tags", S_IFDIR, 0},
    {".svs/refs/heads", S_IFDIR, 0},
    {".svs/refs/heads/HEAD", S_IFREG, "ref: ref/heads/master"}
};

void cmd_init(int argc, char** argv) {
    int bufsize = 200;
    char* cwd = malloc(bufsize);

    for (;; bufsize *= 2) {
        if(getcwd(cwd, sizeof(cwd)) == NULL) {
            bufsize += PATH_MAX;
            cwd = realloc(cwd, bufsize);
        }

        printf("%d\n", bufsize);

        if (errno != ERANGE) {
            break;
        }
    }

    printf("%s", cwd);

    /* for (int i = 0; i < sizeof(init_template) / sizeof(InitFileTemplate); i++) { */
        /* if(mkdir(strcat(cwd, init_template[i].path), init_template[i].mode) != EXIT_SUCCESS) { */
            /* perror("error to init the repo\n"); */
        /* } */

        /* if(init_template[i].content) { */
            /* int fd = open(init_template[i].path, O_WRONLY); */

            /* if(write(fd, init_template[i].content, sizeof(init_template[i].content)) != sizeof(init_template[i].content)) { */
                /* perror("error to write on init files\n"); */
            /* } */
        /* } */
    /* } */

    free(cwd);
}
