TARGET = ppc
FLAGS = -MMD -Wall -Wextra -Wpedantic -I.
CC = gcc

BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
INSTR_DIR = instr

SOURCE = $(wildcard *.c)
INSTR_SOURCE = $(wildcard $(INSTR_DIR)/*.c)

ALL_SOURCE = $(INSTR_SOURCE) $(SOURCE)
OBJS      := $(ALL_SOURCE:%.c=$(OBJ_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	@echo "  LD      $@"
	@$(CC) $(OBJS) -o $@

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "  CC      $<"
	@$(CC) $(FLAGS) -c $< -o $@


clean:
	rm -rf $(BUILD_DIR) $(TARGET)
