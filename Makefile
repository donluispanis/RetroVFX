#Makefile for X-Kating Project

# Name of the executable created (.exe will be added automatically if necessary)
TARGET := PaintLike

# Path for the executable
BIN_PATH := bin/
OBJ_PATH := obj/

# general compiler settings (might need to be set when compiling the lib, too)
ifndef NDEBUG
CXXFLAGS += -g -Wall -std=c++14
else
CXXFLAGS += -O2
endif

# Instruction to create directories
MKDIR_P = mkdir -p

#default target is Window
all: create_dir make_src all_windows
	$(warning Linking done!)

linux: create_dir make_src all_linux
	$(warning Linking done!)

create_dir: make_bin_dir make_obj_dir

make_bin_dir:
	$(warning Creating bin directory... (if it doesn't exist))
	$(MKDIR_P) $(BIN_PATH)

make_obj_dir:
	$(warning Creating obj directory... (if it doesn't exist))
	$(MKDIR_P) $(BIN_PATH)$(OBJ_PATH)

#Makes to execute
make_src:
	$(MAKE) -C src

################################################################################
# Windows 
################################################################################
all_windows: LDFLAGS += -L./lib/win -lopengl32 -lm -lmingw32 -lglfw3

all_windows:
	$(CXX) $(CXXFLAGS) $(addprefix $(BIN_PATH)$(OBJ_PATH),$(shell ls $(BIN_PATH)$(OBJ_PATH))) -o $(BIN_PATH)$(TARGET) $(LDFLAGS)

################################################################################
# Linux
################################################################################
all_linux: LDFLAGS += -L./lib/linux -lGL -lglfw -Wl,-rpath=./lib/linux

all_linux:
	$(CXX) $(CXXFLAGS) $(addprefix $(BIN_PATH)$(OBJ_PATH),$(shell ls $(BIN_PATH)$(OBJ_PATH))) -o $(BIN_PATH)$(TARGET) $(LDFLAGS)

clean:
	$(warning Cleaned!)
	rm -r $(BIN_PATH)$(OBJ_PATH)

.PHONY: all clean info win