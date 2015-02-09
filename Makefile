GCC = g++
LD = $(GCC)

TARGET = build/TestSudoku
LIBRARY = build/libSudokuSolver.so

INCLUDE_LIB = include
INCLUDE_LIB_ARG = $(foreach d, $(INCLUDE_LIB), -I$d)
OBJECTS_LIB = $($(wildcard src/*.cpp):.cpp=.o)
CSHAREDFLAGS = -c -fPIC $(INCLUDE_LIB_ARG)
LDSHAREDFLAGS = -shared

SOURCES_TEST = $(wildcard test/*.cpp)
INCLUDE_TEST = test $(INCLUDE_LIB)
INCLUDE_TEST_ARG = $(foreach d, $(INCLUDE_TEST), -I$d)
OBJECTS_TEST = $(SOURCES_TEST:.cpp=.o)
CFLAGS = -c -Wall -g -O $(INCLUDE_TEST_ARG)
LDFLAGS = -Lbuild -lSudokuSolver -lstdc++


all: $(LIBRARY) $(TARGET)

src/%.o: src/%.cpp
	$(GCC) $(CSHAREDFLAGS) $< -o $@

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
