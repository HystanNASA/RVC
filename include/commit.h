#ifndef COMMIT_H
#define COMMIT_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include <openssl/sha.h>

#include "paths.h"
#include "error_handling.h"
#include "utils.h"

struct metadata
{
	char* commit_hash;
	char* prev_commit_hash;
	char* tree_hash;
	char* author;
	char* email;
	char* branch_name;
	char* message;
	char date_and_time[20];
};

int commit(char**, int);

#endif // COMMIT_H
