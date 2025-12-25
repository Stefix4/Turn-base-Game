.PHONY: all clean help run check-raylib
.DEFAULT_GOAL := all

# Compiler and flags
# CXX: compiler command. Change if you prefer clang++ or a different compiler.
# CXXFLAGS: common compilation flags and include directories
CXX = g++
CXXFLAGS = -O2 -Wall -std=c++17 -I include

# By default do NOT probe for system raylib. Set to 1 on the command line to opt-in
# Example: `make USE_SYSTEM_RAYLIB=1` will use pkg-config to find system raylib
USE_SYSTEM_RAYLIB ?= 0
# Ignore any exported USE_SYSTEM_RAYLIB from the shell environment so plain `make` won't probe pkg-config
unexport USE_SYSTEM_RAYLIB
# You can still opt-in on the make command line: `make USE_SYSTEM_RAYLIB=1`

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

# Defer checking for system raylib until link time. Use bundled lib by default for Linux.
ifeq ($(WINDOWS),1)
	TARGET = build/windows/Game.exe
	LDFLAGS = -Llib/ -lraylib -lopengl32 -lgdi32 -lwinmm
	# Use mkdir -p so creating an existing directory won't fail (works in MSYS/Cygwin)
	MKDIR_P = mkdir -p
	RM = rm -rf
else
	TARGET = build/linux/Game
	# Default to bundled libraylib in lib/; if system raylib is present, we'll use pkg-config at link time
	LDFLAGS = -Llib/ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
	MKDIR_P = mkdir -p
	RM = rm -rf
endif

# Diagnostic target to inspect raylib availability and warn about Windows builds
check-raylib:
	@echo "Checking for raylib..."
	@if command -v pkg-config >/dev/null 2>&1 && pkg-config --exists raylib ; then \
		echo "Using system raylib: $$(pkg-config --modversion raylib)"; \
		pkg-config --cflags --libs raylib; \
	elif [ -f lib/libraylib.a ] || [ -f lib/libraylib.so ]; then \
		echo "Using bundled library in lib/"; file lib/*raylib* 2>/dev/null || true; \
		if file lib/libraylib.a 2>/dev/null | grep -Ei 'pe32|ms windows|minGW|win32' >/dev/null 2>&1; then \
			echo 'Warning: bundled libraylib appears to be a Windows (MinGW) build and will not link on Linux.'; \
		fi; \
	else \
		echo 'No raylib found. Install system raylib (e.g. on Debian/Ubuntu: sudo apt install libraylib-dev) or add a Linux build into lib/'; exit 1; \
	fi

# Guard target: detect Windows-built libraylib and show a clear error (used by the linker recipe)
.PHONY: check-windows-libs
check-windows-libs:
	@sh -c 'if [ -f lib/libraylib.a ] && strings lib/libraylib.a 2>/dev/null | grep -Ei "MZ|__imp_|__mingw" -m1 >/dev/null 2>&1; then printf "\nERROR: bundled lib/libraylib.a appears to contain Windows (MinGW/PE) objects and cannot be linked on Linux.\n\nFixes:\n  1) Install and use system raylib: sudo apt install libraylib-dev && make USE_SYSTEM_RAYLIB=1\n  2) Remove or move Windows-built files from lib/: mkdir -p backup_windows && mv lib/* backup_windows\n\nRun \"make check-raylib\" for more diagnostics.\n"; exit 1; fi'

# Platform directory name (used for object output)
PLAT := $(if $(filter 1,$(WINDOWS)),windows,linux)
# Build object files into build/$(PLAT)/
OBJ := $(patsubst src/%.cpp, build/$(PLAT)/%.o, $(SRC))

all: $(TARGET)

$(TARGET): $(if $(filter 0,$(WINDOWS)),backup-windows-libs) $(OBJ)
	@echo "Building for $(if $(filter 1,$(WINDOWS)),Windows,Linux) (USE_SYSTEM_RAYLIB=$(USE_SYSTEM_RAYLIB))"
ifeq ($(WINDOWS),1)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET) $(LDFLAGS)
else
	@# Use system raylib only if explicitly requested via USE_SYSTEM_RAYLIB=1
	@if [ "$(USE_SYSTEM_RAYLIB)" = "1" ]; then \
		echo "Using system raylib (pkg-config)"; \
		CFLAGS="$$(pkg-config --cflags raylib 2>/dev/null)"; \
		LIBS="$$(pkg-config --libs raylib 2>/dev/null)"; \
		if [ -z "$${LIBS}" ]; then \
			echo "pkg-config did not return raylib libs or pkg-config not installed"; exit 1; \
		fi; \
		$(CXX) $(CXXFLAGS) $${CFLAGS} $(OBJ) -o $(TARGET) $${LIBS}; \
	else \
		echo "Using bundled libraylib in lib/ (to use system raylib: make USE_SYSTEM_RAYLIB=1)"; \
		$(MAKE) -s check-windows-libs || exit 1; \
		$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET) $(LDFLAGS); \
	fi
endif

.PHONY: backup-windows-libs
backup-windows-libs:
	@echo "Building for $(if $(filter 1,$(WINDOWS)),Windows,Linux) (USE_SYSTEM_RAYLIB=$(USE_SYSTEM_RAYLIB))"
	@mkdir -p backup_windows
	@sh -c 'if [ -d lib ] && [ "$$(ls -A lib 2>/dev/null)" ]; then \
		echo ">>> Moving files from lib/ to backup_windows/"; \
		mv lib/* backup_windows/; \
	else \
		echo ">>> lib/ is empty, nothing to move"; \
	fi'


# Pattern rule: compile source files into platform-specific build folder
build/$(PLAT)/%.o: src/%.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	@echo "Running $(TARGET)"
ifeq ($(WINDOWS),1)
	@$(TARGET)
else
	@LD_LIBRARY_PATH=lib:$$LD_LIBRARY_PATH ./$(TARGET) || \
	 (echo "Failed to start $(TARGET). Showing shared library info:" && ldd $(TARGET))
endif

clean:
ifeq ($(WINDOWS),0)
	@echo "Linux clean: restoring backup_windows -> lib"
	@sh -c 'if [ -d backup_windows ] && [ "$$(ls -A backup_windows 2>/dev/null)" ]; then \
		echo ">>> Moving files from backup_windows/ to lib/"; \
		mkdir -p lib; \
		mv backup_windows/* lib/; \
		rm -rf backup_windows; \
	else \
		echo ">>> backup_windows/ is empty or missing, nothing to restore"; \
	fi'

endif
	@$(RM) build


help:
	@echo "Usage: make [target]"
	@echo ""
	@echo "Common targets:"
	@echo "  all (default)    Build the project for the current OS"
	@echo "  run              Build and run the game"
	@echo "  check-raylib     Verify raylib availability & warn if bundled lib is a Windows build"
	@echo "  clean            Remove build artifacts"
	@echo "  help             Show this help"

