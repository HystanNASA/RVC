#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <openssl/sha.h>

size_t getSizeOfFile(FILE* file);
void makeHash(char*, size_t, unsigned char*);
void realHexToStrHex(unsigned char*, unsigned char*, int);

#endif // UTILS_H