#pragma once

#include "simulation/simulation_actor.hpp"

namespace vehicles {

class Vehicle : public simulation::SimulationActor {
 public:
  virtual ~Vehicle() = default;
  virtual void Move(int distance_km) = 0;

 protected:
  void Act() override;

 protected:
  double position_km_{0};
  // double destination_km_{0};
};

}  // namespace vehicles
