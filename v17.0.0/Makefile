CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./src

SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build

SRC_FILES := $(shell find $(SRC_DIR) -name "*.cpp")
TEST_FILES := $(shell find $(TEST_DIR) -name "*.cpp")

SRC_OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))
TEST_OBJECTS := $(patsubst $(TEST_DIR)/%.cpp,$(BUILD_DIR)/tests_%.o,$(TEST_FILES))

TARGET = $(BUILD_DIR)/runTests

all: $(BUILD_DIR) $(TARGET)

$(TARGET): $(SRC_OBJECTS) $(TEST_OBJECTS)
	@if [ -z "$^" ]; then echo "No source files found!"; exit 1; fi
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/tests_%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

run: all
	./$(TARGET)