CC := gcc
CFLAGS := -Iinc -Wall -Wextra -std=c11 -O2

BUILD_DIR := build
SRC_DIRS := src


SRCS := $(wildcard $(SRC_DIRS)/*.c)

OBJS := $(patsubst $(SRC_DIRS)%.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

TARGET := $(BUILD_DIR)/todo-cli

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CC) $(OBJS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIRS)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

-include $(DEPS)
