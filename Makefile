# ============================================================
#   PLATFORM DETECTION (macOS vs Linux/Other)
# ============================================================
UNAME_S := $(shell uname -s)

# Default compiler
CXX := g++

# macOS: use g++-15 + system SDK
ifeq ($(UNAME_S),Darwin)
	CXX := g++-15
	SDK_PATH := $(shell xcrun --show-sdk-path)
	CXXFLAGS += -isysroot "$(SDK_PATH)"
endif

# ============================================================
#   BUILD DIR CONFIGURATION
# ============================================================
BUILD_DIR := build
BIN := simulation.out

# ensure build directory exists
$(shell mkdir -p $(BUILD_DIR))

# ============================================================
#   SOURCE FILES
# ============================================================
SRC := \
	src/main.cpp \
	src/manager.cpp \
	src/simulation/simulation_manager.cpp \
	src/world/highway.cpp \
	src/world/traffic_flow.cpp \
	src/world/station.cpp \
	src/world/charging_station.cpp \
	src/vehicles/vehicle.cpp \
	src/vehicles/ev.cpp \
	src/vehicles/vehicle_model.cpp \
	src/vehicles/ev_model.cpp

# Map source → build directory
OBJ := $(SRC:%.cpp=$(BUILD_DIR)/%.o)
DEP := $(OBJ:.o=.d)

# Create subdirectories inside build/
DIRS := $(sort $(dir $(OBJ)))
$(shell mkdir -p $(DIRS))

# ============================================================
#   PARALLEL COMPILATION (automatic -j)
# ============================================================
# Number of CPU cores
NPROC := $(shell getconf _NPROCESSORS_ONLN 2>/dev/null || sysctl -n hw.ncpu)

# Make automatically runs in parallel
MAKEFLAGS += -j$(NPROC)

# ============================================================
#   DEFAULT COMPILE FLAGS
# ============================================================
CXXFLAGS += -std=gnu++20 -Wall -Wextra -Wpedantic -pthread -I./src -MMD -MP
LDFLAGS := -pthread

# ============================================================
#   DEBUG MODE (make debug)
# ============================================================
ifeq ($(MAKECMDGOALS),debug)
    CXXFLAGS += -g -O0
endif

# ============================================================
#   RELEASE MODE (make release)
# ============================================================
ifeq ($(MAKECMDGOALS),release)
    CXXFLAGS += -O3 -DNDEBUG
endif

# ============================================================
#   DEFAULT TARGET
# ============================================================
all: $(BIN)

# ============================================================
#   LINKING
# ============================================================
$(BIN): $(OBJ)
	@echo "Linking → $@"
	@$(CXX) $(CXXFLAGS) $(OBJ) -o $@ $(LDFLAGS)

# ============================================================
#   COMPILATION
# ============================================================
$(BUILD_DIR)/%.o: %.cpp
	@echo "Compiling → $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# ============================================================
#   CLEAN
# ============================================================
clean:
	@echo "Cleaning..."
	@rm -rf $(BUILD_DIR) $(BIN)

# ============================================================
#   OTHER TARGETS
# ============================================================
debug: $(BIN)
release: clean $(BIN)

# ============================================================
#   DEPENDENCIES
# ============================================================
-include $(DEP)

.PHONY: all clean debug release
