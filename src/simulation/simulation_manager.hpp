#pragma once

#include "world/highway.hpp"
#include "vehicles/ev_model.hpp"

namespace simulation {

class SimulationManager {
 public:
  SimulationManager(const double ev_percentage = 0.05) 
    : evPercentage_(ev_percentage) {
    highway_ = std::make_unique<world::Highway>(40.0, 130);
    InitializeWorld();
    PrintInitializationSummary();
  }
  ~SimulationManager() = default;

  void StepSimulation(int steps = 1);

 private:
  void InitializeWorld();
  void InitializeVehicleModels();
  void InitializeVehicles();

  void PrintInitializationSummary();

  std::unique_ptr<world::Highway> highway_;
  std::vector<std::shared_ptr<vehicles::EVModel>> evModels_;

  // Configurations
  double evPercentage_;
  int simulationDurationMinutes_{60};
  int simulationStepMinutes_{1};
};

}  // namespace simulation
