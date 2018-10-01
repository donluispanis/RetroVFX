#Makefile for PaintLike Project

# Our .cpp and where to store them
SOURCES:= $(wildcard *.cpp)
_OBJECTS := $(subst .cpp,.o,$(SOURCES))
BIN_DIR := ../bin/
OBJ_DIR := obj/
OBJECTS := $(patsubst %,$(BIN_DIR)$(OBJ_DIR)%,$(_OBJECTS))
NDEBUG := ''
# general compiler settings (might need to be set when compiling the lib, too)
CPPFLAGS += -I./../ -I./../include

ifndef NDEBUG
CXXFLAGS += -g -Wall -std=c++14
else
CXXFLAGS += -O2
endif

all: $(OBJECTS)
	$(warning Compilation done!)

$(BIN_DIR)$(OBJ_DIR)%.o: %.cpp
	$(warning Compiling...)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $^

clean:
	$(warning Cleaned!)
	rm -r $(BIN_DIR)$(OBJ_DIR)
	

info:
		$(info $(SOURCES))
		$(info $(OBJECTS))

.PHONY: all clean info 
