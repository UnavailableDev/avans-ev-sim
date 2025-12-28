#pragma once

#include "station.hpp"
#include "vehicles/ev.hpp"

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

  void HandleArrival(std::shared_ptr<vehicles::Vehicle> v) override;

  int GetQueueLength() const;
  int GetMaxQueueLength() const { return maxQueueLength_; }
  int GetChargeCount() const { return chargeCount_; }

 protected:
  world::FuelType fuelType_{world::FuelType::kElectric};

 private:
  // thread-safe methods to manage the queue
  void AddToQueue(std::shared_ptr<vehicles::EV> ev);
  std::shared_ptr<vehicles::EV> PopFromQueue();

 private:
  mutable std::mutex queueMutex_;
  std::queue<std::shared_ptr<vehicles::EV>> evQueue_;

  // int queue_length_{0};
  int maxQueueLength_{0};
  int chargeCount_{0};
};

}  // namespace world
