#ifndef COMMIT_H
#define COMMIT_H

#include <stdio.h>
#include <stdlib.h>

#include <openssl/sha.h>

#include "paths.h"
#include "error_handling.h"
#include "utils.h"

int commit(char**, int);

#endif // COMMIT_H
