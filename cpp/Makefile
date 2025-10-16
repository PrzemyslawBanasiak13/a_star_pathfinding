CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall
LIBS := -lsfml-graphics -lsfml-window -lsfml-system

all: main

main: a_star.cpp node.hpp
	$(CXX) $(CXXFLAGS) a_star.cpp -o aStar $(LIBS)

clean:
	rm -f aStar