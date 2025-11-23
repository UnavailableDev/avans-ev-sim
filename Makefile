CXX := g++-15
CXXFLAGS := -std=gnu++20 -Wall -Wextra -Wpedantic -I./src
CXXFLAGS += -isysroot "$(shell xcrun --show-sdk-path)"

# CXXFLAGS += -g
# CXXFLAGS += -std=c++20

SRC := \
	src/main.cpp \
	src/simulation/simulation_manager.cpp \
	src/simulation/simulation_actor.cpp \
	src/simulation/statistics.cpp \
	src/world/highway.cpp \
	src/world/traffic_flow.cpp \
	src/world/station.cpp \
	src/world/charging_station.cpp \
	src/vehicles/vehicle.cpp \
	src/vehicles/ev.cpp \
	src/vehicles/vehicle_model.cpp \
	src/vehicles/ev_model.cpp

OBJ := $(SRC:.cpp=.o)

TARGET := simulation.out

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
