#pragma once

#include <string>

namespace vehicles {

class VehicleModel {
 public:
  virtual ~VehicleModel() = default;

 protected:
  std::string name_;
};

}  // namespace vehicles
