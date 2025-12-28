#pragma once

#include <string>
#include <memory>
#include "world/fuel_type.hpp"

namespace vehicles { class Vehicle; }

namespace world {

class Station {
 public:
  virtual ~Station() = default;
  // Accept vehicle by shared_ptr to avoid slicing / abstract-type-by-value
  virtual void HandleArrival(std::shared_ptr<vehicles::Vehicle> v) = 0;

  const std::string& GetName() const { return name_; }
  double GetPosition() const { return position_km_; }

 protected:
  Station() = default;
  Station(const std::string& name, double position_km)
      : name_(name), position_km_(position_km) {}

 protected:
  std::string name_;
  double position_km_{0};
  FuelType fuelType_{FuelType::kCombustion};
};

}  // namespace world
