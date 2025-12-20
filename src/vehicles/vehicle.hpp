#pragma once

#include "vehicle_model.hpp"
// #include "simulation/simulation_actor.hpp"

namespace vehicles {

class Vehicle {
// class Vehicle : public simulation::SimulationActor {
 public:
  virtual ~Vehicle() = default;
  virtual void Move(int distance_km) = 0;
  int GetID() const { return id_; }
  double GetPosition_km() const { return position_km_; }

 protected:
  double GetDestination_km() const { return destination_km_; }
//  protected:
//   void Act() override;

 protected:
  int id_{0};
  // VehicleModel model_;
  double position_km_{0};
  double destination_km_{0};
};

}  // namespace vehicles
