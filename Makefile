# Path for the executable
BIN_PATH := bin/
OBJ_PATH := obj/

CXXFLAGS += -std=c++14 -static-libgcc -static-libstdc++

# General compiler settings
ifndef NDEBUG
CXXFLAGS += -g -Wall
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

fire_wasm: create_dir make_src make_fire compile_fire_wasm

make_fire: 
	@$(MAKE) --no-print-directory -s -C src/Fire

compile_fire: TARGET := Fire.exe

compile_fire: all_windows

compile_fire_lin: TARGET := Fire

compile_fire_lin: all_linux

compile_fire_wasm: TARGET := Fire.html

compile_fire_wasm: all_wasm

################################################################################
# DOT TUNNEL
################################################################################
dottunnel: create_dir make_src make_dottunnel compile_dottunnel

dottunnel_lin: create_dir make_src make_dottunnel compile_dottunnel_lin

dottunnel_wasm: create_dir make_src make_dottunnel compile_dottunnel_wasm

make_dottunnel: 
	@$(MAKE) --no-print-directory -s -C src/DotTunnel

compile_dottunnel: TARGET := DotTunnel.exe

compile_dottunnel: all_windows

compile_dottunnel_lin: TARGET := DotTunnel

compile_dottunnel_lin: all_linux

compile_dottunnel_wasm: TARGET := DotTunnel.html

compile_dottunnel_wasm: all_wasm

################################################################################
# ROTOZOOM
################################################################################
rotozoom: create_dir make_src make_rotozoom compile_rotozoom

rotozoom_lin: create_dir make_src make_rotozoom compile_rotozoom_lin

rotozoom_wasm: create_dir make_src make_rotozoom compile_rotozoom_wasm

make_rotozoom: 
	@$(MAKE) --no-print-directory -s -C src/RotoZoom

compile_rotozoom: TARGET := RotoZoom.exe

compile_rotozoom: all_windows

compile_rotozoom_lin: TARGET := RotoZoom

compile_rotozoom_lin: all_linux

compile_rotozoom_wasm: TARGET := RotoZoom.html

compile_rotozoom_wasm: all_wasm


################################################################################
# DEFORMATIONS
################################################################################
deformations: create_dir make_src make_deformations compile_deformations

deformations_lin: create_dir make_src make_deformations compile_deformations_lin

deformations_wasm: create_dir make_src make_deformations compile_deformations_wasm

make_deformations: 
	@$(MAKE) --no-print-directory -s -C src/Deformations

compile_deformations: TARGET := Deformations.exe

compile_deformations: all_windows

compile_deformations_lin: TARGET := Deformations

compile_deformations_lin: all_linux

compile_deformations_wasm: TARGET := Deformations.html

compile_deformations_wasm: all_wasm

################################################################################
# PLASMA
################################################################################
plasma: create_dir make_src make_plasma compile_plasma

plasma_lin: create_dir make_src make_plasma compile_plasma_lin

plasma_wasm: create_dir make_src make_plasma compile_plasma_wasm

make_plasma: 
	@$(MAKE) --no-print-directory -s -C src/Plasma

compile_plasma: TARGET := Plasma.exe

compile_plasma: all_windows

compile_plasma_lin: TARGET := Plasma

compile_plasma_lin: all_linux

compile_plasma_wasm: TARGET := Plasma.html

compile_plasma_wasm: all_wasm

################################################################################
# PLANES
################################################################################
planes: create_dir make_src make_planes compile_planes

planes_lin: create_dir make_src make_planes compile_planes_lin

planes_wasm: create_dir make_src make_planes compile_planes_wasm

make_planes: 
	@$(MAKE) --no-print-directory -s -C src/Planes

compile_planes: TARGET := Planes.exe

compile_planes: all_windows

compile_planes_lin: TARGET := Planes

compile_planes_lin: all_linux

compile_planes_wasm: TARGET := Planes.html

compile_planes_wasm: all_wasm

################################################################################
# GEOMETRY
################################################################################
geometry: create_dir make_src make_geometry compile_geometry

geometry_lin: create_dir make_src make_geometry compile_geometry_lin

geometry_wasm: create_dir make_src make_geometry compile_geometry_wasm

make_geometry: 
	@$(MAKE) --no-print-directory -s -C src/Geometry

compile_geometry: TARGET := Geometry.exe

compile_geometry: all_windows

compile_geometry_lin: TARGET := Geometry

compile_geometry_lin: all_linux

compile_geometry_wasm: TARGET := Geometry.html

compile_geometry_wasm: all_wasm

################################################################################
# FINAL DEMO
################################################################################
finaldemo: create_dir make_src make_finaldemo compile_finaldemo

finaldemo_lin: create_dir make_src make_finaldemo compile_finaldemo_lin

finaldemo_wasm: create_dir make_src make_finaldemo compile_finaldemo_wasm

make_finaldemo: 
	@$(MAKE) --no-print-directory -s -C src/FinalDemo
	@$(MAKE) --no-print-directory -s -C src/FinalDemo/Imp

compile_finaldemo: TARGET := FinalDemo.exe

compile_finaldemo: all_windows

compile_finaldemo_lin: TARGET := FinalDemo

compile_finaldemo_lin: all_linux

compile_finaldemo_wasm: TARGET := FinalDemo.html

compile_finaldemo_wasm: all_wasm

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

all_windows: LDFLAGS += -L./lib/win -lopengl32 -lglew32 -lglfw3 -lportaudio

all_windows:
	@printf "$(GREEN)Compiling done!\n"
	@printf "$(YELLOW)Linking...\n"
	@$(CXX) $(CXXFLAGS) $(addprefix $(BIN_PATH)$(OBJ_PATH),$(shell ls $(BIN_PATH)$(OBJ_PATH))) -o $(BIN_PATH)$(TARGET) $(LDFLAGS)
	@printf "$(GREEN)Linking done!\n$(WHITE)"

################################################################################
# Linux
################################################################################

# if the variable below is not defined, the build process will look for the GLFW3 and portaudio libraries provided by RetroVFX
ifeq ($(USE_LINUX_PRECOMPILED_BINARIES), false)
all_linux: LDFLAGS +=  -lGL -lGLEW -lglfw -lportaudio 
else
all_linux: LDFLAGS += -L./lib/linux -lGL -lGLEW -lglfw -lportaudio -Wl,-rpath=./lib/linux
endif

all_linux:
	@printf "$(GREEN)Compiling done!\n"
	@printf "$(YELLOW)Linking...\n"
	@$(CXX) $(CXXFLAGS) $(addprefix $(BIN_PATH)$(OBJ_PATH),$(shell ls $(BIN_PATH)$(OBJ_PATH))) -o $(BIN_PATH)$(TARGET) $(LDFLAGS)
	@printf "$(GREEN)Linking done!\n$(WHITE)"

################################################################################
# Web Assembly
################################################################################

all_wasm: LDFLAGS += --shell-file assets/base_html.html -s USE_GLFW=3 -s FULL_ES3=1 -s WASM=1

ifdef EMBED_RESOURCES
all_wasm: LDFLAGS += --embed-file $(EMBED_RESOURCES)
endif

all_wasm:
	@printf "$(GREEN)Compiling done!\n"
	@printf "$(YELLOW)Linking...\n"
	@$(CXX) $(CXXFLAGS) --bind $(addprefix $(BIN_PATH)$(OBJ_PATH),$(shell ls $(BIN_PATH)$(OBJ_PATH))) -o $(BIN_PATH)$(TARGET) $(LDFLAGS)
	@printf "$(GREEN)Linking done!\n$(WHITE)"

################################################################################
# Cleaning up
################################################################################

clean:
	@rm -r -f $(BIN_PATH)$(OBJ_PATH)
	@printf "$(GREEN)Cleaned!\n$(WHITE)"

clean_main:
	@rm -r -f $(BIN_PATH)$(OBJ_PATH)main.o
	@printf "$(GREEN)Cleaned!\n$(WHITE)"

.PHONY: all clean info win