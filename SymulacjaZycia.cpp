#include <iostream>
#include <optional>
#include <string>
#include <random>
#include <chrono>
#include <thread>

#define N_COLS 3
#define N_ROWS 5
constexpr std::chrono::milliseconds SIMULATION_STEP_TIMEOUT(100);

#include "Headers/Vicinity.h"
#include "Headers/Rows.h"
#include "Headers/Organism.h"
#include "Headers/Grid.h"

class Simulation {
	Grid grid;

public:
	Simulation() : grid(N_ROWS, N_COLS) {
		grid.fillRandom();
	}

	void run() {
		while (true) {
			grid.step();
			std::cout << grid;
			std::this_thread::sleep_for(SIMULATION_STEP_TIMEOUT);
		}
	}
};

int main()
{
	Simulation simulation = Simulation();
	simulation.run();

	std::cout << "Fuck this!" << std::endl;
	return 0;
}