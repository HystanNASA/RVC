# Introduction

**RVC** is a version control

# Dependecies

Ensure that these libraries are downloaded and accessible:

> * OpenSS
> * ZLIB

The source code of these libraries can be downloaded into `third_party/`

# Build

From the root directory execute:

```
cmake -B build/
make -C build/
```

The executable will be generated in `bin/`

# Usage

```
rvc init
rvc add CMakeFile.txt README.md
rvc commit
```

# Implementation

**File structure:**
* .rvc/
	* HEAD
	* stage
	* branches
	* objects/
		* object_hash...
		* object_hash...
		* object_hash...

**Structure explanation:**
* `.rvc/`: the root directory for `RVC` in the working directory
* `HEAD`: contains the current commit or branch name
* `stage`: contains the blob names that are generated from the provided with `rvc add`
* `branches`: stores branch names and their last hashes
* `objects/`: stores all blob and tree objects

**Objects:**
* blob: stores compressed data and path
* tree: stores list of blobs
* commit: commit hash, prev commit hash, tree hash, author, email, branch, message, date: dd:mm:YY hh:mm:ss

**Commands:**
* init: creates file structure
* add: craetes blobs out of added files and add it to the stage file</br>
* *commit: craetes a commit out of the stage file (coming soon)*
* *status: prints info about the current project status (coming soon)*
* *gc: deletes unnecessary objects (coming soon)*

# Diagram

![commands](docs/commands.png)

# License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
