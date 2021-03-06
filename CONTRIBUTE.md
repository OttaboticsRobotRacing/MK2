# How to contribute to MK2

## Project Documentation

Documentation for the source code for MK2 can be found at https://ottaboticsrobotracing.github.io/MK2/

## Modules

Most development is done as modules stored within the modules/ directory. Each module contains the following files/directories:

* `src/` : for source code (.cpp)
* `include/` : for header files (.hpp)
* `Makefile` : rules for compiling the code
* `module.mk` : rules for compiling the module into the core
* `README.md` : README documentation for the module

## How to contribute

### Prerequisites

* A system running Ubuntu 16.04 (a virtual machine is OK)
* OpenCV 3.4.0, a setup script can be found at https://github.com/jimde/setup-scripts/blob/master/install-opencv-with-contrib.sh
* If you plan to use Tensorflow, a setup script can be found at https://github.com/jimde/setup-scripts/blob/master/install-tensorflow-static-lib.sh (untested)

### Instructions

1. clone this repository using `git clone github.com/OttaboticsRobotRacing/MK2.git`
1. create a new branch using `git checkout -b [BRANCH NAME]`. Please use a unique and detailed branch name
1. If you're modifying an existing module, you can skip to step 12
1. Copy the sample module and rename it
1. Modify the following lines in `Makefile`
1. Modify line 26 `_OBJECTS := sample.o`; replace `sample.o` with whatever object files you will need to compile
1. Modify line 55 `$(CXX) $(OBJECTS) $(SRCDIR)main.cpp -o $(OUTDIR)main $(CXXFLAGS)`; replace `main.cpp` with the name of your main file in `src/`
1. Modify line 62 `$(CXX) $(OBJECTS) $(TESTDIR)test.cpp -o $(OUTDIR)test $(CXXFLAGS)`; replace `test.cpp` with the name of your testing file in `test/`
1. Modify the following lines in `module.mk`
1. Modify line 2 `IDIR += modules/sample/include/` and replace `sample` with the name of your module
1. Modify line 5 `OBJECTS += modules/sample/build/sample.o` to include the path to every object that is compiled
1. Compile your code with `make all` or `make test` which compiles your main file or your test file, respectively
1. Run your code with `bin/main` or `bin/test` depending if you compiled main or test
1. Any source files, such as images, should be in `bin/`
1. Once your code if fully tested and functional, submit a pull request through Github (a code review will be required)
