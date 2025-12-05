#pragma once

#include "vehicle.hpp"
#include "simulation/simulation_actor.hpp"
#include "ev_model.hpp"

// #include <atomic>
#include <memory>

#define MIN_INITIAL_SOC 0.1

namespace vehicles {

class EV : public Vehicle, public simulation::SimulationActor {
 private:
  static double RandomSOC(){
    return (static_cast<double>(rand())/ static_cast<double>(RAND_MAX))
           * (1.0-MIN_INITIAL_SOC) + MIN_INITIAL_SOC;
  };
 public:
  // explicit EV(EVModel model);
  EV(int id, const EVModel& model, double start_position_km = 0.0, double soc = RandomSOC())
      : id_(id), model_(model), soc_(soc) {
    position_km_ = start_position_km;
  }
  ~EV() override = default;

  int GetID() const { return id_; }
  const EVModel& GetModel() const { return model_; }
  double GetStateOfCharge() const { return soc_; }

 protected:
  void Run() override;
  void Move() override;

 private:
  int id_;
  EVModel model_;
  double soc_{1.0}; // state of charge 0.0 - 1.0
  // std::atomic<bool> active_{false};
};

}  // namespace vehicles
