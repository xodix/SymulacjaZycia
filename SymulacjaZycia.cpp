#include <iostream>
#include <optional>
#include <string>
#include <random>

#define N_COLS 3
#define N_ROWS 5

#include "Vicinity.h"
#include "Rows.h"
#include "Organism.h"
#include "Grid.h"

class Simulation {
	Grid readGrid;

public:
	Simulation() : readGrid(N_ROWS, N_COLS) {
		readGrid.fillRandom();
	}

	void run() {
		std::cout << "runnning the simulation right now;" << std::endl;
	}
};

int main()
{
	Simulation simulation = Simulation();
	simulation.run();

	std::cout << "Fuck this!" << std::endl;
	return 0;
}