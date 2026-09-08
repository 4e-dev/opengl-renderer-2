# compiler settings
CXX=clang++
CXXFLAGS=-Wall -Wextra -Wpedantic -std=c++23

# paths
BUILD_PATH=build
INCLUDE_PATH=include
LIB_PATH=lib
SRC_PATH=src

# executable
BIN_NAME=game

# find every .cpp file under src/
SOURCES=$(wildcard $(SRC_PATH)/*.cpp)

# replace every .cpp name with its .o counterpart
OBJECTS=$(SOURCES:$(SRC_PATH)/%.cpp=$(BUILD_PATH)/%.o)

# executable
$(BIN_NAME): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

# compilation step (.cpp to .o)
$(BUILD_PATH)/%.o: $(SRC_PATH)/%.cpp
	@mkdir -p $(BUILD_PATH)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_PATH) -c $< -o $@

# cleanup
.PHONY: clean
clean:
	rm -rf $(BUILD_PATH) $(BIN_NAME)
