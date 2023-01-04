#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

#include <errno.h>

const static unsigned ERROR_LIMIT = 32;
static unsigned error_index = 0;
static const char* errors[32];

void addError(const char*);
unsigned getNumberOfErrors();
const char* getError(unsigned);

#endif // ERROR_HANDLING_H