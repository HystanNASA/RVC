#include "init.h"

static int initHead(FILE*);
static int initBranches(FILE*);

int createFileStructure()
{   
	FILE* head, *branches;

	if(mkdir(ROOT_DIR, 0777) != 0)
		return errno;

	if(mkdir(OBJECTS_DIR, 0777) != 0)
		return errno;

	head = fopen(HEAD_FILE, "w");
	if (head == NULL)
		return errno;
	initHead(head);
	fclose(head);

	if (fclose(fopen(STAGE_FILE, "w")) != 0)
		return errno;

	branches = fopen(BRANCHES_FILE, "w");
	if (branches == NULL)
		return errno;
	initBranches(branches);
	fclose(branches);

	return errno;
}

static int initHead(FILE* file)
{
	const char init_branch_name[] = "master";
	fwrite(init_branch_name, sizeof(char), sizeof(init_branch_name), file);
	return errno;
}

static int initBranches(FILE* file)
{
	const char init_branch_name[] = "master\000000000000000000000000000000000\0";
	fwrite(init_branch_name, sizeof(char), sizeof(init_branch_name), file);
	return errno;
}
