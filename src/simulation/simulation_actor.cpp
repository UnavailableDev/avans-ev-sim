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
    // If Stop() is called from the actor's own thread, don't try to join
    // (joining self causes std::system_error: Resource deadlock avoided).
    if (std::this_thread::get_id() == thread_.get_id()) {
      thread_.detach();
    } else {
      thread_.join();
    }
  }
}

}  // namespace simulation
