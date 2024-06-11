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

	size_t paddingSize(size_t numberShowed, size_t messageLength)
	{
		int padding = N_COLS - log10(numberShowed) - messageLength;
		return (size_t)(padding > 0 ? padding : 0);
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
		while (true)
		{
			std::stringstream writeBuffer;
			m_currStep++;

			// Write over last buffer (ASCII escape codes)
			// Super fast but breaks when terminal window is not sized correctly
			writeBuffer << (char)27 << "[H";

			// Almost fixes the problem
			writeBuffer << "Krok symulacji: " << m_currStep << std::string(paddingSize(m_currStep, 17), ' ') << '\n';
			writeBuffer << m_grid;

			OrganismsStatistics stats = m_grid.GetOrganismsStatistics();
			writeBuffer << "Glony    * : " << stats.nAlge << std::string(paddingSize(stats.nAlge, 14), ' ') << '\n';
			writeBuffer << "Grzyby   # : " << stats.nFungus << std::string(paddingSize(stats.nFungus, 14), ' ') << '\n';
			writeBuffer << "Bakterie @ : " << stats.nBacteria << std::string(paddingSize(stats.nBacteria, 14), ' ') << '\n';
			writeBuffer << "Martwe   + : " << stats.nDead << std::string(paddingSize(stats.nDead, 14), ' ') << '\n';

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