#pragma once

#include "simulation/simulation_actor.hpp"

#include <vector>
#include <memory>
#include <string>

#include "station.hpp"

namespace world {

enum class Direction {
  NORTH_TO_SOUTH,
  SOUTH_TO_NORTH,
};

class TrafficFlow : public simulation::SimulationActor {
 public:
  TrafficFlow(Direction direction, int vehicles_per_hour)
      : direction_(direction), vehiclesPerHour_(vehicles_per_hour) {}

  void AddStation(std::shared_ptr<Station> station);
  const std::vector<std::shared_ptr<Station>>& GetStations() const;

  Direction GetDirection() const { return direction_; }
  int GetVehiclesPerHour() const { return vehiclesPerHour_; }

 protected:
  void Act() override;

 private:
  Direction direction_;
  int vehiclesPerHour_;
  std::vector<std::shared_ptr<Station>> stations_;
};

}  // namespace world
