CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./include

SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build

LIB = $(BUILD_DIR)/libtester.a
TARGET = $(BUILD_DIR)/runTests

SRC_FILES := $(shell find $(SRC_DIR) -name "*.cpp")
TEST_FILES := $(shell find $(TEST_DIR) -name "*.cpp")

# Object files
SRC_OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/obj/%.o,$(SRC_FILES))
TEST_OBJECTS := $(patsubst $(TEST_DIR)/%.cpp,$(BUILD_DIR)/tests_%.o,$(TEST_FILES))

all: $(BUILD_DIR) $(LIB) $(TARGET)

# -------------------------
# Build static library
# -------------------------
$(LIB): $(SRC_OBJECTS)
	@echo "Archiving library..."
	ar rcs $@ $^

# -------------------------
# Link executable
# -------------------------
$(TARGET): $(TEST_OBJECTS) $(LIB)
	@if [ -z "$^" ]; then echo "No source files found!"; exit 1; fi
	$(CXX) $(CXXFLAGS) $(TEST_OBJECTS) $(LIB) -o $@

# -------------------------
# Compile src → obj
# -------------------------
$(BUILD_DIR)/obj/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# -------------------------
# Compile tests → obj
# -------------------------
$(BUILD_DIR)/tests_%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# -------------------------
# Build dir
# -------------------------
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

run: all
	./$(TARGET)