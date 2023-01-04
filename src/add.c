#include "add.h"

#define CHUNK 0x4000
#define HASH_SIZE (SHA256_DIGEST_LENGTH + 1)

const char* ROOT_DIR = ".rvc/";
const char* OBJECTS_DIR = ".rvc/objects/";

static size_t getSizeOfFile(FILE*);
static void makeHash(char*, size_t, unsigned char*);
static void realHexToStrHex(unsigned char*, unsigned char*, int);
static void createBlob(char*, unsigned char*, char*);
static void addToStage(unsigned char*, int);

int addFilesToStagingArea(char** files, int number_of_files)
{
    if (number_of_files < 1) {
        errno = EINVAL;
        addError("nothing to add");
        return errno;
    }
    
    unsigned char* stagingData = malloc(number_of_files * HASH_SIZE);

    for (size_t i = 0; i < number_of_files && errno == 0; i++)
    {
        unsigned char hash[HASH_SIZE];
        FILE* file = fopen(files[i], "rb");
        size_t size_of_file = 0;
        size_t bytes_read = 0;
        char* data = NULL;

        hash[SHA256_DIGEST_LENGTH] = '\0';

        if (file == NULL)
            return errno;

        size_of_file = getSizeOfFile(file);
        data = malloc(sizeof(*data) * size_of_file + 1);
        data[size_of_file] = '\0';
        bytes_read = fread(data, sizeof(*data), size_of_file, file);

        if (bytes_read != size_of_file || data == NULL)
            return errno;

        makeHash(data, size_of_file, hash);
        createBlob(files[i], hash, data);
        strncpy((char*)(stagingData + (i * HASH_SIZE)), (const char*)hash, HASH_SIZE);

        fclose(file);
        free(data);
    }

    if (!errno)
        addToStage(stagingData, number_of_files);

    free(stagingData);

    return errno;
}

static size_t getSizeOfFile(FILE* file)
{
    size_t size_of_file = 0;

    fseek(file, 0, SEEK_END);
    size_of_file = ftell(file);
    fseek(file, 0, SEEK_SET);

    return size_of_file;
}

static void makeHash(char* data, size_t data_size, unsigned char* hash)
{
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, data, data_size);
    SHA256_Final(hash, &sha256);

    realHexToStrHex(hash, hash, SHA256_DIGEST_LENGTH);
}

static void realHexToStrHex(unsigned char* xp, unsigned char* bb, int n)
{
    const char xx[]= "0123456789abcdef";
    while (--n >= 0) xp[n] = xx[(bb[n>>1] >> ((1 - (n&1)) << 2)) & 0xF];
}

static void createBlob(char* filename, unsigned char* hash, char* data)
{
    unsigned char out[CHUNK];
    char* new_filename = NULL;
    FILE* file = NULL;
    z_stream strm;

    new_filename = malloc(sizeof(char) * (HASH_SIZE + strlen(OBJECTS_DIR)));
    memcpy(new_filename, OBJECTS_DIR, strlen(OBJECTS_DIR));
    memcpy(new_filename + strlen(OBJECTS_DIR), hash, HASH_SIZE);

    file = fopen(new_filename, "wb");

    if (file == NULL)
        return;

    fwrite(filename, sizeof(char), strlen(filename), file);

    strm.zalloc = Z_NULL;
    strm.zfree  = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = strlen(data);
    strm.next_in = (unsigned char *) data;

    int status = deflateInit2(&strm, Z_DEFAULT_COMPRESSION, Z_DEFLATED,
                              15 | 16, 8, Z_DEFAULT_STRATEGY);
    if (status < 0)
        return;

    do {
        int have;
        strm.avail_out = CHUNK;
        strm.next_out = out;
        
        int status = deflate (& strm, Z_FINISH);
        if (status < 0)
            return;

        have = CHUNK - strm.avail_out;
        fwrite (out, sizeof (char), have, file);
    } while (strm.avail_out == 0);
    
    deflateEnd(&strm);
    free(new_filename);
    fclose(file);
}

static void addToStage(unsigned char* hash_filenames, int number_of_hashes)
{
    const char* stage_filename = "stage";
    char* filename = NULL;
    FILE* file = NULL;
    int filename_size;

    filename_size = sizeof(char) * (strlen(stage_filename) + strlen(ROOT_DIR));
    filename = malloc(filename_size + 1);
    filename[filename_size] = '\0';
    memcpy(filename, ROOT_DIR, strlen(ROOT_DIR));
    memcpy(filename + strlen(ROOT_DIR), stage_filename, strlen(stage_filename));

    file = fopen(filename, "w");

    if (file == NULL)
        return;

    fwrite(hash_filenames, HASH_SIZE, number_of_hashes, file);

    free(filename);
    fclose(file);
}
