The Makefile is provided for executing convenience, running it won't rebuild the project
The _Makefile can be used to compile and rebuild the project, but may require edits
    because it assumes that CMake is the primary method of building/running
In order to build with CMake then run:
cmake -S . -B build
cmake --build build --parallel
make run

Inside Makefile, there are more ways to run the executable, and reading the docs (which I spent hours on)
    would help you understand the inner workings better