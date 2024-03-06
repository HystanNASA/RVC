#include "utils.h"

size_t getSizeOfFile(FILE* file)
{
	size_t size_of_file = 0;

	fseek(file, 0, SEEK_END);
	size_of_file = ftell(file);
	fseek(file, 0, SEEK_SET);

	return size_of_file;
}

void makeHash(char* data, size_t data_size, unsigned char* hash)
{
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, data, data_size);
	SHA256_Final(hash, &sha256);

	realHexToStrHex(hash, hash, SHA256_DIGEST_LENGTH);
}

void realHexToStrHex(unsigned char* xp, unsigned char* bb, int n)
{
	const char xx[]= "0123456789abcdef";
	while (--n >= 0) xp[n] = xx[(bb[n>>1] >> ((1 - (n&1)) << 2)) & 0xF];
}
