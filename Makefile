# Define the source directory and output directory
SRC_DIR := src
BIN_DIR := bin
TRACE_DIR := trace

# Get a list of all C source files in the source directory
SRCS := $(wildcard $(SRC_DIR)/**/*.c)

# Get a list of test sets
TESTS := $(wildcard $(SRC_DIR)/*)

# Generate a list of corresponding object files in the output directory
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%,$(SRCS))

# Define the compiler and flags
CC := gcc
CFLAGS := 

# The default target is to build all binaries
all: $(OBJS)

# Rule to compile each C source file to an object file
$(BIN_DIR)/%: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -o $@

# Clean the generated binaries
clean:
	rm -rf $(BIN_DIR)/*

# Test
test:
	./test.sh

# Add a .PHONY rule to avoid conflicts with file names
.PHONY: all clean
