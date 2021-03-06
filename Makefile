APP=calendula

CXXFLAGS=-I. -std=c++17 -Wall -fno-exceptions -nodefaultlibs -ggdb
LIBS=-lc

.PHONY: all run clean

all: $(APP)

run: clean $(APP)
	./$(APP)

# Taken from https://stackoverflow.com/a/51730966
version.txt:
	printf '"%s"' `git describe --tags --always --dirty` | grep -qsf - version.txt \
	|| printf >version.txt 'const char version[]="%s";\n' `git describe --tags --always --dirty`

$(APP): $(wildcard *.cpp) $(wildcard *.hpp) 3rd_party/aids.hpp version.txt
	$(CXX) $(CXXFLAGS) main.cpp -o $(APP) $(LIBS)

