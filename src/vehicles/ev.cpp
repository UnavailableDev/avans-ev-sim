#include "ev.hpp"

#include <iostream>

namespace vehicles {


void EV::Move(double distance_km) {
  // Placeholder movement
  position_km_ += distance_km;
  // Decrease state of charge based on model usage
  double usage = model_.GetUsage_Wh_km() * distance_km; // Wh used for x km
  double batteryCapacity_Wh = model_.GetBatteryCapacity_kWh() * 1000; // convert kWh to Wh
  soc_ -= usage / batteryCapacity_Wh;
  if (soc_ < 0) {
    std::cout << "EV ID " << id_ << " has depleted its battery!\n";
    // running_ = false;
  } else if (position_km_ > destination_km_) {
    std::cout << "EV ID " << id_ << ", soc: " << soc_ * 100 << "%" << ", has reached its destination.\n";
  }
}

void EV::PrintInfo() const {
    std::cout << "EV ID: " << id_ 
              << ", Model: " << model_.GetName() 
              << ", Position: " << position_km_ << " km"
              << ", Destination: " << destination_km_ << " km"
              << ", State of Charge: " << soc_ * 100 << " %\n"; 
}

}  // namespace vehicles
