CXX = g++

COMMON_FLAGS = -Wall -std=c++20 -Iinclude

DEBUG_FLAGS = -g -O0 -march=native 
RELEASE_FLAGS = -O3 -DNDEBUG -march=native -flto

TARGET_DIR = build
TARGET = $(TARGET_DIR)/main

SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst src/%.cpp,$(TARGET_DIR)/%.o,$(SRCS))
DEPENDS = $(OBJS:.o=.d)

CFLAGS := $(shell pkg-config --cflags sdl2)
LIBS := $(shell pkg-config --libs sdl2)

ifdef RELEASE
	CXXFLAGS = $(COMMON_FLAGS) $(RELEASE_FLAGS)
else
	CXXFLAGS = $(COMMON_FLAGS) $(DEBUG_FLAGS)
endif

all: $(TARGET)

-include $(DEPENDS)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

$(TARGET_DIR)/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS) $(DEPENDS)