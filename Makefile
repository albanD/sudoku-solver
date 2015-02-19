GCC = g++
LD = $(GCC)

TARGET = build/TestSudoku
LIBRARY = build/libSudokuSolver.so
DEBUGEXE = build/debug

SOURCES_LIB = $(wildcard src/*.cpp)
INCLUDE_LIB = include
INCLUDE_LIB_ARG = $(foreach d, $(INCLUDE_LIB), -I$d)
OBJECTS_LIB = $(SOURCES_LIB:.cpp=.o)
all: CSHAREDFLAGS = -std=c++11 -c -fPIC $(INCLUDE_LIB_ARG)
debug: CSHAREDFLAGS = -std=c++11 -c -g $(INCLUDE_LIB_ARG)
LDSHAREDFLAGS = -shared

SOURCES_TEST = $(wildcard test/*.cpp)
INCLUDE_TEST = test $(INCLUDE_LIB)
INCLUDE_TEST_ARG = $(foreach d, $(INCLUDE_TEST), -I$d)
OBJECTS_TEST = $(SOURCES_TEST:.cpp=.o)
all: CFLAGS = -std=c++11 -c -Wall $(INCLUDE_TEST_ARG)
debug: CFLAGS = -std=c++11 -c -Wall -g $(INCLUDE_TEST_ARG)
LDFLAGS = -Lbuild -lSudokuSolver -lstdc++

LDDEBUGFLAGS = -lstdc++ -g -gdwarf-3

all: $(LIBRARY) $(TARGET)
debug: $(DEBUGEXE)

src/%.o: src/%.cpp
	$(GCC)  $(CSHAREDFLAGS) $< -o $@

$(OBJECTS_TEST): $(SOURCES_TEST)
	$(GCC) $(CFLAGS) $^ -o $@


$(LIBRARY): $(OBJECTS_LIB)
	mkdir -p build
	$(LD) -o $@ $^ $(LDSHAREDFLAGS)

$(TARGET): $(OBJECTS_TEST)
	$(LD) -o $@ $^ $(LDFLAGS)

$(DEBUGEXE): $(OBJECTS_LIB) $(OBJECTS_TEST)
	$(LD) -o $@ $^ $(LDDEBUGFLAGS)


cl:
	rm $(OBJECTS)

clean:
	rm $(TARGET) $(LIBRARY) $(DEBUGEXE) $(OBJECTS_LIB) $(OBJECTS_TEST)
