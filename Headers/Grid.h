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
	void step(Vicinity<Cell> readVicinity, Vicinity<Cell> writeVicinity) {
		// Dead cells take no steps
		if (contents.has_value()) {
		}
	}
};

class Grid {
	Rows<Cell> m_readBuffer;
	Rows<Cell> m_writeBuffer;

public:

	Grid(size_t colLen, size_t rowLen) : m_readBuffer(colLen, rowLen), m_writeBuffer(colLen, rowLen) {}

	void fillRandom() {
		for (size_t i = 0; i < m_readBuffer.columnLength(); i++)
			for (size_t j = 0; j < m_readBuffer.rowLength(); j++) {
				m_readBuffer[i][j] = Cell();
				m_readBuffer[i][j] = Cell::random();
			}
	}

	void step() {
		while (true)
		{
			for (size_t i = 0; i < m_readBuffer.columnLength(); i++) {
				for (size_t j = 0; j < m_readBuffer.rowLength(); j++) {
					Cell currCell = m_readBuffer[i][j];
					auto readVicinity = Vicinity<Cell>(m_readBuffer, i, j);
					auto writeVicinity = Vicinity<Cell>(m_writeBuffer, i, j);
					currCell.step(readVicinity, writeVicinity);
				}
			}
		}
	}
};
