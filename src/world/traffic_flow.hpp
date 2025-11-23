#pragma once

#include "simulation/simulation_actor.hpp"

namespace world {

class TrafficFlow : public simulation::SimulationActor {
 protected:
  void Run() override;
};

}  // namespace world
