# Set compiler to g++
CXX=g++

# The CXXFLAGS variable sets compile flags for g++
# -g			compile with debug information
# -Wall			give verbose compiler warning
# -std=c++11	use c++11
CXXFLAGS=`pkg-config --cflags --libs opencv` -g -Wall

# list of objects
_OBJECTS=test.o
OBJECTS=$(patsubst %,build/%,$(_OBJECTS))

all: $(OBJECTS)
	@echo $(CXX) $(OBJECTS) src/main.cpp -o bin/main $(CXXFLAGS)
	$(CXX) $(OBJECTS) src/main.cpp -o bin/main $(CXXFLAGS)

build/%.o: src/%.cpp
	@echo $(CXX) -c -o $@ $< $(CXXFLAGS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)


.PHONY: clean
clean:
	rm -rf build/*.o
