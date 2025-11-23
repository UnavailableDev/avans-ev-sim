#pragma once

// #include <memory>
// #include <memory.h>

namespace simulation {

class SimulationManager {
 public:
  SimulationManager();
  void StartSimulation();
  void StopSimulation();

 private:
  void InitializeWorld();
};

}  // namespace simulation
