#include "charging_station.hpp"

namespace world {

void ChargingStation::HandleArrival(std::shared_ptr<vehicles::Vehicle> v) {
  auto ev_ptr = std::dynamic_pointer_cast<vehicles::EV>(v);
  if (ev_ptr) {
    AddToQueue(ev_ptr);
  }
}

void ChargingStation::Update() {
  auto ev = PopFromQueue();
  if (ev) {
    // Simulate charging by setting its state of charge to 1.0
    ev->SetStateOfCharge(1.0);
  }
}

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
  if (evQueue_.empty()) return nullptr;
  
  auto ev = evQueue_.front();
  evQueue_.pop();
  chargeCount_++;
  totalCharged_ += ev->GetStateOfCharge() * ev->GetModel().GetBatteryCapacity_kWh();
  return ev;
}

int ChargingStation::GetQueueLength() const {
  std::lock_guard<std::mutex> lock(queueMutex_);
  return static_cast<int>(evQueue_.size());
}

}  // namespace world
