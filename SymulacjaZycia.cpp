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
	Grid readGrid = Grid(N_ROWS, N_COLS);
	Grid writeGrid = Grid(N_ROWS, N_COLS);

public:
	Simulation() {
		readGrid.fillRandom();
	}

	void run() {
		while (true)
			readGrid.step();
	}
};

int main()
{
	Simulation simulation = Simulation();
	std::cout << "Fuck this!" << std::endl;
	return 0;
}