#pragma once

#include <thread>
#include <atomic>

namespace simulation {

class SimulationActor {
 public:
  virtual ~SimulationActor() = default;

  void Start();
  void Stop();

 protected:
  virtual void Run() = 0;

 private:
  std::thread thread_;
  std::atomic<bool> running_{false};
};

}  // namespace simulation
