### Introduction

RVC is a version control

### Dependecies

> * OpenSS
> * ZLIB

The source code of these libraries can be downloaded into `third_party/`

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
* state: like a tree but it's temporary
* branches: stores hashes and its branches line by line
* objects/: stores all objects

Objects:
* blob: stores compressed data and path
* tree: stores list of blobs
* commit: commit hash, prev commit hash, tree hash, author, email, branch, message, date: dd:mm:yy mm:hh

Commands:
* init: creates file structure
* add: craetes blobs out of added files and add it to the stage file
* commit: craetes a commit out of the stage file
* status: prints info about the current project status
* gc: deletes unnecessary objects