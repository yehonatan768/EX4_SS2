CXX = g++
CXXFLAGS = -std=c++17 -Wall
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

all: Demo test

Demo: Demo.o node.hpp tree.hpp
	$(CXX) $(CXXFLAGS) -o Demo Demo.o node.hpp tree.hpp $(LDFLAGS)

test: test.o node.hpp tree.hpp
	$(CXX) $(CXXFLAGS) -o test test.o node.hpp tree.hpp $(LDFLAGS)

Demo.o: Demo.cpp node.hpp tree.hpp
	$(CXX) $(CXXFLAGS) -c Demo.cpp

test.o: test.cpp node.hpp tree.hpp
	$(CXX) $(CXXFLAGS) -c test.cpp

clean:
	rm -f Demo test *.o

