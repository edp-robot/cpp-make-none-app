CC = g++
CacheDIR = ../cache
CFLAGS = -Iinclude -I$(CacheDIR)/Unity/src -I$(CacheDIR)/microhttpd/include -I/usr/local/include -I/usr/include -MMD -MP
LDFLAGS = -L/usr/local/lib -L/usr/lib -L$(CacheDIR)/microhttpd/lib -lmicrohttpd

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

.PHONY: all build clean test install install-dependencies

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
	LD_LIBRARY_PATH=$(CacheDIR)/microhttpd/lib ./$(TEST_EXEC)

$(TEST_EXEC): $(TEST_OBJ_FILES)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf $(BUILD_DIR)

install: install_dependencies

install_dependencies:
	$(MAKE) -f dependencies.mk install_dependencies CacheDIR=$(CacheDIR)
