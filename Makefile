V := 1
SOURCE_DIR    := src
BUILD_DIR     := build
include $(N64_INST)/include/n64.mk

ROM_VERSION   := 1.3
NAME          := sm64-blj-trainer-$(ROM_VERSION)
ROMNAME       := $(NAME).z64

# Project directories
RES_DIR       := resources
FS_DIR		  := $(BUILD_DIR)/fs
DFS_FILE	  := $(BUILD_DIR)/data.dfs

all: $(ROMNAME)
.PHONY: all

build/main.o: .FORCE
.FORCE:

$(ROMNAME): N64_ROM_TITLE="sm64 blj trainer"
$(ROMNAME): $(DFS_FILE)

# Create a directory for files that will go into the DFS
$(shell mkdir -p $(FS_DIR))

# -------------------- File copy --------------------

RAW_FILES := $(shell find $(RES_DIR) -type f -name '*.raw')
FS_RAW_FILES := $(patsubst $(RES_DIR)/%, $(FS_DIR)/%, $(RAW_FILES))
$(FS_RAW_FILES): $(FS_DIR)/% : $(RES_DIR)/%
	@mkdir -p $(@D)
	cp $< $@

SPRITE_FILES := $(shell find $(RES_DIR) -type f -name '*.sprite')
FS_SPRITE_FILES := $(patsubst $(RES_DIR)/%, $(FS_DIR)/%, $(SPRITE_FILES))
$(FS_SPRITE_FILES): $(FS_DIR)/% : $(RES_DIR)/%
	@mkdir -p $(@D)
	cp $< $@

BIN_FILES := $(shell find $(RES_DIR) -type f -name '*.bin')
FS_BIN_FILES := $(patsubst $(RES_DIR)/%, $(FS_DIR)/%, $(BIN_FILES))
$(FS_BIN_FILES): $(FS_DIR)/% : $(RES_DIR)/%
	@mkdir -p $(@D)
	cp $< $@

# Move resources to DFS
$(DFS_FILE): $(FS_RAW_FILES) $(FS_SPRITE_FILES) $(FS_BIN_FILES)
	$(N64_MKDFS) $@ $(FS_DIR)

SRCS := $(wildcard $(SOURCE_DIR)/*.c)
OBJS := $(SRCS:$(SOURCE_DIR)/%.c=$(BUILD_DIR)/%.o)
$(BUILD_DIR)/$(NAME).elf: $(OBJS)

-include $(wildcard $(BUILD_DIR)/*.d)