#include <iostream>
#include <optional>
#include <string>
#include <random>
#include <chrono>
#include <thread>
#include <fstream>
#include <sstream>

#include "../Headers/RandomGenerator.h"
#include "../Headers/Vicinity.h"
#include "../Headers/Rows.h"
#include "../Headers/Organism.h"
#include "../Headers/Grid.h"
#include "TestingUtilities.h"

int test_read_write_empty_cell()
{
	std::string input;
	input.push_back(CELL_EMPTY);
	std::istringstream is(input);
	Cell cell;
	is >> cell;

	std::ostringstream os;
	os << cell;
	if (input != os.str())
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int test_read_write_dead_cell()
{
	std::string input;
	input.push_back(ORGANISM_DEAD);
	std::istringstream is(input);
	Cell cell;
	is >> cell;

	std::ostringstream os;
	os << cell;
	if (input != os.str())
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int test_read_write_alge_cell()
{
	std::string input;
	input.push_back(ORGANISM_ALGE);
	std::istringstream is(input);
	Cell cell;
	is >> cell;

	std::ostringstream os;
	os << cell;
	if (input != os.str())
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int test_read_write_fungus_cell()
{
	std::string input;
	input.push_back(ORGANISM_FUNGUS);
	std::istringstream is(input);
	Cell cell;
	is >> cell;

	std::ostringstream os;
	os << cell;
	if (input != os.str())
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int test_read_write_bacteria_cell()
{
	std::string input;
	input.push_back(ORGANISM_BACTERIA);
	std::istringstream is(input);
	Cell cell;
	is >> cell;

	std::ostringstream os;
	os << cell;
	if (input != os.str())
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int test_read_write_grid()
{
	std::string input = "_+*\n#@*";
	std::istringstream is(input);
	Grid grid = Grid(2, 3);
	is >> grid;

	std::ostringstream os;
	os << grid;

	return input == os.str();
}

// As this is a standardized basic_istream and basic_ostream abstractions. I can use the following with both stringstream and fstream.
int main(int argc, char *argv[])
{
	test("reading empty cell in and writing it out", test_read_write_empty_cell);
	test("reading a cell with dead organism in and writing it out", test_read_write_dead_cell);
	test("reading a cell with alge organism in and writing it out", test_read_write_alge_cell);
	test("reading a cell with fungus organism in and writing it out", test_read_write_fungus_cell);
	test("reading a cell with bacteria organism in and writing it out", test_read_write_bacteria_cell);

	test("reading grid in and writing it out", test_read_write_grid);

	return EXIT_SUCCESS;
}