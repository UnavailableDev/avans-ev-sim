#include "charging_station.hpp"

namespace world {

void ChargingStation::HandleArrival() {}

void ChargingStation::AddToQueue(std::shared_ptr<vehicles::EV> ev) {
  std::lock_guard<std::mutex> lock(queueMutex_);
  evQueue_.push(ev);
  int currentLength = static_cast<int>(evQueue_.size());
  if (currentLength > maxQueueLength_) {
    maxQueueLength_ = currentLength;
  }
}

std::shared_ptr<vehicles::EV> ChargingStation::PopFromQueue() {
  std::lock_guard<std::mutex> lock(queueMutex_);
  if (evQueue_.empty()) {
    return nullptr;
  }
  
  auto ev = evQueue_.front();
  evQueue_.pop();
  chargeCount_++;
  return ev;
}

int ChargingStation::GetQueueLength() const {
  std::lock_guard<std::mutex> lock(queueMutex_);
  return static_cast<int>(evQueue_.size());
}

}  // namespace world
