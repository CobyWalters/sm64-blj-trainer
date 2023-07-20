V := 1
SOURCE_DIR    := src
BUILD_DIR     := build
include $(N64_INST)/include/n64.mk

ROM_VERSION   := 1.3
NAME          := sm64-blj-trainer-$(ROM_VERSION)
ROMNAME       := $(NAME).z64

# Project directories
RES_DIR       := resources
DFS_FILE	  := $(BUILD_DIR)/data.dfs

all: $(ROMNAME)
.PHONY: all

build/main.o: .FORCE
.FORCE:

$(ROMNAME): N64_ROM_TITLE="sm64 blj trainer"
$(ROMNAME): $(DFS_FILE)

# File conversions
SFX_DIR := $(RES_DIR)/sfx
WAV_FILES := $(wildcard $(SFX_DIR)/*.wav)
WAV64_FILES := $(WAV_FILES:.wav=.wav64)

$(WAV64_FILES): $(SFX_DIR)/%.wav64: $(SFX_DIR)/%.wav
	$(N64_AUDIOCONV) -o $(SFX_DIR) $<

# Move resources to DFS
$(DFS_FILE): $(WAV64_FILES)
	$(N64_MKDFS) $@ resources

SRCS := $(wildcard $(SOURCE_DIR)/*.c)
OBJS := $(SRCS:$(SOURCE_DIR)/%.c=$(BUILD_DIR)/%.o)
$(BUILD_DIR)/$(NAME).elf: $(OBJS)

clean:
	rm -f $(BUILD_DIR)/* *.z64
.PHONY: clean

-include $(wildcard $(BUILD_DIR)/*.d)