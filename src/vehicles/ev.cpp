#include "ev.hpp"

#include <iostream>

namespace vehicles {

void EV::Run() {
}

void EV::Move() {
  // Placeholder movement
  const double stepDistance_km = 0.1;
  position_km_ += stepDistance_km;
  // Decrease state of charge based on model usage
  double usage = model_.GetUsage_Wh_km() * stepDistance_km; // Wh used for x km
  double batteryCapacity_Wh = model_.GetBatteryCapacity_kWh() * 1000; // convert kWh to Wh
  soc_ -= usage / batteryCapacity_Wh;
  if (soc_ < 0) {
    std::cout << "EV ID " << id_ << " has depleted its battery!\n";
    soc_ = 0;
    Stop(); // Exit the simulation
    // running_ = false;
  }
}

}  // namespace vehicles
