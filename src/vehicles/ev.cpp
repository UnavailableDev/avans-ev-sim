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
  // Battery depleted - cannot move
  if (soc_ < 0) {
    std::cout << "EV ID " << id_ << " has depleted its battery!\n";
    return false;
  }
  
  // If currently at a station, check if charged enough to leave
  if (atStation_) {
    if (soc_ >= 0.9) {
      atStation_ = false;
      return true;
    }
    return false;
  }
  
  // Battery low - check for nearby charging stations
  if (soc_ < 0.20) {
    for (const auto& station : routeStations_) {
      if (station->GetPosition() >= position_km_ && 
          station->GetFuelType() == this->fuelType_ &&
          station->GetPosition() - position_km_ <= distance_km) {
        // Station is ahead and within travel distance
        atStation_ = true;
        position_km_ = station->GetPosition();
        station->HandleArrival(std::dynamic_pointer_cast<EV>(self_ptr_));
        return false;
      }
    }
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
