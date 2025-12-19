#include "vehicle.hpp"

#include "simulation/thread.hpp"

namespace vehicles {

void Vehicle::Act() {
  // Placeholder implementation; actual movement logic should be in derived classes 
  int x = thread::WaitForStep();
  Move(10 * x);
  if (thread::step_barrier) {
    thread::step_barrier->arrive_and_wait();
  }
}

}  // namespace vehicles
