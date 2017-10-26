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
MODULEDIR	:= modules/
TESTDIR		:= test/

##################################################
# Required object dependencies
##################################################

OBJECTS		:=

##################################################
# Modules
##################################################

MODULES 	:= sample

# Include *.mk files from modules
include $(patsubst %,$(MODULEDIR)/%/module.mk,$(MODULES))

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
	@echo "\n----- Compiling core -----\n"
	@mkdir -p $(OUTDIR)
	$(CXX) $(OBJECTS) $(SRCDIR)/core.cpp -o $(OUTDIR)/core $(CXXFLAGS)

.PHONY: test
test: $(OBJECTS)
	@echo "\n----- Compiling test -----\n"
	@mkdir -p $(OUTDIR)
	$(CXX) $(OBJECTS) $(TESTDIR)/test.cpp -o $(OUTDIR)/test $(CXXFLAGS)

%.o:
	$(eval FILE_NAME = $(firstword $(subst ., ,$(lastword $(subst /, ,$@)))))
	$(eval MODULE_NAME = $(word 2,$(subst /, ,$@)))
	$(eval BUILD_DIR = $(MODULEDIR)/$(MODULE_NAME)/build/)
	@mkdir -p $(BUILD_DIR)
	@echo "\n----- Compiling object file:" $@ "from" $(MODULEDIR)$(MODULE_NAME)"/src/"$(FILE_NAME)".cpp -----\n"
	$(CXX) -c -o $@ $(MODULEDIR)/$(MODULE_NAME)/src/$(FILE_NAME).cpp $(CXXFLAGS)

.PHONY: clean
clean:
	@echo "\n----- Cleaning object files -----\n"
	rm -rf $(OBJECTS)
