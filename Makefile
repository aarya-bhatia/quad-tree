CXX=clang++
CXXFLAGS=-Wall -g -std=c++14
INCLUDES=$(shell find src -type d)
CPPFLAGS=$(addprefix -I, $(INCLUDES)) -MMD -MP
SRC=$(shell find src -name *.cpp)
OBJ=$(SRC:src/%.cpp=obj/%.o)
LDLIBS=-lsfml-graphics -lsfml-window -lsfml-system
TARGET_EXE=main

all: $(TARGET_EXE)

$(TARGET_EXE): $(OBJ)
	$(CXX) $(LDLIBS) $^ -o $@

obj/%.o: src/%.cpp src/algorithm/Quad.h src/algorithm/AABB.h
	mkdir -p $(dir $@);
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf obj $(TARGET_EXE)