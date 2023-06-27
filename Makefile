V=1
SOURCE_DIR=src
BUILD_DIR=build
include $(N64_INST)/include/n64.mk
ROM_VERSION=1.0
NAME=sm64-blj-trainer-$(ROM_VERSION)
ROMNAME=$(NAME).z64
FS=$(BUILD_DIR)/data.dfs

all: $(ROMNAME)
.PHONY: all

build/main.o: .FORCE
.FORCE:

SRCS = $(wildcard $(SOURCE_DIR)/*.c)
OBJS = $(SRCS:$(SOURCE_DIR)/%.c=$(BUILD_DIR)/%.o)

$(ROMNAME): N64_ROM_TITLE="sm64 blj trainer"
$(ROMNAME): $(FS)

$(FS): $(wildcard fs/*)
	$(N64_MKDFS) $@ fs

$(BUILD_DIR)/$(NAME).elf: $(OBJS)

clean:
	rm -f $(BUILD_DIR)/* *.z64
.PHONY: clean

-include $(wildcard $(BUILD_DIR)/*.d)