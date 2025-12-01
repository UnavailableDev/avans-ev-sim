#include "traffic_flow.hpp"

namespace world {

void TrafficFlow::AddStation(std::shared_ptr<Station> station) {
  stations_.push_back(station);
}
const std::vector<std::shared_ptr<Station>>& TrafficFlow::GetStations() const {
  return stations_;
}

void TrafficFlow::Run() {
  // Placeholder simulation loop
}

}  // namespace world
