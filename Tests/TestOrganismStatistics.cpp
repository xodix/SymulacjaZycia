#include <iostream>
#include <optional>
#include <string>
#include <chrono>
#include <thread>
#include <fstream>
#include <random>
#include <sstream>

#include "../Headers/RandomGenerator.h"
#include "../Headers/Vicinity.h"
#include "../Headers/Rows.h"
#include "../Headers/Organism.h"
#include "../Headers/Grid.h"
#include "TestingUtilities.h"

int TestCreateOrganismStatistics()
{
	std::string input = "_+*\n#@*\n++_";
	std::istringstream is(input);
	Grid grid = Grid(3, 3);
	is >> grid;
	OrganismsStatistics statistics = grid.GetOrganismsStatistics();

	if (statistics.nAlge != 2)
		return EXIT_FAILURE;

	if (statistics.nBacteria != 1)
		return EXIT_FAILURE;

	if (statistics.nFungus != 1)
		return EXIT_FAILURE;

	if (statistics.nDead != 3)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

// As this is a standardized basic_istream and basic_ostream abstractions. I can use the following with both stringstream and fstream.
int main(int argc, char *argv[])
{
	test("Creating Organism Statistics", TestCreateOrganismStatistics);

	return EXIT_SUCCESS;
}