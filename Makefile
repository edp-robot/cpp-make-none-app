CC = g++
CFLAGS = -std=c++11 -Iinclude -MMD -MP
LDFLAGS = -Llib -lmicrohttpd -Wl,-rpath,lib

SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = target
TEST_DIR = tests

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
TEST_FILES = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJ_FILES = $(TEST_FILES:$(TEST_DIR)/%.cpp=$(BUILD_DIR)/%.o) $(OBJ_FILES)

EXEC = $(BUILD_DIR)/app
TEST_EXEC = $(BUILD_DIR)/test_main

-include $(OBJ_FILES:.o=.d)

.PHONY: all build clean test

all: build

$(BUILD_DIR)/.dirstamp:
	mkdir -p $(BUILD_DIR)
	touch $(BUILD_DIR)/.dirstamp

build: $(BUILD_DIR)/.dirstamp $(EXEC)

$(EXEC): $(OBJ_FILES)
	$(CC) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)/.dirstamp
	$(CC) -c $< -o $@ $(CFLAGS)

test: $(BUILD_DIR)/.dirstamp $(TEST_EXEC)
	LD_LIBRARY_PATH=lib ./$(TEST_EXEC)

$(TEST_EXEC): $(TEST_OBJ_FILES)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf $(BUILD_DIR)
