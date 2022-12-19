#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "init.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        errno = EINVAL;
        printf("%s\n", strerror(errno));
    }

    if (strcmp(argv[1], "init") == 0 && argc == 2) {
        if (createFileStructure() != 0)
            printf("%s\n",strerror(errno));
    } else {
        errno = EINVAL;
        printf("%s\n", strerror(errno));
    }

    return 0;
}