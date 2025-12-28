#include "simulation/simulation_manager.hpp"

#include <random>
#include <iostream>
#include <memory>

#include <vector>
#include <thread>

#include "world/highway.hpp"
#include "world/charging_station.hpp"
#include "world/traffic_flow.hpp"
#include "vehicles/ev_model.hpp"
#include "vehicles/ev.hpp"

namespace simulation {

void SimulationManager::StepSimulation(unsigned steps) {
  std::vector<std::thread> threads(highway_->GetTrafficFlows().size());

  for (size_t i = 0; i < threads.size(); i++) {
    threads[i] = std::thread([this, i, steps]() {
      for (size_t step = 0; step < steps; step++) {
        highway_->GetTrafficFlows()[i]->StepSimulation(simulationStepMinutes_, highway_->GetSpeedLimit());
      }
    });
  }

  for (auto& thread : threads) {
    if (thread.joinable()) thread.join();
  }

  PrintStatus();

  // for (size_t step = 0; step < steps; ++step) {
  //   std::cout << "Simulation Step " << (step + 1) << " / " << steps << "\n";
  // }
}

void SimulationManager::InitializeWorld() {
  highway_->SetSpeedLimit(100.0);

  auto flowSN = std::make_shared<world::TrafficFlow>(world::Direction::kSouthToNorth, 3688);
  auto flowNS = std::make_shared<world::TrafficFlow>(world::Direction::kNorthToSouth, 4321);
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
  double destination_km = highway_->GetLength();
  double speed_kmh = highway_->GetSpeedLimit();

  uint64_t vehicleID = 0;
  for (const auto& flow : highway_->GetTrafficFlows()) {
    int totalVehiclesPerHour = flow->GetVehiclesPerHour();
    double evCountDouble = static_cast<double>(totalVehiclesPerHour) * (destination_km / speed_kmh) * evPercentage_;
    int evCount = static_cast<int>(evCountDouble);

    for (int i = 0; i < evCount; ++i) {
      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_real_distribution<> dis(0.0, destination_km);
      double start_position_km = dis(gen);
      auto ev = std::make_shared<vehicles::EV>(vehicleID++, evModels_.at(i % evModels_.size()), start_position_km, destination_km);
      flow->AddVehicle(ev);
    }
  }
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
              << (flow->GetDirection() == world::Direction::kNorthToSouth ? "North to South" : "South to North")
              << ", Vehicles per Hour: " << flow->GetVehiclesPerHour() << "\n";
    for (const auto& station : flow->GetStations()) {
      std::cout << "  - Station Name: " << station->GetName()
                << ", Position: " << station->GetPosition() << " km\n";
    }
    std::cout << "  - Vehicles in Flow: " << flow->GetVehicles().size() << "\n";
    // for (const auto& vehicle : flow->GetVehicles()) {
    //   vehicle->PrintInfo();
    // }
  }
}

void SimulationManager::PrintStatus() {
  std::cout << "Simulation Status:\n";
  for (const auto& flow : highway_->GetTrafficFlows()) {
    std::cout << "Traffic Flow Direction: " 
              << (flow->GetDirection() == world::Direction::kNorthToSouth ? "North to South" : "South to North") 
              << "\n";
    for (const auto& station : flow->GetStations()) {
      auto chargingStation = std::dynamic_pointer_cast<world::ChargingStation>(station);
      if (chargingStation) {
        std::cout << "  - Station Name: " << chargingStation->GetName() 
                  << ", Total Charges: " << chargingStation->GetChargeCount() 
                  << ", Max Queue Length: " << chargingStation->GetMaxQueueLength()
                  << ", Current Queue Length: " << chargingStation->GetQueueLength() << "\n";
      }
    }
  }
}

}  // namespace simulation
