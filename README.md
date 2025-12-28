# EV Traffic Simulation (C++)

This project simulates EV traffic, charging queues, and charging station load
on a highway using a multithreaded, object-oriented design.

## Features (Design Phase only)
- Multithreaded EV actors
- Inheritance-based vehicle hierarchy
- Abstract station and actor classes
- Charging queue simulation
- Highway with two traffic directions

## Build

make

## Run

./simulation.out

## Clean

make clean

---

Coding style follows the **Google C++ Style Guide**.


### *notes*
- [ ] change call order to Action -> Move in EV/Vehicle (This makes the fuel usage a bit more accurate)
- [ ] Throw warning if station has still vehicles queued at en of simulation
- [ ] (optional) make charging take correct amount of time (adjust both flow and station code)
- [ ] (optional) make prints pretier
- [ ] Update PlantUML
- [ ] (optional) Add threading diagram (sequence diagram?)
- [ ] EVModel distrobution
- [ ] Adjust timesteps in simulator?
