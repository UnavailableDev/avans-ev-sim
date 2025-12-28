#include "ev.hpp"

#include <iostream>

namespace vehicles {


void EV::Move(double distance_km) {
  if (this->Action()) {
    position_km_ += distance_km;
    // Decrease state of charge based on model usage
    double usage = model_.GetUsage_Wh_km() * distance_km; // Wh used for x km
    double batteryCapacity_Wh = model_.GetBatteryCapacity_kWh() * 1000; // convert kWh to Wh
    soc_ -= usage / batteryCapacity_Wh;

    if (position_km_ >= destination_km_) {
      position_km_ = 0.0;
      soc_ = RandomSOC();
      // std::cout << "EV ID " << id_ << " has reached its destination\n";
    }
  }
}

bool EV::Action() {
  if (soc_ < 0) {
    std::cout << "EV ID " << id_ << " has depleted its battery!\n";
    // running_ = false;
    return false;
  } else if (soc_ < 0.1) {
    /// TODO: find look for charging station and join queue (mutex handling in station needed).
    return false;
  }
  return true;
}
void EV::PrintInfo() const {
    std::cout << "EV ID: " << id_ 
              << ", Model: " << model_.GetName() 
              << ", Position: " << position_km_ << " km"
              << ", Destination: " << destination_km_ << " km"
              << ", State of Charge: " << soc_ * 100 << " %\n"; 
}

}  // namespace vehicles
