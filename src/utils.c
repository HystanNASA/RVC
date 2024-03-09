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

char* concatFileAndDirNames(const void* const filepath, size_t filepath_size, const void* const dirpath, size_t dirpath_size)
{
	char* new_path = malloc(sizeof(char) * (filepath_size + dirpath_size));
	if (new_path == NULL) return NULL;
	memcpy(new_path, dirpath, dirpath_size);
	memcpy(new_path + dirpath_size, filepath, filepath_size);
	return new_path;
}

char* getLastBranchCommitHash(const char* const branch_name)
{
	FILE* file = fopen(BRANCHES_FILE, "r");
	size_t filesize = 0;
	char* file_buffer = NULL;

	if (!file) return NULL;

	filesize = getSizeOfFile(file);
	file_buffer = malloc(filesize + 1);
	if (!file_buffer) {
		fclose(file);
		return NULL;
	}
	file_buffer[filesize] = '\0';
	fread(file_buffer, filesize, 1, file);

	// The max size of a branch name is 64 (+ '\0')
	char branch[MAX_BRANCH_SIZE + 1] = { 0 };
	char* commit_hash = malloc(sizeof(char) * HASH_SIZE);
	if (!commit_hash) {
		free(file_buffer);
		fclose(file);
		return NULL;
	}

	// Finds the last commit hash of the branch.
	//  The branch file content follows the format: branch_name1\0commit_hash1\0branch_name2\0commit_hash2\0...
	for (size_t i = 0, terminator_counter = 0, branch_iter = 0, commit_iter = 0; i < filesize; i++) {
		if (file_buffer[i] == '\0') {
			terminator_counter++;
		} else if (terminator_counter == 0) {
			branch[branch_iter++] = file_buffer[i];
		} else if (terminator_counter == 1) {
			commit_hash[commit_iter++] = file_buffer[i];
		} else if (terminator_counter == 2) {
			// Return the assosiated commit hash when the name is found
			if (strcmp(branch_name, branch) == 0) return commit_hash;
			terminator_counter = commit_iter = branch_iter = 0;
			memset(branch, '\0', MAX_BRANCH_SIZE);
		}
		assert(terminator_counter <= 2);
	}

	free(commit_hash);
	free(file_buffer);
	fclose(file);

	return NULL;
}

char* getHeadCommmitHash()
{
	char* branch_name = getHeadBranchName(), *commit_hash = NULL;
	if (!branch_name) return NULL;
	commit_hash = getLastBranchCommitHash(branch_name);
	free(branch_name);
	return commit_hash;
}

char* getHeadBranchName()
{
	FILE* file = fopen(HEAD_FILE, "r");
	size_t filesize = 0;
	char* branch_name = NULL;

	if (!file) return NULL;

	filesize = getSizeOfFile(file);
	branch_name = malloc(filesize + 1);
	if (!branch_name) return NULL;
	branch_name[filesize] = '\0';
	fread(branch_name, filesize, 1, file);
	fclose(file);

	return branch_name;
}
