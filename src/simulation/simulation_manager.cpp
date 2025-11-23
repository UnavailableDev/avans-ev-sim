#include "simulation/simulation_manager.hpp"

namespace simulation {

SimulationManager::SimulationManager() {}

void SimulationManager::StartSimulation() {
  InitializeWorld();
}

void SimulationManager::StopSimulation() {}

void SimulationManager::InitializeWorld() {}

}  // namespace simulation
