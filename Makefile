# compiler settings
CXX=clang++
CC=clang

CXXFLAGS=-Wall -Wextra -Wpedantic -std=c++23
CFLAGS=-Wall -Wextra -Wpedantic

# paths
BUILD_PATH=build
INCLUDE_PATH=include
LIB_PATH=lib
SRC_PATH=src

# executable
BIN_NAME=game

# libraries
LDFLAGS=-L$(LIB_PATH)/glfw
LDLIBS=-lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl

# source files
CPP_SOURCES=$(wildcard $(SRC_PATH)/*.cpp)
C_SOURCES=$(wildcard $(SRC_PATH)/*.c)

# object files
CPP_OBJECTS=$(CPP_SOURCES:$(SRC_PATH)/%.cpp=$(BUILD_PATH)/%.o)
C_OBJECTS=$(C_SOURCES:$(SRC_PATH)/%.c=$(BUILD_PATH)/%.o)

OBJECTS=$(CPP_OBJECTS) $(C_OBJECTS)

# link object files into executable
$(BIN_NAME): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) $(LDLIBS) -o $@

# compile c++ files
$(BUILD_PATH)/%.o: $(SRC_PATH)/%.cpp
	@mkdir -p $(BUILD_PATH)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_PATH) -c $< -o $@

# compile c files
$(BUILD_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(BUILD_PATH)
	$(CC) $(CFLAGS) -I$(INCLUDE_PATH) -c $< -o $@

# cleanup
.PHONY: clean
clean:
	rm -rf $(BUILD_PATH) $(BIN_NAME)
