#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "init.h"
#include "add.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        errno = EINVAL;
        printf("%s\n", strerror(errno));
    }

    if (strcmp(argv[1], "init") == 0 && argc == 2) {
        createFileStructure();
    } else if (strcmp(argv[1], "add") == 0) {
        addFilesToStagingArea(argv + 2, argc - 2);
    } else {
        errno = EINVAL;
    }

    if (errno != 0) {
        fprintf(stderr, "%s\n", strerror(errno));
    }


    return 0;
}