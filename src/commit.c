#include "commit.h"

static char* readStageFile(size_t*);
static void makeTree(char*, size_t, unsigned char*);
static struct metadata makeMetadata();
static void createCommit(unsigned char*);
static int validHash(unsigned char*);
static void clearStageFile();
static void clearMetadata(struct metadata* metadata);

int commit(char** files, int number_of_files)
{
	size_t data_size = 0;
	char* data = NULL;
	unsigned char tree_hash[HASH_SIZE] = { 0 };

	data = readStageFile(&data_size);
	makeTree(data, data_size, tree_hash);
	createCommit(tree_hash);
	clearStageFile();

	if (!data) {
		addError("nothing to commit");
		errno = EINVAL;
	} else {
		free(data);
	}

	return errno;
}

static char* readStageFile(size_t* filesize)
{
	FILE* file = NULL;
	char* data = NULL;

	file = fopen(STAGE_FILE, "r");

	if (!file) {
		// The file is expected to always exist, so if it has not been created,
		//	then create it now but return with an error since there is no stage info to process
		file = fopen(STAGE_FILE, "w");
		fclose(file);
		errno = ENOENT;
		return NULL;
	}

	*filesize = getSizeOfFile(file);
	data = malloc(*filesize + 1);

	if (data) {
		data[*filesize] = '\0';
		fread(data, sizeof(data), *filesize, file);
	} else {
		addError("cannot allocate memory");
	}

	fclose(file);

	return data;
}

static void makeTree(char* data, size_t data_size, unsigned char* tree_hash)
{
	FILE* file = NULL;
	char* new_filename = NULL;

	if (!data)
		return;

	makeHash(data, data_size, tree_hash);

	new_filename = concatFileAndDirNames(tree_hash, HASH_SIZE, OBJECTS_DIR, strlen(OBJECTS_DIR));
	if (!new_filename) return;
	file = fopen(new_filename, "w");
	if (!file) return;

	fwrite(data, data_size, 1, file);
	fclose(file);
	free(new_filename);
}

static struct metadata makeMetadata()
{
	time_t nowtime;
	struct metadata metadata;

	time(&nowtime);
	strftime(metadata.date_and_time, 20, "%d/%m/%Y %H:%M:%S", localtime(&nowtime));

	metadata.prev_commit_hash = getHeadCommmitHash();
	metadata.commit_hash = NULL;
	metadata.tree_hash = NULL;
	metadata.author = NULL;
	metadata.email = NULL;
	metadata.branch_name = NULL;
	metadata.message = NULL;

	return metadata;
}

static void createCommit(unsigned char* tree_hash)
{
	struct metadata metadata;

	if (!validHash(tree_hash))
		return;

	metadata = makeMetadata();
	clearMetadata(&metadata);
}

static void clearStageFile()
{
	FILE* file = fopen(STAGE_FILE, "w");
	fclose(file);
}

static void clearMetadata(struct metadata* metadata)
{
	free(metadata->commit_hash);
	free(metadata->tree_hash);
	free(metadata->author);
	free(metadata->email);
	free(metadata->branch_name);
	free(metadata->message);
}

static int validHash(unsigned char* hash)
{
	for (unsigned i = 0; i < HASH_SIZE; i++)
		if (hash[i] != 0)
			return 1;
	return 0;
}
