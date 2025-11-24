#pragma once

#include "vehicle.hpp"
#include "simulation/simulation_actor.hpp"
#include "ev_model.hpp"

// #include <atomic>
#include <memory>

namespace vehicles {

class EV : public Vehicle, public simulation::SimulationActor {
 public:
  // explicit EV(EVModel model);
  EV(int id, const EVModel& model, double start_position_km, double soc)
      : model_(model), soc_(1.0) {
    position_km_ = start_position_km;
  }
  ~EV() override = default;

  int GetID() const { return id; }
  const EVModel& GetModel() const { return model_; }
  double GetStateOfCharge() const { return soc_; }

 protected:
  void Run() override;
  void Move() override;

 private:
  int id;
  EVModel model_;
  double soc_{1.0}; // state of charge 0.0 - 1.0
  // std::atomic<bool> active_{false};
};

}  // namespace vehicles
