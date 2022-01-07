CXX=clang++

WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable

CXXFLAGS=$(WARNINGS) -g -std=c++14 -O0
INCLUDES=$(shell find src -type d)
CPPFLAGS=$(addprefix -I, $(INCLUDES)) -MMD -MP
SRC=$(shell find src -name *.cpp)
OBJ=$(SRC:src/%.cpp=.obj/%.o)
LDLIBS=-lsfml-graphics -lsfml-window -lsfml-system

all: main test

main: .obj/main.o .obj/AABB.o .obj/QtNode.o .obj/Quad.o
	$(CXX) $(LDLIBS) $^ -o $@

test: .obj/test.o .obj/AABB.o .obj/QtNode.o .obj/Quad.o
	$(CXX) $(LDLIBS) $^ -o $@

.obj/%.o: src/%.cpp $(wildcard src/*.h) | .obj
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.obj:
	mkdir -p .obj

clean:
	rm -rf .obj main test