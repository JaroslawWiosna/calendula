APP=calendula

CXXFLAGS=-I. -std=c++17 -Wall -fno-exceptions -nodefaultlibs -ggdb
LIBS=-lc

.PHONY: all run clean

all: $(APP)

run: clean $(APP)
	./$(APP)

$(APP): $(wildcard *.cpp) $(wildcard *.hpp) 
	$(CXX) $(CXXFLAGS) main.cpp -o $(APP) $(LIBS)

