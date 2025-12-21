#pragma once

#include "vehicle.hpp"
#include "ev_model.hpp"

// #include <atomic>
#include <memory>

#define MIN_INITIAL_SOC 0.1

namespace vehicles {

class EV : public Vehicle {
 private:
  static double RandomSOC(){
    return (static_cast<double>(rand())/ static_cast<double>(RAND_MAX))
           * (1.0-MIN_INITIAL_SOC) + MIN_INITIAL_SOC;
  };

 public:
  // explicit EV(EVModel model);
  EV(int id, const EVModel& model, double start_position_km = 0.0, double soc = RandomSOC())
    : Vehicle(id, start_position_km), model_(model), soc_(soc) {}

  // Overload to accept shared_ptr<EVModel>
  EV(int id, const std::shared_ptr<EVModel>& model_ptr, double start_position_km = 0.0, double soc = RandomSOC())
    : Vehicle(id, start_position_km), model_(*model_ptr), soc_(soc) {}
  ~EV() override = default;

  const EVModel& GetModel() const { return model_; }
  double GetStateOfCharge() const { return soc_; }

//  protected:
  void Move(double distance_km) override;
  void PrintInfo() const override;

 private:
  EVModel model_;
  double soc_{1.0}; // state of charge 0.0 - 1.0
  // std::atomic<bool> active_{false};
};

}  // namespace vehicles
