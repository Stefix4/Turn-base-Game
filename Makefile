.PHONY: all clean help run

# Compiler and flags
# CXX: compiler command. Change if you prefer clang++ or a different compiler.
# CXXFLAGS: common compilation flags and include directories
CXX = g++
CXXFLAGS = -O2 -Wall -std=c++17 -I include

SRC = src/game.cpp \
      src/map.cpp \
      src/characters.cpp \
      src/functions.cpp \
      src/menu.cpp

# Detect OS in a robust way (Windows_NT, MINGW, MSYS, CYGWIN, Linux)
UNAME_S := $(shell uname -s 2>/dev/null)
WINDOWS := 0
ifeq ($(OS),Windows_NT)
	WINDOWS := 1
endif
ifneq (,$(findstring MINGW,$(UNAME_S)))
	WINDOWS := 1
endif
ifneq (,$(findstring MSYS,$(UNAME_S)))
	WINDOWS := 1
endif
ifneq (,$(findstring CYGWIN,$(UNAME_S)))
	WINDOWS := 1
endif

ifeq ($(WINDOWS),1)
	TARGET = build/windows/Game.exe
	LDFLAGS = -Llib/ -lraylib -lopengl32 -lgdi32 -lwinmm
	# Use mkdir -p so creating an existing directory won't fail (works in MSYS/Cygwin)
	MKDIR_P = mkdir -p
	RM = rm -rf
else
	TARGET = build/linux/Game
	LDFLAGS = -Llib/ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
	MKDIR_P = mkdir -p
	RM = rm -rf
endif

# Platform directory name (used for object output)
PLAT := $(if $(filter 1,$(WINDOWS)),windows,linux)
# Build object files into build/$(PLAT)/
OBJ := $(patsubst src/%.cpp, build/$(PLAT)/%.o, $(SRC))

all: $(TARGET)

$(TARGET): $(OBJ)
	@echo "Building for $(if $(filter 1,$(WINDOWS)),Windows,Linux)"
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET) $(LDFLAGS)

# Pattern rule: compile source files into platform-specific build folder
build/$(PLAT)/%.o: src/%.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	@echo "Running $(TARGET)"
	@$(TARGET)
clean:
	$(RM) build

help:
	@echo "Usage: make [target]"
	@echo ""
	@echo "Common targets:"
	@echo "  all (default)    Build the project for the current OS"
	@echo "  run              Build and run the game"
	@echo "  clean            Remove build artifacts"
	@echo "  help             Show this help"
