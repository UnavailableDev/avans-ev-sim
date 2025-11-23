#pragma once

#include "vehicle_model.hpp"

namespace vehicles {

class EVModel : public VehicleModel {
 public:
  EVModel();

 private:
  double battery_capacity_kwh_{0};
  double usage_kwh_per_km_{0};
};

}  // namespace vehicles
