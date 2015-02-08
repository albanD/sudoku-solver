GCC = g++
LD = $(GCC)

TARGET = build/TestSudoku
LIBRARY = build/libSudokuSolver.so

SOURCES_LIB = $(wildcard src/*.cpp)
INLCUDE_LIB = include
INLCUDE_LIB_ARG = $(foreach d, $(INLCUDE_LIB), -I$d)
OBJECTS_LIB = $(SOURCES_LIB:.cpp=.o)
CSHAREDFLAGS = -c -fPIC $(INLCUDE_LIB_ARG)
LDSHAREDFLAGS = -shared

SOURCES_TEST = $(wildcard test/*.cpp)
INLCUDE_TEST = test $(INLCUDE_LIB)
INLCUDE_TEST_ARG = $(foreach d, $(INLCUDE_TEST), -I$d)
OBJECTS_TEST = $(SOURCES_TEST:.cpp=.o)
CFLAGS = -c -Wall -g -O $(INLCUDE_TEST_ARG)
LDFLAGS = -Lbuild -lSudokuSolver -lstdc++


all: $(LIBRARY) $(TARGET)

$(OBJECTS_LIB): $(SOURCES_LIB)
	$(GCC) $(CSHAREDFLAGS) $^ -o $@

$(OBJECTS_TEST): $(SOURCES_TEST)
	$(GCC) $(CFLAGS) $^ -o $@


$(LIBRARY): $(OBJECTS_LIB)
	mkdir -p build
	$(LD) -o $@ $^ $(LDSHAREDFLAGS)

$(TARGET): $(OBJECTS_TEST)
	$(LD) -o $@ $^ $(LDFLAGS)



cl:
	rm $(OBJECTS)

clean:
	rm $(TARGET) $(OBJECTS_LIB) $(OBJECTS_TEST)