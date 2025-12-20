#include "highway.hpp"

namespace world {

Highway::Highway() {}

void Highway::AddTrafficFlow(std::shared_ptr<TrafficFlow> flow) {
  flows_.push_back(flow);
}

const std::vector<std::shared_ptr<TrafficFlow>>& Highway::GetTrafficFlows() const {
  return flows_;
}

}  // namespace world