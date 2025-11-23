#pragma once

#include "station.hpp"

namespace world {

class ChargingStation : public Station {
 public:
  ChargingStation();
  void HandleArrival() override;

 private:
  int queue_length_{0};
  int max_queue_length_{0};
  int charge_count_{0};
};

}  // namespace world
