# cLLM Makefile
# Usage: make [target] [options]
# Options:
#   BUILD_TYPE=Debug|Release (default: Release)
#   ENABLE_TESTS=ON|OFF (default: OFF)
#   ENABLE_LOGGING=ON|OFF (default: ON)
#   CLEAN=1 (clean build directory before building)

# Default values
BUILD_DIR ?= build
BUILD_TYPE ?= Release
ENABLE_TESTS ?= OFF
ENABLE_LOGGING ?= ON
CLEAN ?= 0

# Detect number of CPU cores for parallel builds
NPROC := $(shell nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 1)

# Build flags
CMAKE_FLAGS := -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) \
               -DCLLM_BUILD_TESTS=$(ENABLE_TESTS) \
               -DCLLM_ENABLE_LOGGING=$(ENABLE_LOGGING)

# Parallel build support
ifneq (,$(filter -j%,$(MAKEFLAGS)))
    JOBS := $(patsubst -j%,%,$(filter -j%,$(MAKEFLAGS)))
else
    JOBS := $(NPROC)
endif
BUILD_FLAGS := -j$(JOBS)

# ANSI color codes
GREEN := \033[32m
YELLOW := \033[33m
RED := \033[31m
RESET := \033[0m

# Print functions
print_info = @echo "$(GREEN)$(1)$(RESET)"
print_warn = @echo "$(YELLOW)$(1)$(RESET)"
print_error = @echo "$(RED)$(1)$(RESET)"

# Check if required tools are installed
check_tools:
	@command -v cmake >/dev/null 2>&1 || { $(call print_error,"Error: cmake is required but not installed."); exit 1; }
	@command -v conan >/dev/null 2>&1 || { $(call print_error,"Error: conan is required but not installed."); exit 1; }

# Create build directory
$(BUILD_DIR):
	$(call print_info,"Creating build directory...")
	@mkdir -p $(BUILD_DIR)

# Clean build directory
clean:
	$(call print_info,"Cleaning build directory...")
	@rm -rf $(BUILD_DIR)

# Configure project
configure: check_tools $(BUILD_DIR)
	$(call print_info,"Configuring project...")
	@cd $(BUILD_DIR) && conan install .. --output-folder=. --build=missing
	@cd $(BUILD_DIR) && cmake .. $(CMAKE_FLAGS)

# Build project
build: configure
	$(call print_info,"Building project...")
	@cmake --build $(BUILD_DIR) $(BUILD_FLAGS)

# Install project
install: build
	$(call print_info,"Installing project...")
	@cmake --install $(BUILD_DIR)

# Generate documentation
docs: build
	$(call print_info,"Generating documentation...")
	@cmake --build $(BUILD_DIR) --target docs

# Show build configuration
config:
	$(call print_info,"Build Configuration:")
	@echo "  Build Type:   $(BUILD_TYPE)"
	@echo "  Build Tests:  $(ENABLE_TESTS)"
	@echo "  Logging:      $(ENABLE_LOGGING)"
	@echo "  Build Dir:    $(BUILD_DIR)"
	@echo "  Jobs:         $(JOBS)"

# Show help
help:
	$(call print_info,"cLLM Makefile Usage:")
	@echo "make [target] [options]"
	@echo ""
	@echo "Targets:"
	@echo "  all        Build the project (default)"
	@echo "  build      Configure and build the project"
	@echo "  clean      Remove build directory"
	@echo "  install    Build and install the project"
	@echo "  docs       Generate documentation"
	@echo "  config     Show current build configuration"
	@echo "  help       Show this help message"
	@echo ""
	@echo "Options:"
	@echo "  BUILD_TYPE=Debug|Release    Build type (default: Release)"
	@echo "  ENABLE_TESTS=ON|OFF        Enable tests (default: OFF)"
	@echo "  ENABLE_LOGGING=ON|OFF      Enable logging (default: ON)"
	@echo "  CLEAN=1                    Clean build directory before building"
	@echo ""
	@echo "Examples:"
	@echo "  make                       # Default build"
	@echo "  make BUILD_TYPE=Debug      # Debug build"
	@echo "  make ENABLE_TESTS=ON       # Build with tests"
	@echo "  make clean                 # Clean build directory"

# Default target
all: config
	@if [ "$(CLEAN)" = "1" ]; then \
		$(MAKE) clean; \
	fi
	@$(MAKE) build

.PHONY: all build clean install docs config help check_tools configure