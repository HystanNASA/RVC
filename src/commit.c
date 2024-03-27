#include "commit.h"

static char* readStageFile(size_t*);
static void makeTree(char*, size_t, unsigned char*);
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

static void createCommit(unsigned char* tree_hash)
{
	time_t nowtime;
	char* data = NULL, *filename = NULL;
	struct metadata metadata;
	FILE* commit_file = NULL;

	if (!validHash(tree_hash))
		return;

	time(&nowtime);
	strftime(metadata.date_and_time, 20, "%d/%m/%Y %H:%M:%S", localtime(&nowtime));

	// Initialize metadata
	memset(metadata.commit_hash, 0, HASH_SIZE);
	metadata.prev_commit_hash = getHeadCommmitHash();
	metadata.tree_hash = tree_hash;
	metadata.author = "";
	metadata.email = "";
	metadata.branch_name = getHeadBranchName();
	metadata.message = "";

	// Lengths plus their null characters
	size_t prev_commit_hash_len = strlen(metadata.prev_commit_hash) + 1;
	size_t tree_hash_len = strlen((char*)metadata.tree_hash) + 1;
	size_t author_len = strlen(metadata.author) + 1;
	size_t email_len = strlen(metadata.email) + 1;
	size_t branch_name_len = strlen(metadata.branch_name) + 1;
	size_t message_len = strlen(metadata.message) + 1;
	size_t metadata_len = prev_commit_hash_len + tree_hash_len + author_len + email_len + branch_name_len + message_len;
	size_t pointer = 0;

	data = malloc(metadata_len);
	if (data == NULL)
		return;

	memcpy(data, metadata.prev_commit_hash, prev_commit_hash_len);
	memcpy(data + (pointer += prev_commit_hash_len), metadata.tree_hash, tree_hash_len);
	memcpy(data + (pointer += tree_hash_len), metadata.author, author_len);
	memcpy(data + (pointer += author_len), metadata.email, email_len);
	memcpy(data + (pointer += email_len), metadata.branch_name, branch_name_len);
	memcpy(data + (pointer += branch_name_len), metadata.message, message_len);

	makeHash(data, metadata_len, metadata.commit_hash);

	filename = concatFileAndDirNames(metadata.commit_hash, HASH_SIZE, OBJECTS_DIR, strlen(OBJECTS_DIR));
	if (filename == NULL)
		return;

	commit_file = fopen(filename, "w");
	if (commit_file == NULL)
		return;

	fwrite(data, metadata_len, 1, commit_file);

	free(filename);
	fclose(commit_file);

	clearMetadata(&metadata);
}

static void clearStageFile()
{
	FILE* file = fopen(STAGE_FILE, "w");
	fclose(file);
}

static void clearMetadata(struct metadata* metadata)
{
	free(metadata->branch_name);
}

static int validHash(unsigned char* hash)
{
	for (unsigned i = 0; i < HASH_SIZE; i++)
		if (hash[i] != 0)
			return 1;
	return 0;
}
