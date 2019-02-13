#Makefile for FireEffect Project

#Colors
GREEN  := \033[1;32m
YELLOW := \033[1;33m
BLUE   := \033[0;36m

# Our .cpp and where to store them
SOURCES:= $(wildcard *.cpp)
_OBJECTS := $(subst .cpp,.o,$(SOURCES))
BIN_DIR := ../../bin/
OBJ_DIR := obj/
OBJECTS := $(patsubst %,$(BIN_DIR)$(OBJ_DIR)%,$(_OBJECTS))

# general compiler settings (might need to be set when compiling the lib, too)
CPPFLAGS += -I./../../ -I./../../include

ifndef NDEBUG
CXXFLAGS += -g -Wall -std=c++14 -Wno-unknown-pragmas
else
CXXFLAGS += -O2
endif

all: $(OBJECTS)

$(BIN_DIR)$(OBJ_DIR)%.o: %.cpp
	@printf "$(BLUE)Compiling $@\n"
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $^

clean:
	@rm -r -f $(BIN_DIR)$(OBJ_DIR)
	@printf "$(GREEN)Cleaned!\n"

info:
		$(info $(SOURCES))
		$(info $(OBJECTS))

.PHONY: all clean info 
