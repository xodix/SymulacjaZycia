#pragma once

// Single cell in a grid.
class Cell {
	// Can contain Organism (dead or alive) or nullopt (empty) and is stored on the stack.
	std::optional<Organism> contents = std::nullopt;

public:
	Cell() {
		contents = std::nullopt;
	}

	Cell(Organism organism) {
		contents = organism;
	}

	static Cell random() {
		static std::random_device rd;
		std::uniform_int_distribution<unsigned int> dist(0, 6);
		unsigned int hello = dist(rd);

		// Empty cell has equal probability to every other type of cell.
		if (hello == 0)
			return Cell();

		Organism organism = Organism::random();
		return Cell(organism);
	}

	// TODO
	void step() {};
};

class Grid {
	Rows<Cell> contents;

public:
	Grid(size_t colLen, size_t rowLen) {
		contents = Rows<Cell>(colLen, rowLen);
	}

	void fillRandom() {
		for (size_t i = 0; i < contents.columnLength(); i++)
			for (size_t j = 0; j < contents.rowLength(); j++) {
				contents[i][j] = Cell();
				contents[i][j] = Cell::random();
			}
	};

	//TODO
	void step() {
		while (true)
		{
			for (size_t i = 0; i < contents.columnLength(); i++)
				for (size_t j = 0; j < contents.rowLength(); j++) {
				}
			}
		}
	};
};
