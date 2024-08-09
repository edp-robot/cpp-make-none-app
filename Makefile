CC = g++
CFLAGS = -std=c++11 -Iinclude -MMD -MP
LDFLAGS = -Llib -lmicrohttpd

SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = target
TEST_DIR = tests

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
TEST_FILES = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJ_FILES = $(TEST_FILES:$(TEST_DIR)/%.cpp=$(BUILD_DIR)/%.o)
TEST_OBJ_FILES := $(filter-out $(BUILD_DIR)/main.o, $(TEST_OBJ_FILES))

EXEC = $(BUILD_DIR)/app
TEST_EXEC = $(BUILD_DIR)/test_app

# Включаем зависимости
-include $(OBJ_FILES:.o=.d)
-include $(TEST_OBJ_FILES:.o=.d)

all: build test

build: $(BUILD_DIR)/.dirstamp $(EXEC)

$(BUILD_DIR)/.dirstamp:
	mkdir -p $(BUILD_DIR)
	touch $(BUILD_DIR)/.dirstamp

$(EXEC): $(OBJ_FILES)
	$(CC) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)/.dirstamp
	$(CC) $(CFLAGS) -c $< -o $@

test: $(BUILD_DIR)/.dirstamp $(TEST_EXEC)
	LD_LIBRARY_PATH=lib:$$LD_LIBRARY_PATH ./$(TEST_EXEC)

$(TEST_EXEC): $(OBJ_FILES) $(TEST_OBJ_FILES)
	$(CC) -o $@ $(filter-out $(BUILD_DIR)/main.o, $^) $(LDFLAGS)

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp | $(BUILD_DIR)/.dirstamp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all build clean test
