##################################################
# Compiler settings
##################################################

# Set compiler to g++
CXX			:= g++

# Compiler flags
XFLAGS		:= -g -Wall -std=c++11

##################################################
# Directory macros
##################################################

IDIR		:= include/
OBJDIR		:= build/
SRCDIR		:= src/
OUTDIR		:= bin/
TESTDIR		:= test/

##################################################
# Required object dependencies
##################################################

# Update this line with list of objects to be compiled
_OBJECTS	:= navigation-pid.o line-equation.o pid.o framerate.o
OBJECTS		:= $(patsubst %,$(OBJDIR)/%,$(_OBJECTS))

##################################################
# Libraries
##################################################

# OpenCV library
INC1		:= `pkg-config --cflags --libs opencv`
# User-created headers
INC2		:= $(patsubst %,-I%,$(IDIR))
# All include directories and libraries
INCDIRS		:= $(INC1) $(INC2)

##################################################
# Compiler flags
##################################################

CXXFLAGS	:= $(INCDIRS) $(XFLAGS)

##################################################
# Make rules
##################################################

.PHONY: all
all: $(OBJECTS)
	@echo "\n----- Compiling main -----\n"
	@mkdir -p build
	@mkdir -p bin
	$(CXX) $(OBJECTS) $(SRCDIR)main.cpp -o $(OUTDIR)main $(CXXFLAGS)

.PHONY: test
test: $(OBJECTS)
	@echo "\n----- Compiling test -----\n"
	@mkdir -p build
	@mkdir -p bin
	$(CXX) $(OBJECTS) $(TESTDIR)test.cpp -o $(OUTDIR)test $(CXXFLAGS)

.PHONY: framerate
framerate: $(OBJECTS)
	@echo "\n----- Compiling framerate -----\n"
	@mkdir -p build
	@mkdir -p bin
	$(CXX) $(OBJECTS) $(TESTDIR)test_framerate.cpp -o $(OUTDIR)framerate $(CXXFLAGS)

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	@echo "\n----- Compiling object file:" $@ "from" $< "-----\n"
	@mkdir -p build
	$(CXX) -c -o $@ $< $(CXXFLAGS)

.PHONY: clean
clean:
	@echo "\n----- Cleaning object files -----\n"
	rm -rf $(OBJDIR)*.o
