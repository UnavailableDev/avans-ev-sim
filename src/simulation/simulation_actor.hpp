#pragma once

#include <thread>
#include <atomic>

namespace simulation {

class SimulationActor {
 public:
  SimulationActor();
  virtual ~SimulationActor();

  void Start(); // start the actor's thread
  void Stop();  // stop the actor's thread
  bool IsRunning() const { return running_; }

 protected:
  virtual void Act() = 0; // main loop of the actor

 private:
  std::thread thread_;
  std::atomic<bool> running_{false};
};

}  // namespace simulation
