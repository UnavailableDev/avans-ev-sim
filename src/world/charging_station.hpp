#pragma once

#include "station.hpp"

#include <queue>
#include <mutex>
#include <memory>

namespace vehicles {
class EV; // forward declaration
} // namespace vehicles

namespace world {

class ChargingStation : public Station {
 public:
  ChargingStation(std::string name, double position_km)
      : Station(name, position_km) {};
  ~ChargingStation() override = default;

  void HandleArrival() override;

  // thread-safe methods to manage the queue
  void AddToQueue(std::shared_ptr<vehicles::EV> ev);
  std::shared_ptr<vehicles::EV> PopFromQueue();

  int GetQueueLength() const;
  int GetMaxQueueLength() const { return maxQueueLength_; }
  int GetChargeCount() const { return chargeCount_; }

 private:
  mutable std::mutex queueMutex_;
  std::queue<std::shared_ptr<vehicles::EV>> evQueue_;

  // int queue_length_{0};
  int maxQueueLength_{0};
  int chargeCount_{0};
};

}  // namespace world
