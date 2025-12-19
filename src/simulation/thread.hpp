#include <mutex>
#include <condition_variable>
#include <vector>
#include <memory>

#include "../vehicles/vehicle.hpp"

class Barrier {
 public:
   explicit Barrier(std::size_t count)
      : thread_count(count), waiting(0), generation(0) {}

   void arrive_and_wait() {
      std::unique_lock<std::mutex> lock(mutex);
      auto gen = generation;

      if (++waiting == thread_count) {
         generation++;
         waiting = 0;
         cv.notify_all();
      } else {
         cv.wait(lock, [&] { return gen != generation; });
      }
   }

 private:
   std::mutex mutex;
   std::condition_variable cv;
   std::size_t thread_count;
   std::size_t waiting;
   std::size_t generation;
};

// A simple step controller that serializes calls to a single simulation step.
// Call `Step(actors, x)` to execute `Move(10*x)` for all vehicles while
// preventing concurrent step callers from entering the step at the same time.
namespace thread {
inline std::mutex step_mutex;

// Step control primitives shared across translation units.
inline std::mutex control_mutex;
inline std::condition_variable control_cv;
inline int control_x = 0;
inline bool control_has_step = false;
inline Barrier* step_barrier = nullptr;

inline void SetBarrier(Barrier* b) { step_barrier = b; }

inline void SetStep(int x) {
   std::unique_lock<std::mutex> lock(control_mutex);
   control_x = x;
   control_has_step = true;
   control_cv.notify_all();
}

inline int WaitForStep() {
   std::unique_lock<std::mutex> lock(control_mutex);
   control_cv.wait(lock, [] { return control_has_step; });
   return control_x;
}

inline void ClearStep() {
   std::unique_lock<std::mutex> lock(control_mutex);
   control_has_step = false;
}

template <typename T>
inline void Step(const std::vector<std::shared_ptr<T>>& actors, int x) {
   std::lock_guard<std::mutex> lock(step_mutex);
   int distance = 10 * x;
   for (const auto& a : actors) {
      if (a) {
         a->Move(distance);
      }
   }
}

}  // namespace thread
