#pragma once

#include <string>

#include "simulation/simulation_actor.hpp"

namespace world {

enum class Direction {
  NORTH_TO_SOUTH,
  SOUTH_TO_NORTH,
};

class TrafficFlow : public simulation::SimulationActor {
 public:
  TrafficFlow(Direction direction, int vehicles_per_hour)
      : direction_(direction), vehiclesPerHour_(vehicles_per_hour) {}

  Direction GetDirection() const { return direction_; }
  int GetVehiclesPerHour() const { return vehiclesPerHour_; }

 protected:
  void Run() override;

 private:
  Direction direction_;
  int vehiclesPerHour_;
};

}  // namespace world
