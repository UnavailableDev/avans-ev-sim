#include "simulation/simulation_manager.hpp"

#include <random>
#include <iostream>
#include <memory>

#include "world/highway.hpp"
#include "world/charging_station.hpp"
#include "world/traffic_flow.hpp"
#include "vehicles/ev_model.hpp"
#include "vehicles/ev.hpp"

namespace simulation {

void SimulationManager::InitializeWorld() {
  highway_->SetSpeedLimit(100.0);

  auto flowSN = std::make_shared<world::TrafficFlow>(world::Direction::SOUTH_TO_NORTH, 3688);
  auto flowNS = std::make_shared<world::TrafficFlow>(world::Direction::NORTH_TO_SOUTH, 4321);
  auto station1 = std::make_shared<world::ChargingStation>("Station Lingehorst", 30.0);
  auto station2 = std::make_shared<world::ChargingStation>("Station Bisde", 12.0);
  flowSN->AddStation(station1);
  flowNS->AddStation(station2);
  highway_->AddTrafficFlow(flowSN);
  highway_->AddTrafficFlow(flowNS);

  InitializeVehicleModels();
  InitializeVehicles();
}

void SimulationManager::InitializeVehicleModels() {
  // EVs should to be ordered according to their distribution, from lowest to highest
  evModels_.push_back(std::make_shared<vehicles::EVModel>("VW ID.3", 62.0, 166, 19950));
  evModels_.push_back(std::make_shared<vehicles::EVModel>("Kia Niro", 68.0, 168, 23105));
  evModels_.push_back(std::make_shared<vehicles::EVModel>("Tesla Model 3", 60.0, 142, 45545)); // 60kWh, 142 Wh/km
}

void SimulationManager::InitializeVehicles() {

}

void SimulationManager::PrintInitializationSummary() {
  std::cout << "Simulation Initialization Summary:\n";
  std::cout << "Highway Length: " << highway_->GetLength() << " km\n";
  std::cout << "Speed Limit: " << highway_->GetSpeedLimit() << " km/h\n";
  // std::cout << "Number of Charging Stations: " << highway_->GetTrafficFlows() GetStations().size() << "\n";
  // for (const auto& station : highway_->GetStations()) {
  //   std::cout << "  - Station Name: " << station->GetName() 
  //             << ", Position: " << station->GetPosition() << " km\n";
  // }
  std::cout << "Number of Traffic Flows: " << highway_->GetTrafficFlows().size() << "\n";
  for (const auto& flow : highway_->GetTrafficFlows()) {
    std::cout << "  - Flow Direction: " 
              << (flow->GetDirection() == world::Direction::NORTH_TO_SOUTH ? "North to South" : "South to North")
              << ", Vehicles per Hour: " << flow->GetVehiclesPerHour() << "\n";
    for (const auto& station : flow->GetStations()) {
      std::cout << "  - Station Name: " << station->GetName()
                << ", Position: " << station->GetPosition() << " km\n";
    }
  }
}

}  // namespace simulation
