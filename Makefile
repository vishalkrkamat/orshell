SRC_DIR := src
BUILD_DIR := build
CC := gcc
CFLAGS := -g -Wall -Wextra -O2

# Default target: make <filename-without-.c>
%: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@echo "🔍 Building $< ..."
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$@ $<
	@echo "🚀 Running $@ ..."
	@./$(BUILD_DIR)/$@

# Create build directory if missing
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean build artifacts
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
