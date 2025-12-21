#include "traffic_flow.hpp"

#include <thread>

namespace world {

void TrafficFlow::AddStation(std::shared_ptr<Station> station) { stations_.push_back(station); }

const std::vector<std::shared_ptr<Station>>& TrafficFlow::GetStations() const { return stations_; }

// void TrafficFlow::AddVehicle(std::shared_ptr<vehicles::Vehicle> v) { vehicles_.push_back(v); }
// const std::vector<std::shared_ptr<vehicles::Vehicle>>& TrafficFlow::GetVehicles() const { return vehicles_; }

void TrafficFlow::StepSimulation(double minutes, double speed_kmh) {
   double distance_km = (speed_kmh * minutes) / 60.0;

   for (const auto& vehicle : vehicles_) {
      vehicle->Move(static_cast<int>(distance_km));
   }
}

}  // namespace world
