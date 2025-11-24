#include "ev_model.hpp"

namespace vehicles {

EVModel::EVModel() : batteryCapacity_kWh_(0), usage_Wh_km_(0), distribution_(0) {
   name_ = "Undefined";
}

}  // namespace vehicles
