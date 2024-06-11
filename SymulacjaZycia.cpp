#include <iostream>
#include <optional>
#include <chrono>
#include <thread>
#include <filesystem>
#include <fstream>
#include <sstream>

#define N_COLS 30
#define N_ROWS 30
constexpr std::chrono::milliseconds SIMULATION_STEP_TIMEOUT(1000);

#include "Headers/RandomGenerator.h"
#include "Headers/Vicinity.h"
#include "Headers/Rows.h"
#include "Headers/Organism.h"
#include "Headers/Grid.h"

class Simulation
{
protected:
	Grid m_grid;
	std::filesystem::path m_filePath;
	size_t m_currStep = 0;

	inline void clearScreen() {
#if _WIN32
			system("cls");
#else
			system("clear");
#endif
	}

public:
	Simulation(std::string filePath) : m_grid(N_ROWS, N_COLS), m_filePath(filePath)
	{
		if (!filePath.empty())
		{
			std::ifstream file(filePath);
			if (!file.is_open())
				throw std::runtime_error("Nie można otworzyć pliku z konfiguracją początkową!");

			m_grid.FillFile(file);
		}
		else
		{
			m_grid.FillRandom();
		}
	}

	void Run()
	{
		clearScreen();

		while (true)
		{
			std::stringstream writeBuffer;
			m_currStep++;

			// ANSI sequences work differently on different TERMINALS. Using slow solution instead.
			clearScreen();

			writeBuffer << "Krok symulacji: " << m_currStep << '\n';
			writeBuffer << m_grid;

			OrganismsStatistics stats = m_grid.GetOrganismsStatistics();
			writeBuffer << "Glony    * : " << stats.nAlge << '\n';
			writeBuffer << "Grzyby   # : " << stats.nFungus << '\n';
			writeBuffer << "Bakterie @ : " << stats.nBacteria << '\n';
			writeBuffer << "Martwe   + : " << stats.nDead << '\n';

			if (!(stats.nAlge || stats.nBacteria || stats.nFungus))
				break;

			std::cout << writeBuffer.str();

			m_grid.Step();
			std::this_thread::sleep_for(SIMULATION_STEP_TIMEOUT);
		}
	}
};

int main(int argc, const char *argv[])
{
	setlocale(LC_ALL, "pl_PL");
	Simulation simulation = Simulation((argc > 1) ? argv[1] : std::string());
	simulation.Run();

	std::cout << "Symulacja się zakończyła ponieważ nie ma w niej żywych organizmów.\n";

	return 0;
}