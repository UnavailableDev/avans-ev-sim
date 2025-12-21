#include "traffic_flow.hpp"

#include <thread>
#include <iostream>

namespace world {

void TrafficFlow::AddStation(std::shared_ptr<Station> station) { stations_.push_back(station); }
const std::vector<std::shared_ptr<Station>>& TrafficFlow::GetStations() const { return stations_; }

void TrafficFlow::AddVehicle(std::shared_ptr<vehicles::Vehicle> vehicle) { vehicles_.push_back(vehicle); }
const std::vector<std::shared_ptr<vehicles::Vehicle>>& TrafficFlow::GetVehicles() const { return vehicles_; }

void TrafficFlow::StepSimulation(double minutes, double speed_kmh) {
   double distance_km = (speed_kmh * minutes) / 60.0;

   for (const auto& vehicle : vehicles_) {
      vehicle->Move(static_cast<int>(distance_km));
   }
}

void TrafficFlow::PrintVehicles() const {
   for (const auto& vehicle : vehicles_) {
      std::cout << "Vehicle ID: " << vehicle->GetID() << ", Position: " << vehicle->GetPosition_km() << " km\n";
   }
}

}  // namespace world
