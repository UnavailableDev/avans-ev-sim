#include "simulation_actor.hpp"

namespace simulation {

SimulationActor::SimulationActor() : running_(false) {}

SimulationActor::~SimulationActor() {
  Stop();  // ensures no detached threads remain
}

void SimulationActor::Start() {
  if (running_)
    return;  // already running

  running_ = true;

  thread_ = std::thread([this]() {
    Act();
    running_ = false;
  });
}

void SimulationActor::Stop() {
  if (!running_)
    return;  // not running
  
  running_ = false;
  
  if (thread_.joinable()) {
    thread_.join();
  }
}

}  // namespace simulation
