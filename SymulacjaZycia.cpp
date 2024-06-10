#include <iostream>
#include <optional>
#include <string>
#include <chrono>
#include <thread>
#include <filesystem>
#include <fstream>
#include <random>

#define N_COLS 30
#define N_ROWS 30
constexpr std::chrono::milliseconds SIMULATION_STEP_TIMEOUT(1000);

#include "Headers/RandomGenerator.h"
#include "Headers/Vicinity.h"
#include "Headers/Rows.h"
#include "Headers/Organism.h"
#include "Headers/Grid.h"

class Simulation {
	Grid grid;
	std::filesystem::path filePath;
	size_t currStep = 0;

public:
	Simulation(std::string filePath) : grid(N_ROWS, N_COLS), filePath(filePath) {
		if (!filePath.empty()) {
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

			grid.step();
			std::this_thread::sleep_for(SIMULATION_STEP_TIMEOUT);
		}
	}
};

int main(int argc, const char *argv[])
{
	Simulation simulation = Simulation((argc > 1) ? argv[1] : std::string());
	simulation.run();
	std::cout << "Symulacja się zakończyła ponieważ nie ma w niej żywych organizmów.\n";

	return 0;
}