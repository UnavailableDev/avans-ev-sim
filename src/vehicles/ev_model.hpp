#pragma once

#include "vehicle_model.hpp"

#include <string>

namespace vehicles {

class EVModel : public VehicleModel {
 public:
  EVModel();
  EVModel(const std::string& name, double battery_capacity_kwh, double usage_Wh_per_km, int distribution)
      : VehicleModel(name),
        batteryCapacity_kWh_(battery_capacity_kwh),
        usage_Wh_km_(usage_Wh_per_km),
        distribution_(distribution) {
  }
  // ~EVModel() override = default;

  double GetBatteryCapacity_kWh() const { return batteryCapacity_kWh_; }
  double GetUsage_Wh_km() const { return usage_Wh_km_; }
  int GetDistribution() const { return distribution_; }

 private:
  double batteryCapacity_kWh_;
  double usage_Wh_km_;
  int distribution_;
};

}  // namespace vehicles
