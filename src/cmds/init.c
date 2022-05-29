#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct {
    char* path;
    uint16_t flags;
    mode_t mode;
    char* content;
    int16_t content_length;
} InitFileTemplate;

static InitFileTemplate init_template[] = {
    {"/.svs", 0, S_IFDIR | S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH, 0, 0},
    {"/.svs/branches", 0, S_IFDIR | S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH, 0, 0},
    {"/.svs/objects", 0, S_IFDIR | S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH, 0, 0},
    {"/.svs/refs", 0, S_IFDIR | S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH, 0, 0},
    {"/.svs/refs/tags", 0, S_IFDIR | S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH, 0, 0},
    {"/.svs/refs/heads", 0, S_IFDIR | S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH, 0, 0},
    {"/.svs/refs/heads/HEAD",
     O_CREAT | O_WRONLY,
     S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH,
     "ref: ref/heads/master",
     21}};

void
cmd_init(int argc, char** argv) {
    char* cwd;
    int8_t init_template_length = sizeof(init_template) / sizeof(InitFileTemplate);

    if ((cwd = getcwd(NULL, 0)) == NULL) {
        perror("failed to get the current working directory\n");
    }

    for (int i = 0; i < init_template_length; i++) {
        int16_t path_length = sizeof(cwd) + sizeof(init_template[i].path);
        char* buffer = (char*) malloc(sizeof(char*) * path_length);

        memcpy(buffer, cwd, sizeof(char*) * sizeof(cwd));

        if (init_template[i].flags != 0) {
            int fd;

            if ((fd = open(strcat(buffer, init_template[i].path), init_template[i].flags, init_template[i].mode))
                == -1) {
                perror("error to init the file content\n");
            }

            if (init_template[i].content) {
                if (write(fd, init_template[i].content, init_template[i].content_length)
                    != init_template[i].content_length) {
                    perror("error to write on init files\n");
                }
            }
            // @@@: do nothing if the directory exists
        } else if (mkdir(strcat(buffer, init_template[i].path), init_template[i].mode) != 0) {
            perror("error to init the repo\n");
        }

        free(buffer);
    }

    free(cwd);
}
