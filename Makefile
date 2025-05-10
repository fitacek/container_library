# Directories
INCLUDE_DIR = include
SRC_DIR     = src
TEST_DIR    = test
BUILD_DIR   = build

# Compiler flags
CXX = g++
CXXFLAGS = -std=c++17 -I$(INCLUDE_DIR) -Wall -pedantic -Wextra -g

# Targets
LIB_OBJ = $(BUILD_DIR)/avl_tree.o
TEST_OBJ = $(BUILD_DIR)/test_avl_tree.o
EXEC = $(BUILD_DIR)/test_avl

# Default target
all: compile

# Compile the library (only the .o file)
compile: $(LIB_OBJ)

# Compile and link the test
test: $(EXEC)
	./$(EXEC)

# Build the test executable
$(EXEC): $(LIB_OBJ) $(TEST_OBJ)
	$(CXX) $^ -o $@

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/test_avl_tree.o: $(TEST_DIR)/test_avl_tree.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cleanup
clean:
	rm -rf $(BUILD_DIR)