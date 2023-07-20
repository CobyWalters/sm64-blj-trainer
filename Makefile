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
WAV_DIR := $(RES_DIR)/sfx
WAV_FILES := $(wildcard $(WAV_DIR)/*.wav)
WAV64_FILES := $(WAV_FILES:.wav=.wav64)
RAW_FILES := $(wildcard $(WAV_DIR)/*.raw)

$(WAV64_FILES): $(WAV_DIR)/%.wav64: $(WAV_DIR)/%.wav
	$(N64_AUDIOCONV) -o $(WAV_DIR) $<

# Move resources to DFS
$(DFS_FILE): $(RAW_FILES)
	$(N64_MKDFS) $@ resources

SRCS := $(wildcard $(SOURCE_DIR)/*.c)
OBJS := $(SRCS:$(SOURCE_DIR)/%.c=$(BUILD_DIR)/%.o)
$(BUILD_DIR)/$(NAME).elf: $(OBJS)

clean:
	rm -f $(BUILD_DIR)/* *.z64
.PHONY: clean

-include $(wildcard $(BUILD_DIR)/*.d)