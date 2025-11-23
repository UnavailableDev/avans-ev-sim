#include "simulation_actor.hpp"

namespace simulation {

void SimulationActor::Start() {
  running_ = true;
  thread_ = std::thread(&SimulationActor::Run, this);
}

void SimulationActor::Stop() {
  running_ = false;
  if (thread_.joinable()) {
    thread_.join();
  }
}

}  // namespace simulation
