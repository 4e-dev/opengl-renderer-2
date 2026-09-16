# compiler shtuff
compiler = clang++
flags = -Wall -Wextra -Wpedantic -std=c++23

# source files and objects
game_sources = $(wildcard src/*.cpp)
game_objects = $(game_sources:src/%.cpp=build/%.o)

test_sources = $(wildcard tests/*.cpp)
test_objects = $(test_sources:tests/%.cpp=build/tests/%.o)

# GAME BINARY!!! ૮ ˶ᵔ ᵕ ᵔ˶ ა
.PHONY: all
all: game

.PHONY: game
game: $(game_objects)
	$(compiler) $(game_objects) -Llib/glfw -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -o game

build/%.o: src/%.cpp
	mkdir -p build
	$(compiler) $(flags) -Iinclude -c $< -o $@

# TEST BINARY!!! ૮ • ﻌ - ა
.PHONY: test
test: $(test_objects)
	$(compiler) $(test_objects) -o runtest

build/tests/%.o: tests/%.cpp
	mkdir -p build/tests
	$(compiler) $(flags) -Iinclude -c $< -o $@

# cleanup
.PHONY: clean
clean:
	rm -rf build game runtest
