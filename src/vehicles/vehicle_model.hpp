#pragma once

#include <string>

namespace vehicles {

class VehicleModel {
 public:
  virtual ~VehicleModel() = default;

  const std::string& GetName() const { return name_; }
 protected:
  std::string name_;
};

}  // namespace vehicles
