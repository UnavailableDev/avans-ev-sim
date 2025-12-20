#pragma once

#include <string>

namespace world {

class Station {
 public:
  virtual ~Station() = default;
  virtual void HandleArrival() = 0;

  const std::string& GetName() const { return name_; }
  double GetPosition() const { return position_km_; }

 protected:
  Station() = default;
  Station(const std::string& name, double position_km)
      : name_(name), position_km_(position_km) {}

  std::string name_;
  double position_km_{0};
};

}  // namespace world
