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
WHITE  := \033[0;37m

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
# DOT TUNNEL
################################################################################
dottunnel: create_dir make_src make_dottunnel compile_dottunnel

dottunnel_lin: create_dir make_src make_dottunnel compile_dottunnel_lin

make_dottunnel: 
	@$(MAKE) --no-print-directory -s -C src/DotTunnel

compile_dottunnel: TARGET := DotTunnel

compile_dottunnel: all_windows

compile_dottunnel_lin: TARGET := DotTunnel

compile_dottunnel_lin: all_linux

################################################################################
# ROTOZOOM
################################################################################
rotozoom: create_dir make_src make_rotozoom compile_rotozoom

rotozoom_lin: create_dir make_src make_rotozoom compile_rotozoom_lin

make_rotozoom: 
	@$(MAKE) --no-print-directory -s -C src/RotoZoom

compile_rotozoom: TARGET := RotoZoom

compile_rotozoom: all_windows

compile_rotozoom_lin: TARGET := RotoZoom

compile_rotozoom_lin: all_linux

################################################################################
# PERFORMANCE TESTS
################################################################################
perf_test: create_dir make_perf link_test

make_perf:
	@$(MAKE) --no-print-directory -s -C src/PerformanceTests

link_test:
	@printf "$(GREEN)Compiling done!\n"
	@printf "$(YELLOW)Linking...\n"
	@$(CXX) bin/obj/PerformanceTests.o bin/obj/TestTemplate.o -o bin/PerformanceTest
	@printf "$(GREEN)Linking done!\n$(WHITE)"

perf_test_asm:
	@printf "$(YELLOW)Generating assembly...\n"
	@$(CXX) -S src/PerformanceTests/PerformanceTests.cpp
	@printf "$(GREEN)Assembly generated!\n$(WHITE)"

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
	@$(MAKE) --no-print-directory -s -C src/Utils
	@$(MAKE) --no-print-directory -s -C src/ClassicDemoTemplate
	@$(MAKE) --no-print-directory -s -C src/ClassicDemoTemplate/Characters
	@$(MAKE) --no-print-directory -s -C src/ClassicDemoTemplate/RenderManager
	@$(MAKE) --no-print-directory -s -C src/ClassicDemoTemplate/WindowManager

################################################################################
# Windows 
################################################################################
all_windows: LDFLAGS += -L./lib/win -lopengl32 -lglew32 -lm -lmingw32 -lglfw3

all_windows:
	@printf "$(GREEN)Compiling done!\n"
	@printf "$(YELLOW)Linking...\n"
	@$(CXX) $(CXXFLAGS) $(addprefix $(BIN_PATH)$(OBJ_PATH),$(shell ls $(BIN_PATH)$(OBJ_PATH))) -o $(BIN_PATH)$(TARGET) $(LDFLAGS)
	@printf "$(GREEN)Linking done!\n$(WHITE)"

################################################################################
# Linux
################################################################################
all_linux: LDFLAGS += -L./lib/linux -lGL -lGLEW -lglfw -Wl,-rpath=./lib/linux

all_linux:
	@printf "$(GREEN)Compiling done!\n"
	@printf "$(YELLOW)Linking...\n"
	@$(CXX) $(CXXFLAGS) $(addprefix $(BIN_PATH)$(OBJ_PATH),$(shell ls $(BIN_PATH)$(OBJ_PATH))) -o $(BIN_PATH)$(TARGET) $(LDFLAGS)
	@printf "$(GREEN)Linking done!\n$(WHITE)"

clean:
	@rm -r -f $(BIN_PATH)$(OBJ_PATH)
	@printf "$(GREEN)Cleaned!\n$(WHITE)"

clean_main:
	@rm -r -f $(BIN_PATH)$(OBJ_PATH)main.o
	@printf "$(GREEN)Cleaned!\n$(WHITE)"

.PHONY: all clean info win