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
  for (const auto& flow : highway_->GetTrafficFlows()) {
    if (flow) {
      flow->Start();
    }
  }
}

void SimulationManager::StopSimulation() {}

void SimulationManager::InitializeWorld() {
  highway_->SetLength(40.0);
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

#if 1
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
  /// Distribute EVs into each TrafficFlow based on that flow's vehicles-per-hour.
  // First compute the per-flow expected vehicle counts and reserve storage.
  int totalDistributionEVs = 0;
  for (const auto& model : evModels_) {
    totalDistributionEVs += model->GetDistribution();
  }

  double highwayLength = highway_->GetLength();

  // Compute per-flow EV counts and total to reserve
  std::vector<int> evs_per_flow;
  evs_per_flow.reserve(highway_->GetTrafficFlows().size());
  int totalEVs = 0;
  for (const auto& flow : highway_->GetTrafficFlows()) {
    double expectedVehicles = flow->GetVehiclesPerHour() * (simulationDurationMinutes_ / 60.0);
    int evCount = static_cast<int>(expectedVehicles * evPercentage_);
    evs_per_flow.push_back(evCount);
    totalEVs += evCount;
  }

  evs_.reserve(totalEVs);

  // Create EVs and place them into their flows
  int id_counter = 0;
  auto flows = highway_->GetTrafficFlows();
  for (std::size_t f = 0; f < flows.size(); ++f) {
    auto& flow = flows[f];
    int n = evs_per_flow[f];
    for (int j = 0; j < n; ++j) {
      // Select EV model based on distribution
      int randValue = rand() % totalDistributionEVs;
      int cumulativeDistribution = 0;
      std::shared_ptr<vehicles::EVModel> selectedModel = nullptr;

      for (const auto& model : evModels_) {
        cumulativeDistribution += model->GetDistribution();
        if (randValue < cumulativeDistribution) {
          selectedModel = model;
          break;
        }
      }

      if (selectedModel) {
        auto ev = std::make_shared<vehicles::EV>(id_counter++, *selectedModel.get());

        // TODO: Randomize start position along the highway
        // ev->position_km_ = static_cast<double>(rand()) / RAND_MAX * highwayLength;

        evs_.push_back(ev);
        if (flow) {
          flow->AddVehicle(ev);
        }
      }
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
              << (flow->GetDirection() == world::Direction::NORTH_TO_SOUTH ? "North to South" : "South to North")
              << ", Vehicles per Hour: " << flow->GetVehiclesPerHour() << "\n";
    for (const auto& station : flow->GetStations()) {
      std::cout << "  - Station Name: " << station->GetName()
                << ", Position: " << station->GetPosition() << " km\n";
    }
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
