#include "simulation/simulation_manager.hpp"

#include <iostream>
#include <string>

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
    
    std::cout << percentage <<std::endl;
    input.clear();

    /// Simulation
    simulation::SimulationManager manager(percentage);
    manager.StartSimulation();

    // manager.~SimulationManager();

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
