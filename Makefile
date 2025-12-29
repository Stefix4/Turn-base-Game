# ===========================
# Output formatting
# ===========================

LINE      := ----------------------------------------------------------------
DOUBLE    := ================================================================
EMPTY     :=


define banner_line
	@echo
	@echo " $(1) "
	@echo $(LINE)
	@echo
endef

define banner_double
	@echo
	@echo " $(1) "
	@echo $(DOUBLE)
	@echo
endef

define clean_success
	@echo
	@printf '%s\n' '#####################  CLEAN COMPLETED  ########################'
	@echo
endef

define clean_error
	@echo
	@echo "!!!!!!!!!!!!!!!! CLEAN FAILED !!!!!!!!!!!!!!!!"
	@echo
endef

define run_success
	@echo
	@printf '%s\n' '#####################  RUN COMPLETED  ##########################'
	@echo
endef

define run_error
	@echo
	@echo "!!!!!!!!!!!!!!!!!!!!!!!!! RUN FAILED !!!!!!!!!!!!!!!!!!!!!!!!!!!"
	@echo
endef

define build_success
	@echo
	@printf '%s\n' '######################  BUILD COMPLETED  #######################'
	@echo
endef
define build_error
	@echo
	@echo "!!!!!!!!!!!!!!!!!!!!!!!!  BUILD FAILED  !!!!!!!!!!!!!!!!!!!!!!!!"
	@echo
endef

define build_hint
	@echo
	@echo "👉 Run using the command: make run"
	@echo
endef

define help_banner
	$(call banner_double,                        Help Menu                             )
	@echo "Usage: make [target]"
	@echo ""
	@echo "Common targets:"
	@echo "  all (default)    Build the project for the current OS"
	@echo "  run              Build and run the game"
	@echo "  check-raylib     Verify raylib availability"
	@echo "                   (warns if bundled lib is a Windows build)"
	@echo "  clean            Remove build artifacts"
	@echo "  help             Show this help"
	$(call banner_double)
endef

define run_blocked
	@echo
	@echo "!!!!!!!!!!!!!!!!!!!!!!!!! RUN BLOCKED !!!!!!!!!!!!!!!!!!!!!!!!!!"
	awk '\
		BEGIN { e=0; w=0; f=0 } \
		/^ERROR:/   { e++ } \
		/^WARNING:/ { w++ } \
		/^FATAL:/   { f++ } \
		END { \
			width=64; \
			msg=sprintf("Errors: %d    Warnings: %d    Fatals: %d", e, w, f); \
			pad=int((width - length(msg)) / 2); \
			printf "\n%*s%s\n\n", pad, "", msg; \
		} \
	' $(RUN_ERROR_LOG)
	@echo "Last run failed and build/ already exists."
	@echo "Please fix the errors above before running again."
	@echo
	@echo "To view the errors/fatals/warnings, enter the logs directory and access the build_errors.log file."
	@echo
	@echo "To clear the build and try again, run:"
	@echo "  👉  make debug"
	@echo
	@echo "Alternatively(not recommended), to ignore previous errors and run anyway, delete the file:"
	@echo "  👉  rm -f $(RUN_GUARD) && make run"
	@echo
	@echo "Note - Ignoring previous errors may lead to unexpected behavior. It's recommended to address the errors first."
	@echo "     - Check the READNE.md file for troubleshooting tips."
	@echo
endef


define log_cmd
	@echo ">>> Running: $(1)" >> $(BUILD_LOG)
	@$(1) >> $(BUILD_LOG) 2>> $(ERROR_LOG)
endef


# ===========================
# Phony targets 
# ===========================

.PHONY: clean-success clean-error run-success run-error build-success build-error build-hint help-banner run-blocked

clean-success:
	$(call clean_success)

clean-error:
	$(call clean_error)

run-success:
	$(call run_success)

run-error:
	$(call run_error)

run-blocked:
	$(call run_blocked)

build-success:
	$(call build_success)

build-error:
	$(call build_error)

build-hint:
	$(call build_hint)

help-banner:
	$(call help_banner)


# ===========================


.PHONY: all clean help run check-raylib
.DEFAULT_GOAL := all

# ===========================
# Config
# ===========================

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
      src/functions.cpp \
	  src/characters.cpp \
	  src/menu.cpp \
	  src/map.cpp \

# ===========================
# Log files
# ===========================

LOG_DIR := logs
BUILD_LOG := $(LOG_DIR)/build.log
ERROR_LOG := $(LOG_DIR)/build_errors.log
MAP_LOG := $(LOG_DIR)/map.log
MONSTER_MAP_LOG := $(LOG_DIR)/monster_map.log
RUN_GUARD := build/$(PLAT)/.run_guard
RUN_ERROR_LOG := $(LOG_DIR)/run_errors.tmp


.PHONY: logs
logs:
	@mkdir -p $(LOG_DIR)
	@touch $(BUILD_LOG)
	@touch $(ERROR_LOG)
	@touch $(MAP_LOG)
	@touch $(MONSTER_MAP_LOG)

.PHONY: rotate-logs
rotate-logs:
	@mkdir -p $(LOG_DIR)
	@ts=$$(date +"%Y%m%d_%H%M%S"); \
	if [ -f $(BUILD_LOG) ]; then mv $(BUILD_LOG) $(LOG_DIR)/build_$$ts.log; fi; \
	if [ -f $(ERROR_LOG) ]; then mv $(ERROR_LOG) $(LOG_DIR)/errors_$$ts.log; fi; \
	touch $(BUILD_LOG) $(ERROR_LOG)

# ===========================
# OS detection
# ===========================

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
	PALT = build/windows:$(PATH)
	LDFLAGS = -Llib/ -lraylib -lopengl32 -lgdi32 -lwinmm
	# Use mkdir -p so creating an existing directory won't fail (works in MSYS/Cygwin)
	MKDIR_P = mkdir -p
	RM = rm -rf
else
	TARGET = build/linux/Game
	PALT = build/linux:$(PATH)
	# Default to bundled libraylib in lib/; if system raylib is present, we'll use pkg-config at link time
	LDFLAGS = -Llib/ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
	MKDIR_P = mkdir -p
	RM = rm -rf
endif

# Diagnostic target to inspect raylib availability and warn about Windows builds
check-raylib:
	@echo ""
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

# ===========================
# Guard target
# ===========================

.PHONY: guard-run
guard-run:
	@if [ -f $(RUN_GUARD) ]; then \
		$(MAKE) -s run-blocked; \
		exit 1; \
	fi
	@mkdir -p $(dir $(RUN_GUARD))
	@touch $(RUN_GUARD)


.PHONY: ensure-logs
ensure-logs:
	$(logs)
	@echo "Ensuring logs directory exists..."
	@if [ ! -d $(LOG_DIR) ]; then \
		echo ">>> Creating logs directory"; \
		$(MAKE) -s logs; \
	else \
		echo ">>> Logs directory already exists, skipping logs"; \
	fi

.PHONY: ensure-built
ensure-built:
	@echo ""
ifeq ($(WINDOWS),1)
	@echo "Ensuring Windows build exists..."
	@if [ ! -f $(TARGET) ]; then \
		echo ">>> Build not found, building..."; \
		$(MAKE) -s $(TARGET); \
	else \
		echo ">>> Build found, skipping build"; \
	fi
else
	@echo "Ensuring Linux build exists..."
	@if [ ! -f $(TARGET) ]; then \
		echo ">>> Build not found, building..."; \
		$(MAKE) -s $(TARGET); \
	else \
		echo ">>> Build found, skipping build"; \
	fi
endif
.PHONY: ensure-libs
ensure-libs:
	@$(MAKE) -s backup-windows-libs

.PHONY: run-exec
run-exec:
	@echo "Running $(TARGET) ..."
	@> $(RUN_ERROR_LOG)
ifeq ($(WINDOWS),1)
	@$(TARGET) 2>&1 | awk '\
	/^FATAL:/   { print >> "$(RUN_ERROR_LOG)"; next } \
	/^ERROR:/   { print >> "$(RUN_ERROR_LOG)"; next } \
	/^WARNING:/ { print >> "$(RUN_ERROR_LOG)"; next } \
	{ print >> "$(BUILD_LOG)" }'
else
	@LD_LIBRARY_PATH=lib:$$LD_LIBRARY_PATH ./$(TARGET) 2>&1 | awk '\
	/^FATAL:/   { print >> "$(RUN_ERROR_LOG)"; next } \
	/^ERROR:/   { print >> "$(RUN_ERROR_LOG)"; next } \
	/^WARNING:/ { print >> "$(RUN_ERROR_LOG)"; next } \
	{ print >> "$(BUILD_LOG)" }'
endif



all:
ifeq ($(WINDOWS),1)
	$(call banner_double,                        Windows Build                         )
	@$(MAKE) -s ensure-logs && \
	$(MAKE) -s ensure-built && \
	$(MAKE) -s build-success && \
	$(MAKE) -s build-hint || \
	$(MAKE) -s build-error
else
	$(call banner_double,                        Linux Build                           )
	@$(MAKE) -s ensure-logs && \
	$(MAKE) -s ensure-libs && \
	$(MAKE) -s ensure-built && \
	$(MAKE) -s build-success && \
	$(MAKE) -s build-hint || \
	$(MAKE) -s build-error
endif


$(TARGET): $(OBJ)
ifeq ($(WINDOWS),1)
	$(call log_cmd,$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET) $(LDFLAGS))
else
	@sh -c '\
	if [ "$(USE_SYSTEM_RAYLIB)" = "1" ]; then \
		CFLAGS="$$(pkg-config --cflags raylib 2>/dev/null)"; \
		LIBS="$$(pkg-config --libs raylib 2>/dev/null)"; \
		echo " "\
		# echo ">>> Running: $(CXX) $(CXXFLAGS) $$CFLAGS $(OBJ) -o $(TARGET) $$LIBS" >> $(BUILD_LOG); \
		$(CXX) $(CXXFLAGS) $$CFLAGS $(OBJ) -o $(TARGET) $$LIBS >> $(BUILD_LOG) 2>> $(ERROR_LOG); \
	else \
		$(MAKE) -s check-windows-libs || exit 1; \
		echo " "\
		# echo ">>> Running: $(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET) $(LDFLAGS)" >> $(BUILD_LOG); \
		$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET) $(LDFLAGS) >> $(BUILD_LOG) 2>> $(ERROR_LOG); \
	fi'
endif


.PHONY: backup-windows-libs
backup-windows-libs:
	@echo ""
	@echo "Checking if there are Windows-built libraries in lib/ to back up..."
	@if [ -d lib ] && [ "$$(ls -A lib 2>/dev/null)" ] && [ ! -d backup_windows ]; then \
		echo ">>> Backing up the following files:"; \
		echo "lib"; \
		set -- lib/*; \
		count=$$#; \
		i=1; \
		for f in "$$@"; do \
			name=$$(basename "$$f"); \
			if [ "$$count" -eq 1 ]; then \
				echo " └─$$name"; \
			elif [ "$$i" -eq "$$count" ]; then \
				echo " └─$$name"; \
			else \
				echo " ├─$$name"; \
			fi; \
			i=$$((i+1)); \
		done; \
		mkdir -p backup_windows; \
		mv lib/* backup_windows/; \
		echo ">>> Backup complete"; \
	else \
		echo ">>> Library backup already handled or not needed"; \
	fi


# ===========================
# Compile pattern rule
# ===========================

build/$(PLAT)/%.o: src/%.cpp
	@if [ ! -d build ]; then \
		$(MKDIR_P) $(dir $@); \
	fi
	@echo ">>> Compiling $< ..."
	@$(CXX) $(CXXFLAGS) -c $< -o $@ >> $(BUILD_LOG) 2>> $(ERROR_LOG)

.PHONY: run
run:
ifeq ($(WINDOWS),1)
	$(call banner_double,                          Windows Run                         )
	@$(MAKE) -s ensure-logs && \
	$(MAKE) -s rotate-logs && \
	set -e; \
	if ! $(MAKE) -s ensure-built; then \
		$(MAKE) -s run-error; \
		exit 1; \
	fi; \
	if ! $(MAKE) -s guard-run; then \
		$(MAKE) -s run-error; \
		exit 1; \
	fi; \
	if ! $(MAKE) -s run-exec; then \
		$(MAKE) -s run-error; \
		exit 1; \
	fi
	@awk '\
		BEGIN { e=0; w=0; f=0 } \
		/^ERROR:/   { e++ } \
		/^WARNING:/ { w++ } \
		/^FATAL:/   { f++ } \
		END { exit (e > 0 || f > 0) } \
	' $(RUN_ERROR_LOG); rc=$$?; \
	if [ $$rc -eq 0 ]; then \
		$(MAKE) -s run-success; \
		awk '\
			BEGIN { e=0; w=0; f=0 } \
			/^ERROR:/   { e++ } \
			/^WARNING:/ { w++ } \
			/^FATAL:/   { f++ } \
			END { \
				width=64; \
				msg=sprintf("Errors: %d    Warnings: %d    Fatals: %d", e, w, f); \
				pad=int((width - length(msg)) / 2); \
				printf "%*s%s\n\n", pad, "", msg; \
			} \
		' $(RUN_ERROR_LOG); \
		rm -f $(RUN_GUARD); \
	else \
		$(MAKE) -s run-error; \
		awk '\
			BEGIN { e=0; w=0; f=0 } \
			/^ERROR:/   { e++ } \
			/^WARNING:/ { w++ } \
			/^FATAL:/   { f++ } \
			END { \
				width=64; \
				msg=sprintf("Errors: %d    Warnings: %d    Fatals: %d", e, w, f); \
				pad=int((width - length(msg)) / 2); \
				printf "%*s%s\n\n", pad, "", msg; \
			} \
		' $(RUN_ERROR_LOG); \
		exit 1; \
	fi
else
	$(call banner_double,                         Linux Run                            )
	@$(MAKE) -s ensure-logs && \
	$(MAKE) -s rotate-logs && \
	$(MAKE) -s ensure-libs && \
	set -e; \
	if ! $(MAKE) -s ensure-built; then \
		$(MAKE) -s run-error; \
		exit 1; \
	fi; \
	if ! $(MAKE) -s guard-run; then \
		$(MAKE) -s run-error; \
		exit 1; \
	fi; \
	if ! $(MAKE) -s run-exec; then \
		$(MAKE) -s run-error; \
		exit 1; \
	fi
	@awk '\
		BEGIN { e=0; w=0; f=0 } \
		/^ERROR:/   { e++ } \
		/^WARNING:/ { w++ } \
		/^FATAL:/   { f++ } \
		END { exit (e > 0 || f > 0) } \
	' $(RUN_ERROR_LOG); rc=$$?; \
	if [ ! $$rc -eq 0 ]; then \
		if grep -q '^ERROR:\|^FATAL:' $(RUN_ERROR_LOG); then \
		$(MAKE) -s run-error; \
		awk '\
			BEGIN { e=0; w=0; f=0 } \
			/^ERROR:/   { e++ } \
			/^WARNING:/ { w++ } \
			/^FATAL:/   { f++ } \
			END { \
				width=64; \
				msg=sprintf("Errors: %d    Warnings: %d    Fatals: %d", e, w, f); \
				pad=int((width - length(msg)) / 2); \
				printf "%*s%s\n\n", pad, "", msg; \
			} \
		' $(RUN_ERROR_LOG); \
		exit 1; \
		fi; \
	else \
		$(MAKE) -s run-success; \
		rm -f $(RUN_GUARD); \
		awk '\
			BEGIN { e=0; w=0; f=0 } \
			/^ERROR:/   { e++ } \
			/^WARNING:/ { w++ } \
			/^FATAL:/   { f++ } \
			END { \
				width=64; \
				msg=sprintf("Errors: %d    Warnings: %d    Fatals: %d", e, w, f); \
				pad=int((width - length(msg)) / 2); \
				printf "%*s%s\n\n", pad, "", msg; \
			} \
		' $(RUN_ERROR_LOG); \
		rm -f $(RUN_GUARD); \
	fi
endif

clean:
ifeq ($(WINDOWS),0)
	$(call banner_double,                        Linux clean                           )
	@if [ -d backup_windows ]; then \
		if [ "$$(ls -A backup_windows 2>/dev/null)" ]; then \
			echo "Restoring backup_windows -> lib"; \
			echo ">>> Moving files from backup_windows/ to lib/"; \
			mkdir -p lib; \
			mv backup_windows/* lib/; \
			rm -rf backup_windows; \
			echo "Restoration complete"; \
			echo ""; \
		else \
			echo "backup_windows/ is empty, removing directory"; \
			rm -rf backup_windows; \
			echo "Removed backup_windows/ directory"; \
		fi; \
	else \
		echo "backup_windows/ directory does not exist, nothing to restore"; \
	fi
	@if [ -d build ]; then \
		echo "Removing build/ directory"; \
		rm -rf build; \
		echo ">>> Removed build/ directory"; \
	else \
		echo ""; \
		echo ">>> build/ directory does not exist, nothing to clean"; \
	fi
	@echo ""
	@if [ -d $(LOG_DIR) ] && [ "$$(ls -A $(LOG_DIR) 2>/dev/null)" ]; then \
		echo "Removing logs/"; \
		rm -rf $(LOG_DIR); \
		echo ">>> Removed logs/ directory"; \
	else \
		echo ">>> logs/ directory does not exist, nothing to clean"; \
	fi
endif
ifeq ($(WINDOWS),1)
	$(call banner_double,                        Windows clean                        );
	@if [ -d build ]; then \
		echo "Removing build/ directory"; \
		rm -rf build; \
		echo ">>> Removed build/ directory"; \
	else \
		echo ""; \
		echo ">>> build/ directory does not exist, nothing to clean"; \
	fi
	@echo ""
	@if [ -d $(LOG_DIR) ] && [ "$$(ls -A $(LOG_DIR) 2>/dev/null)" ]; then \
		echo "Removing logs/"; \
		rm -rf $(LOG_DIR); \
		echo ">>> Removed logs/ directory"; \
	else \
		echo ">>> logs/ directory does not exist, nothing to clean"; \
	fi
endif
	@# Verification
	@if [ ! -d build ] && [ ! -d $(LOG_DIR) ]; then \
	echo ""; \
	echo "Clean successful"; \
	$(MAKE) -s clean-success; \
else \
	echo "Some directories could not be removed!"; \
	$(MAKE) -s clean-error; \
	exit 1; \
fi

.PHONY: debug
debug: clean run

help:
	@$(MAKE) -s help-banner
