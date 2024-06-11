#include <iostream>
#include <optional>
#include <chrono>
#include <thread>
#include <filesystem>
#include <fstream>

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

    // TODO: replace this with writing into raw terminal context
    void Run()
    {
        while (true)
        {
            m_currStep++;

#if _WIN32
            system("cls");
#else
            system("clear");
#endif

            std::cout << "Krok symulacji: " << m_currStep << '\n';
            std::cout << m_grid;

            OrganismsStatistics stats = m_grid.GetOrganismsStatistics();
            std::cout << "Glony    * : " << stats.nAlge << '\n';
            std::cout << "Grzyby   # : " << stats.nFungus << '\n';
            std::cout << "Bakterie @ : " << stats.nBacteria << '\n';
            std::cout << "Martwe   + : " << stats.nDead << '\n';

            if (!(stats.nAlge || stats.nBacteria || stats.nFungus))
                break;

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