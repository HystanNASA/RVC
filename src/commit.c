#include "commit.h"

static char* readStageFile();
static void makeTree(char*, char[]);
static void makeMetadata();
static void createCommit(char[]);
static int validHash(char[]);

int commit(char** files, int number_of_files)
{
	char* data = NULL;
	char tree_hash[SHA256_DIGEST_LENGTH] = { 0 };

	data = readStageFile();
	makeTree(data, tree_hash);
	createCommit(tree_hash);

	if (!data) {
		addError("nothing to commit");
		errno = EINVAL;
	} else {
		free(data);
	}

	return errno;
}

static char* readStageFile()
{
	FILE* file = NULL;
	char* data = NULL;
	size_t filesize = 0;

	file = fopen(STAGE_FILE, "r");

	if (!file) {
		// The file is expected to always exist, so if it has not been created,
		//	then create it now but return with an error since there is no stage info to process
		file = fopen(STAGE_FILE, "w");
		fclose(file);
		errno = ENOENT;
		return NULL;
	}

	filesize = getSizeOfFile(file);
	data = malloc(filesize + 1);

	if (data) {
		data[filesize] = '\0';
		fread(data, sizeof(data), filesize, file);
	} else {
		addError("cannot allocate memory");
	}

	fclose(file);

	return data;
}

static void makeTree(char* data, char tree_hash[])
{
	if (!data)
		return;
}

static void makeMetadata() {}

static void createCommit(char tree_hash[]) 
{
	if (!validHash(tree_hash))
		return;

	makeMetadata();
}

static int validHash(char hash[])
{
	for (unsigned i = 0; i < SHA256_DIGEST_LENGTH; i++)
		if (hash[i] != 0)
			return 1;
	return 0;
}
