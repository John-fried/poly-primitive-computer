TARGET = ppc
PREFIX = /usr/local
BINDIR = $(PREFIX)/bin

CFLAGS = -MMD -Wall -Wextra -Wpedantic -std=c11 -I.
LDFLAGS = -Wl,--gc-sections
RELEASE_FLAGS = -Os -s -ffunction-sections -fdata-sections
DEBUG_FLAGS = -g -O0 -DDEBUG

BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
INSTR_DIR = instr

SOURCE = $(wildcard *.c)
INSTR_SOURCE = $(wildcard $(INSTR_DIR)/*.c)
ALL_SOURCE = $(INSTR_SOURCE) $(SOURCE)
OBJS := $(ALL_SOURCE:%.c=$(OBJ_DIR)/%.o)

.PHONY: all clean debug install uninstall

all: CFLAGS += $(RELEASE_FLAGS)
all: $(TARGET)

debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(OBJS:.o=.d)

install: all
	install -d $(DESTDIR)$(BINDIR)
	install -m 755 $(TARGET) $(DESTDIR)$(BINDIR)

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/$(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
