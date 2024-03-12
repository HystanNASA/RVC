#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <openssl/sha.h>

#include "paths.h"

#define CHUNK 0x4000
#define HASH_SIZE (SHA256_DIGEST_LENGTH + 1)
#define MAX_BRANCH_SIZE 64

size_t getSizeOfFile(FILE* file);
void makeHash(char*, size_t, unsigned char*);
void realHexToStrHex(unsigned char*, unsigned char*, int);
char* concatFileAndDirNames(const void* const, size_t, const void* const, size_t);
char* getLastBranchCommitHash(const char* const);
char* getHeadCommmitHash();
char* getHeadBranchName();

#endif // UTILS_H
