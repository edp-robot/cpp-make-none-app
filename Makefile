CC = gcc
CacheDIR = ../cache
CFLAGS = -Iinclude -Iunity -I/usr/local/include -I/usr/include -I$(CacheDIR)/microhttpd/include -MMD -MP
LDFLAGS = -L/usr/local/lib -L/usr/lib -L$(CacheDIR)/microhttpd/lib -lmicrohttpd

SRC_DIR = src
TEST_DIR = tests
INCLUDE_DIR = include
BUILD_DIR = target

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
TEST_FILES = $(wildcard $(TEST_DIR)/*.c)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
TEST_OBJ_FILES = $(TEST_FILES:$(TEST_DIR)/%.c=$(BUILD_DIR)/%.o) $(BUILD_DIR)/unity.o $(BUILD_DIR)/server.o

EXEC = $(BUILD_DIR)/app
TEST_EXEC = $(BUILD_DIR)/test_main

-include $(OBJ_FILES:.o=.d)

.PHONY: all build test clean install install-dependencies

all: build test

$(BUILD_DIR)/.dirstamp:
	mkdir -p $(BUILD_DIR)
	touch $(BUILD_DIR)/.dirstamp

build: $(BUILD_DIR)/.dirstamp $(EXEC)

$(EXEC): $(OBJ_FILES)
	$(CC) -o $@ $^ $(LDFLAGS)

test: $(BUILD_DIR)/.dirstamp $(TEST_EXEC)
	LD_LIBRARY_PATH=$(CacheDIR)/microhttpd/lib ./$(TEST_EXEC)

$(TEST_EXEC): $(TEST_OBJ_FILES)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)/.dirstamp
$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c | $(BUILD_DIR)/.dirstamp
$(BUILD_DIR)/%.o: $(CacheDIR)/Unity/src/%.c | $(BUILD_DIR)/.dirstamp
	$(CC) -c $< -o $@ $(CFLAGS)

install: install_dependencies

install_dependencies:
	$(MAKE) -f dependencies.mk install_dependencies CacheDIR=$(CacheDIR)

clean:
	rm -rf $(BUILD_DIR)
