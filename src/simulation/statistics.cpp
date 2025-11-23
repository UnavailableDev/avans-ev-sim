#include "statistics.hpp"

namespace simulation {

void Statistics::RecordChargingSession(const std::string& station_name) {
  ++total_charging_sessions_;
  ++station_sessions_[station_name];
}

}  // namespace simulation
