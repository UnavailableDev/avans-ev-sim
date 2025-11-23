#pragma once

#include "vehicle.hpp"
#include "simulation/simulation_actor.hpp"
#include "ev_model.hpp"

namespace vehicles {

class EV : public Vehicle, public simulation::SimulationActor {
 public:
  explicit EV(EVModel model);

 protected:
  void Run() override;
  void Move() override;

 private:
  EVModel model_;
  double soc_{1.0};
};

}  // namespace vehicles
