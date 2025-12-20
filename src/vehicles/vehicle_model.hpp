#pragma once

#include <string>

namespace vehicles {

class VehicleModel {
 public:
  VehicleModel(const std::string& name = "undefined") 
      : name_(name) {}
  virtual ~VehicleModel() = default;

  const std::string& GetName() const { return name_; }
 protected:
  std::string name_;
};

}  // namespace vehicles
