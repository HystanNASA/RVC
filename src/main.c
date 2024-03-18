#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "paths.h"
#include "init.h"
#include "add.h"
#include "commit.h"
#include "error_handling.h"

const char* help_message =
"usage: rvc <command> [<args>]\n"
"Commands:\n"
"init\tCreate an empty repository in the current directory\n"
"add\tAdd files to the staging area\n"
"commit\tMake a commit of the staging area\n";

void parseCommand(int argc, char* argv[])
{
	if (strcmp(argv[1], "init") == 0 && argc == 2) {
		createFileStructure();
	} else if (strcmp(argv[1], "add") == 0) {
		addFilesToStagingArea(argv + 2, argc - 2);
	} else if (strcmp(argv[1], "commit") == 0) {
		commit(argv + 2, argc - 2);
	} else if (strcmp(argv[1], "--help") == 0) {
		printf("%s", help_message);
	} else {
		errno = EINVAL;
		addError("unknown command");
	}
}

int main(int argc, char* argv[])
{
	if (argc < 2) {
		errno = EINVAL;
		addError("no command is specified");
	} else {
		parseCommand(argc, argv);
	}

	if (errno != 0) {
		fprintf(stderr, "%s\n", strerror(errno));
		for (unsigned i = 0; i < getNumberOfErrors(); ++i) {
			fprintf(stderr, "%s\n", getError(i));
		}
	}

	return 0;
}
