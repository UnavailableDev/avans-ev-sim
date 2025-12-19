#include "traffic_flow.hpp"

#include "simulation/thread.hpp"

#include <thread>
#include <chrono>

namespace world {

void TrafficFlow::AddStation(std::shared_ptr<Station> station) { stations_.push_back(station); }

const std::vector<std::shared_ptr<Station>>& TrafficFlow::GetStations() const { return stations_; }

void TrafficFlow::AddVehicle(std::shared_ptr<vehicles::Vehicle> v) { vehicles_.push_back(v); }

const std::vector<std::shared_ptr<vehicles::Vehicle>>& TrafficFlow::GetVehicles() const { return vehicles_; }

void TrafficFlow::Act() {
  // Start all vehicle actors so each runs on its own thread
  for (auto& v : vehicles_) {
    if (v) {
      v->Start();
    }
  }

  // Barrier should include this TrafficFlow thread (+1) and all vehicles
  Barrier barrier(std::max<std::size_t>(1, vehicles_.size() + 1));
  thread::SetBarrier(&barrier);

  while (IsRunning()) {
    // Publish a step. The step size 'x' can be chosen based on simulation parameters.
    int x = 1; // simple fixed step for now
    thread::SetStep(x);

    // Wait until all vehicles (and this controller) reach the barrier
    barrier.arrive_and_wait();

    // Clear the step flag so vehicle threads will block until the next step
    thread::ClearStep();

    // small pause to pace the simulation controller
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  // Stop all vehicles and clean up
  for (auto& v : vehicles_) {
    if (v) {
      v->Stop();
    }
  }

  thread::SetBarrier(nullptr);
}

}  // namespace world
