GCC = gcc
LD = $(GCC)

TARGET = build/TestSudoku
LIBRARY = build/libSudokuSolver.so

SOURCES_LIB = $(wildcard src/*.cpp)
INLCUDE_LIB = $(wildcard include/*.hpp)
OBJECTS_LIB = $(SOURCES_LIB:.cpp=.o)
CSHAREDFLAGS = -c -fPIC -Iinclude
LDSHAREDFLAGS = -shared

SOURCES_TEST = $(shell echo test/*.cpp)
INLCUDE_TEST = $(shell echo test/*.hpp) $(INLCUDE_LIB)
OBJECTS_TEST = $(SOURCES_TEST:.cpp=.o)
CFLAGS = -c -Wall -g -O -Iinclude
LDFLAGS = -Lbuild -lSudokuSolver -lstdc++

all: $(LIBRARY) $(TARGET)

$(OBJECTS_LIB): $(SOURCES_LIB)
	$(GCC) $(CSHAREDFLAGS) $^ -o $@

$(OBJECTS_TEST): $(SOURCES_TEST)
	$(GCC) $(CFLAGS) $^ -o $@


$(LIBRARY): $(OBJECTS_LIB)
	$(LD) -o $@ $^ $(LDSHAREDFLAGS)

$(TARGET): $(OBJECTS_TEST)
	$(LD) -o $@ $^ $(LDFLAGS)



cl:
	rm $(OBJECTS)

clean:
	rm $(TARGET) $(OBJECTS_LIB) $(OBJECTS_TEST)