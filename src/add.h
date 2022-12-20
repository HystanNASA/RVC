#ifndef ADD_H
#define ADD_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/stat.h>

#include <openssl/sha.h>
#include <zlib.h>

int addFilesToStagingArea(char**, int);

#endif // ADD_H
