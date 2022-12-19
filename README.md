### Introduction

RVC is a version control

### Implementation

File structure:
* .rvc/
   * HEAD
   * stage
   * branches
   * objects/
        * object_hash...
        * object_hash...
        * object_hash...

Structure explanation:
* HEAD: current commit or branch name
* state: like a commit but it's temporary
* branches: stores hashes and its branches line by line
* objects/: stores all objects

Objects:
* blob: stores compressed data
* tree: represents content of a directory; directory name, stores blob hashes, and tree names
* commit: stores tree name, author, time

Commands:
* init: creates file structure
* add: craetes blobs out of added files and add it to the stage file
* commit: craetes a commit out of the stage file
* status: prints info about the current project status