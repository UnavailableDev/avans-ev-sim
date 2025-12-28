#include "ev.hpp"
#include "world/station.hpp"

#include <iostream>

namespace vehicles {


void EV::Move(double distance_km) {
  if (this->Action(distance_km)) {
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

bool EV::Action(double distance_km) {
  if (soc_ < 0) {
    std::cout << "EV ID " << id_ << " has depleted its battery!\n";
    // running_ = false;
    return false;
  } else if (soc_ < 0.1) {
    if (atStation_)
      return false;

    // Check the upcoming stations
    for (const auto& station : routeStations_) {
      if (station->GetPosition() >= position_km_ && station->GetFuelType() == this->fuelType_) {
        if (station->GetPosition() - position_km_ <= distance_km) {
          this->atStation_ = true;
          position_km_ = station->GetPosition();
          // Pass actual EV object via self_ptr instead of creating a copy
          station->HandleArrival(std::dynamic_pointer_cast<EV>(self_ptr_));
          return false;
        } else {
          return true;
        }
      }
    }
  } else if (atStation_) {
    // Leaving station after charging
    atStation_ = false;
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
