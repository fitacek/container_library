# Directories
INCLUDE_DIR = include
SRC_DIR     = src
TEST_DIR    = test
BUILD_DIR   = build

# Compiler flags
CXX = g++
CXXFLAGS = -std=c++17 -I$(INCLUDE_DIR) -Wall -pedantic -Wextra -g -fsanitize=address
LDFLAGS = -fsanitize=address

# Targets
TEST_OBJ = $(BUILD_DIR)/test_avl_tree.o
EXEC = $(BUILD_DIR)/test_avl

# Default target
all: test

# Compile and link the test
test: $(EXEC)
	./$(EXEC)

# Build the test executable (no library object linked)
$(EXEC): $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

# Compile test source file
$(BUILD_DIR)/test_avl_tree.o: $(TEST_DIR)/test_avl_tree.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cleanup
clean:
	rm -rf $(BUILD_DIR)
