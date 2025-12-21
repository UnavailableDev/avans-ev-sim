#include <iostream>
#include <string>

#include "vehicles/ev.hpp"

#include "manager.hpp"
#include "simulation/simulation_manager.hpp"

int main() {
  while (1) {

    /// Input
    std::cout << "Set EV percentage (5% default): ";
    std::string input;

    double percentage = 0;
    std::getline(std::cin, input);
    if (input.empty()) {
      percentage = 0.05;
    } else {
      percentage = (double)atoi(input.c_str())/100;
    }

    std::cout << percentage*100 << "%\n";
    input.clear();

    simulation::SimulationManager sim_manager(percentage);
    sim_manager.StepSimulation(3);

    std::cout << "re-run? y/N: ";
    std::getline(std::cin, input);
    char in = *input.begin();
    if (in == 'y' || in == 'Y') {
      continue;
    }
    break;
  }
  return 0;
}
