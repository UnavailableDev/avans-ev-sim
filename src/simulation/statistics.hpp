#pragma once

#include <string>
#include <unordered_map>

namespace simulation {

class Statistics {
 public:
  void RecordChargingSession(const std::string& station_name);

 private:
  int total_charging_sessions_{0};
  std::unordered_map<std::string, int> station_sessions_;
};

}  // namespace simulation
