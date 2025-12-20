#pragma once

#include <vector>
#include <memory>

#include "world/station.hpp"
#include "world/traffic_flow.hpp"

namespace world {

class Station;
class TrafficFlow;

class Highway {
 public:
  Highway() = default;
  Highway(double length_km, double speed_kmh)
    : length_km_(length_km), speed_kmh_(speed_kmh) {}
  ~Highway() = default;

  double GetLength() const { return length_km_; }

  void SetSpeedLimit(double speed_kmh) { speed_kmh_ = speed_kmh; }
  double GetSpeedLimit() const { return speed_kmh_; }

  void AddTrafficFlow(std::shared_ptr<TrafficFlow> flow);
  const std::vector<std::shared_ptr<TrafficFlow>>& GetTrafficFlows() const;
 
 private:
  double length_km_{0};
  double speed_kmh_{0};

  std::vector<std::shared_ptr<TrafficFlow>> flows_;
};

}  // namespace world
