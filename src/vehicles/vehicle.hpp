#pragma once

#include "simulation/simulation_actor.hpp"

namespace vehicles {

class Vehicle : public simulation::SimulationActor {
 public:
  virtual ~Vehicle() = default;
  virtual void Move() = 0;

 protected:
  double position_km_{0};
  // double destination_km_{0};
};

}  // namespace vehicles
