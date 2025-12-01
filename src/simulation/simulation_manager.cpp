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

void SimulationManager::StartSimulation() {
  InitializeWorld();
}

void SimulationManager::StopSimulation() {}

void SimulationManager::InitializeWorld() {
  highway_->SetLength(40.0);
  highway_->SetSpeedLimit(100.0);

  // TODO: Add station directionality information
  auto station1 = std::make_shared<world::ChargingStation>("Station Lingehorst", 30.0);
  auto station2 = std::make_shared<world::ChargingStation>("Station Bisde", 12.0);
  highway_->AddStation(station1);
  highway_->AddStation(station2);
  

  auto flow1 = std::make_shared<world::TrafficFlow>(world::Direction::SOUTH_TO_NORTH, 3688);
  auto flow2 = std::make_shared<world::TrafficFlow>(world::Direction::NORTH_TO_SOUTH, 4321);
  highway_->AddTrafficFlow(flow1);
  highway_->AddTrafficFlow(flow2);

  InitializeVehicleModels();
  InitializeVehicles();

#if 0
  PrintInitializationSummary();
#endif
}

void SimulationManager::InitializeVehicleModels() {
  // EVs should to be ordered according to their distribution, from lowest to highest
  evModels_.push_back(std::make_shared<vehicles::EVModel>("VW ID.3", 62.0, 166, 19950));
  evModels_.push_back(std::make_shared<vehicles::EVModel>("Kia Niro", 68.0, 168, 23105));
  evModels_.push_back(std::make_shared<vehicles::EVModel>("Tesla Model 3", 60.0, 142, 45545)); // 60kWh, 142 Wh/km
}

void SimulationManager::InitializeVehicles() {
  int totalExpectedVehicles = 0;
  for (const auto& flow : highway_->GetTrafficFlows()) {
    totalExpectedVehicles += static_cast<int>(flow->GetVehiclesPerHour() * (simulationDurationMinutes_ / 60.0));
  }

  int totalEVs = static_cast<int>(totalExpectedVehicles * evPercentage_);
  int totalDistributionEVs = 0;
  for (const auto& model : evModels_) {
    totalDistributionEVs += model->GetDistribution();
  }

  evs_.reserve(totalEVs);
  double highwayLength = highway_->GetLength();

  for (int i = 0; i < totalEVs; i++) {
    // Select EV model based on distribution
    int randValue = rand() % totalDistributionEVs;
    int cumulativeDistribution = 0;
    std::shared_ptr<vehicles::EVModel> selectedModel = nullptr;
    
    for (const auto& model : evModels_) { // Find the model corresponding to the random selected value
      cumulativeDistribution += model->GetDistribution();
      if (randValue < cumulativeDistribution) {
        selectedModel = model;
        break;
      }
    }

    if (selectedModel) {
      double soc = ((double)rand()/ (double)RAND_MAX);
      auto ev = std::make_shared<vehicles::EV>(i, *selectedModel.get(), 0.0, soc);

      // TODO: Randomize start position along the highway
      // ev->position_km_ = static_cast<double>(rand()) / RAND_MAX * highwayLength;
      evs_.push_back(ev);
    }
  }
}

void SimulationManager::PrintInitializationSummary() {
  std::cout << "Simulation Initialization Summary:\n";
  std::cout << "Highway Length: " << highway_->GetLength() << " km\n";
  std::cout << "Speed Limit: " << highway_->GetSpeedLimit() << " km/h\n";
  std::cout << "Number of Charging Stations: " << highway_->GetStations().size() << "\n";
  for (const auto& station : highway_->GetStations()) {
    std::cout << "  - Station Name: " << station->GetName() 
              << ", Position: " << station->GetPosition() << " km\n";
  }
  std::cout << "Number of Traffic Flows: " << highway_->GetTrafficFlows().size() << "\n";
  for (const auto& flow : highway_->GetTrafficFlows()) {
    std::cout << "  - Flow Direction: " 
              << (flow->GetDirection() == world::Direction::NORTH_TO_SOUTH ? "North to South" : "South to North")
              << ", Vehicles per Hour: " << flow->GetVehiclesPerHour() << "\n";
  }
  std::cout << "Number of EV Models: " << evModels_.size() << "\n";
  for (const auto& model : evModels_) {
    int count = 0;
    for (const auto& ev : evs_) {
      if (ev->GetModel().GetName() == model->GetName()) {
        count++;
      }
    }
    std::cout << "  - Model Name: " << model->GetName() 
              << ", Battery Capacity: " << model->GetBatteryCapacity_kWh() << " kWh"
              << ", Usage: " << model->GetUsage_Wh_km() << " Wh/km"
              << ", Distribution: " << model->GetDistribution()
              << ",  In simulation: " << count << " EVs\n";
  }
  std::cout << "Total EVs Initialized: " << evs_.size() << "\n";
  // for (const auto& ev : evs_) {
  //   std::cout << "  - EV ID: " << ev->GetID() 
  //             << ", Model: " << ev->GetModel().GetName() 
  //             << ", Initial SOC: " << ev->GetStateOfCharge() * 100 << "%\n";
  // }
}

}  // namespace simulation
