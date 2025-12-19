#include "vehicle.hpp"

#include "simulation/thread.hpp"

#include <chrono>
#include <thread>

namespace vehicles {

void Vehicle::Act() {
	// Each vehicle waits for a step signal, moves, then synchronizes using the barrier.
	while (IsRunning()) {
		int x = thread::WaitForStep();
		int distance = 10 * x;
		Move(distance);

		if (thread::step_barrier) {
			thread::step_barrier->arrive_and_wait();
		}

		// small sleep to avoid busy-looping if steps come rapidly
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

}  // namespace vehicles
