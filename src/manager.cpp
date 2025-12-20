#include "manager.hpp"

#include <iostream>
#include <vector>
#include <thread>

#include "vehicles/ev_model.hpp"
#include "vehicles/ev.hpp"

static std::vector<vehicles::EV> ev_fleet;

void InitializeManager() {
   std::cout << "Manager initialized.\n";

   for (int i = 0; i < 500; ++i) {
      vehicles::EVModel model("Model_" + std::to_string(i), 50.0 + i * 10, 150.0 + i * 20, i);
      vehicles::EV ev(i, model);
      ev_fleet.push_back(ev);
      std::cout << "Added EV ID " << ev.GetID() << " with model " << model.GetName() << "\n";
   }
}

void StepSimulation() {
   std::cout << "Simulation started.\n";

   std::vector<std::thread> threads;

   for (auto& ev : ev_fleet) {
      threads.emplace_back([&ev]() {
         ev.Move(10); // Move each EV by 10 km
      });
   }

   for (auto& th : threads) {
      if (th.joinable()) {
         th.join();
      }
   }

   // for (const auto& ev : ev_fleet)
   //    std::cout << "EV ID " << ev.GetID() << " moved to position " << ev.GetPosition_km()
   //           << " km with SOC " << ev.GetStateOfCharge() << "\n";
}