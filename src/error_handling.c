#include "error_handling.h"

void addError(const char* message)
{
	if (error_index + 1 < ERROR_LIMIT)
		errors[error_index++] = message;
}

unsigned getNumberOfErrors()
{
	return error_index;
}

const char* getError(unsigned index)
{
	if (index <= error_index)
		return errors[index];
	return "";
}
