#include "init.h"

static int initHead(FILE*);

int createFileStructure()
{   
    FILE* head, *branches;

    if(mkdir(".rvc", 0777) != 0)
        return errno;

    if(mkdir(".rvc/objects", 0777) != 0)
        return errno;

    head = fopen(".rvc/HEAD", "w");
    if (head == NULL)
        return errno;
    initHead(head);
    fclose(head);

    if (fclose(fopen(".rvc/stage", "w")) != 0)
        return errno;

    if (fclose(fopen(".rvc/branches", "w")) != 0)
        return errno;

    return errno;
}

static int initHead(FILE* file)
{
    const char init_branch_name[] = "master";
    fwrite(init_branch_name, sizeof(char), sizeof(init_branch_name), file);
    return errno;
}