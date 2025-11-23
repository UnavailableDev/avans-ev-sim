#pragma once

#include <string>

namespace world {

class Station {
 public:
  virtual ~Station() = default;
  virtual void HandleArrival() = 0;

 protected:
  std::string name_;
  double position_km_{0};
};

}  // namespace world
