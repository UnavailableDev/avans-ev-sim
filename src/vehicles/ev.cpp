#include "ev.hpp"

#include <iostream>

namespace vehicles {


void EV::Move(int distance_km) {
  // Placeholder movement
  position_km_ += distance_km;
  // Decrease state of charge based on model usage
  double usage = model_.GetUsage_Wh_km() * distance_km; // Wh used for x km
  double batteryCapacity_Wh = model_.GetBatteryCapacity_kWh() * 1000; // convert kWh to Wh
  soc_ -= usage / batteryCapacity_Wh;
  if (soc_ < 0) {
    std::cout << "EV ID " << id_ << " has depleted its battery!\n";
    // running_ = false;
  }
}

}  // namespace vehicles
