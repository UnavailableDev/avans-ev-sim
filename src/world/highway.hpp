#pragma once

#include <vector>
#include <memory>

namespace world {

class Station;
class TrafficFlow;

class Highway {
 public:
  Highway();
 
 private:
  double length_km_{0};
  double speed_kmh_{0};
  std::vector<std::shared_ptr<Station>> stations_;
  std::vector<std::shared_ptr<TrafficFlow>> flows_;
};

}  // namespace world
