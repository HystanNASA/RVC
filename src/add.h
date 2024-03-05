#ifndef ADD_H
#define ADD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <openssl/sha.h>
#include <zlib.h>

#include "paths.h"
#include "error_handling.h"
#include "utils.h"

int addFilesToStagingArea(char**, int);

#endif // ADD_H
