#include <iostream>
#include <optional>
#include <string>
#include <random>
#include <chrono>
#include <thread>
#include <fstream>

#define N_COLS 3
#define N_ROWS 5
constexpr std::chrono::milliseconds SIMULATION_STEP_TIMEOUT(100);

#include "Headers/Vicinity.h"
#include "Headers/Rows.h"
#include "Headers/Organism.h"
#include "Headers/Grid.h"

class Simulation {
	Grid grid;
	std::string filePath;
	size_t currStep = 0;

public:
	Simulation(std::string filePath) : grid(N_ROWS, N_COLS), filePath(filePath) {
		if (filePath.empty()) {
			std::ifstream file(filePath);
			if (!file.is_open()) {
				throw std::runtime_error("Grid file not found!");
			}

			grid.fillFile(file);
		}
		else {
			grid.fillRandom();
		}
	}

	// TODO: replace this with writing into raw terminal context
	void run() {
		while (true) {
			currStep++;
			grid.step();

#if _WIN32
			system("cls");
#else
			system("clear");
#endif

			std::cout << "Krok symulacji: " << currStep << '\n';
			std::cout << grid;

			// Improved speed O(4n) -> O(n). While preserving separation of concerns.
			OrganismsStatistics stats = grid.organismsStatistics();
			std::cout << "Glony    * : " << stats.nAlge << '\n';
			std::cout << "Grzyby   # : " << stats.nFungus << '\n';
			std::cout << "Bakterie @ : " << stats.nBacteria << '\n';
			std::cout << "Martwe   + : " << stats.nDead << '\n';

			std::this_thread::sleep_for(SIMULATION_STEP_TIMEOUT);
		}
	}
};

int main(int argc, const char *argv[])
{
	Simulation simulation = Simulation((argc > 1) ? argv[1] : "");
	simulation.run();

	std::cout << "Fuck this!" << std::endl;
	return 0;
}