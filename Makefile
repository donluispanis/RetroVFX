#Makefile for X-Kating Project

# Name of the executable created (.exe will be added automatically if necessary)
TARGET := Demo

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

#Colors
GREEN  := \033[1;32m
YELLOW := \033[1;33m
BLUE   := \033[0;36m

################################################################################
# FIRE
################################################################################
fire: create_dir make_src make_fire compile_fire

fire_lin: create_dir make_src make_fire compile_fire_lin

make_fire: 
	@$(MAKE) --no-print-directory -s -C src/Fire

compile_fire: TARGET := Fire

compile_fire: all_windows

compile_fire_lin: TARGET := Fire

compile_fire_lin: all_linux

################################################################################
# GENERAL
################################################################################

all: create_dir make_src all_windows

linux: create_dir make_src all_linux

create_dir: make_bin_dir make_obj_dir

make_bin_dir:
	@$(MKDIR_P) $(BIN_PATH)

make_obj_dir:
	@$(MKDIR_P) $(BIN_PATH)$(OBJ_PATH)
	@printf "$(YELLOW)Compiling...\n"

make_src:
	@$(MAKE) --no-print-directory -s -C src

################################################################################
# Windows 
################################################################################
all_windows: LDFLAGS += -L./lib/win -lopengl32 -lglew32 -lm -lmingw32 -lglfw3

all_windows:
	@printf "$(GREEN)Compiling done!\n"
	@printf "$(YELLOW)Linking...\n"
	@$(CXX) $(CXXFLAGS) $(addprefix $(BIN_PATH)$(OBJ_PATH),$(shell ls $(BIN_PATH)$(OBJ_PATH))) -o $(BIN_PATH)$(TARGET) $(LDFLAGS)
	@printf "$(GREEN)Linking done!\n"

################################################################################
# Linux
################################################################################
all_linux: LDFLAGS += -L./lib/linux -lGL -lGLEW -lglfw -Wl,-rpath=./lib/linux

all_linux:
	@printf "$(GREEN)Compiling done!\n"
	@printf "$(YELLOW)Linking...\n"
	@$(CXX) $(CXXFLAGS) $(addprefix $(BIN_PATH)$(OBJ_PATH),$(shell ls $(BIN_PATH)$(OBJ_PATH))) -o $(BIN_PATH)$(TARGET) $(LDFLAGS)
	@printf "$(GREEN)Linking done!\n"

clean:
	@rm -r -f $(BIN_PATH)$(OBJ_PATH)
	@printf "$(GREEN)Cleaned!\n"
	
.PHONY: all clean info win