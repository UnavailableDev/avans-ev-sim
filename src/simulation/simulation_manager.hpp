#pragma once

// #include <memory>
// #include <memory.h>

#include "world/highway.hpp"
#include "vehicles/ev_model.hpp"
#include "vehicles/ev.hpp"

namespace simulation {

class SimulationManager {
 public:
  SimulationManager(const double ev_percentage = 0.05) 
  : evPercentage_(ev_percentage) {
    highway_ = std::make_unique<world::Highway>();
  }
  ~SimulationManager() = default;

  void StartSimulation();
  void StopSimulation();

 private:
  void InitializeWorld();
  void InitializeVehicleModels();
  void InitializeVehicles();

  void PrintInitializationSummary();

  std::unique_ptr<world::Highway> highway_;
  std::vector<std::shared_ptr<vehicles::EVModel>> evModels_;
  std::vector<std::shared_ptr<vehicles::EV>> evs_;

  Statistics statistics_;

  // Configurations
  double evPercentage_;
  int simulationDurationMinutes_{60};
  int simulationStepMinutes_{1};
};

}  // namespace simulation
