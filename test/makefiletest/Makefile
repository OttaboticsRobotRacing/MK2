##################################################
# Compiler settings
##################################################

# Set compiler to g++
CXX			= g++

# Compiler flags
XFLAGS		= -g -Wall -std=c++11

##################################################
# Directory macros
##################################################

IDIR		= include
OBJDIR		= build
SRCDIR		= src
OUTDIR		= bin

##################################################
# Required object dependencies
##################################################

_OBJECTS	= test.o
OBJECTS		= $(patsubst %,$(OBJDIR)/%,$(_OBJECTS))

##################################################
# Libraries
##################################################

# OpenCV library
INC1		= `pkg-config --cflags --libs opencv`
# User-created headers
INC2		= -I$(IDIR)
# All include directories and libraries
INCDIRS		= $(INC1) $(INC2)

##################################################
# Compiler flags
##################################################

CXXFLAGS	= $(INCDIRS) $(XFLAGS)

##################################################
# Make rules
##################################################

.PHONY: all
all: $(OBJECTS)
	@echo "\n----- Compiling main -----\n"
	@echo $(CXX) $(OBJECTS) $(SRCDIR)/main.cpp -o $(OUTDIR)/main $(CXXFLAGS)
	@mkdir -p build
	@mkdir -p bin
	@mkdir -p lib
	$(CXX) $(OBJECTS) $(SRCDIR)/main.cpp -o $(OUTDIR)/main $(CXXFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@echo "\n----- Compiling object file:" $@ "from" $< "-----\n"
	@echo $(CXX) -c -o $@ $< $(CXXFLAGS)
	@mkdir -p build
	$(CXX) -c -o $@ $< $(CXXFLAGS)


.PHONY: clean
clean:
	@echo "\n----- Cleaning object files -----\n"
	rm -rf $(OBJDIR)/*.o
