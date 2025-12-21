#include "vehicle.hpp"
#include <iostream>

namespace vehicles {

bool Vehicle::Action() { return true; }

void Vehicle::PrintInfo() const {
	std::cout << "Vehicle ID: " << id_ << ", traveled: " << (position_km_/destination_km_) << " %\n";
}

}  // namespace vehicles
