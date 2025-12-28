#pragma once

#include "vehicle_model.hpp"

#include <vector>
#include <memory>

#include "world/fuel_type.hpp"

namespace world { class Station; }

namespace vehicles {

class Vehicle {
 public:
  Vehicle(int id, double position_km = 0.0, double destination_km = 100.0) 
      : id_(id), position_km_(position_km), destination_km_(destination_km) {}
  virtual ~Vehicle() = default;

  virtual void Move(double distance_km) = 0;

  void SetDestination_km(double distance_km) { destination_km_ = distance_km; }

  void SetStations(const std::vector<std::shared_ptr<world::Station>>& stations) {
    routeStations_ = stations;
  }

  void SetSelfPtr(std::shared_ptr<Vehicle> self) {
    self_ptr_ = self;
  }

  int GetID() const { return id_; }
  double GetPosition_km() const { return position_km_; }
  
  virtual void PrintInfo() const;

 protected:
  double GetDestination_km() const { return destination_km_; }

  /// @brief Implement specific vehicle action
  /// @return True if allowed to move, false otherwise
  virtual bool Action(double distance_km) = 0;

 protected:
  int id_{0};
  // VehicleModel model_;
  double position_km_{0};
  double destination_km_{0};
  world::FuelType fuelType_{world::FuelType::kCombustion};
  std::vector<std::shared_ptr<world::Station>> routeStations_{};
  bool atStation_{false};
  std::shared_ptr<Vehicle> self_ptr_{nullptr};  // Shared pointer to self, set by TrafficFlow
};

}  // namespace vehicles
