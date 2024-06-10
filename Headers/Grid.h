#pragma once
#include <array>

#define CELL_EMPTY '_'

// Single cell in a grid.
class Cell {
    // Can contain Organism (dead or alive) or nullopt (empty) and is stored on the stack.
    std::optional<Organism> contents = std::nullopt;


    void feedAlge(Vicinity<Cell>& readVicinity) {
        contents.value().increaseMelas();
    }

    void feedFungus(Vicinity<Cell>& readVicinity) {
        Cell* dead[8]{};
        size_t n_dead = 0;

        for (size_t i = 0; i < readVicinity.length(); i++)
        {
            if (readVicinity[i]->contents.has_value()) {
                if (!readVicinity[i]->contents.value().isAlive()) {
                    dead[n_dead++] = readVicinity[i];
                }
            }
        }

        RandomGenerator generator = RandomGenerator();

        if (n_dead) {
            size_t n_cell = generator.generateRange(0, n_dead - 1);
            dead[n_cell]->contents = std::nullopt;
            contents.value().increaseMelas();
        }
    }

    void feedBacteria(Vicinity<Cell>& readVicinity) {
        Cell* cells[8]{};
        size_t n_alge = 0;
        size_t n_bacteria = 0;

        for (size_t i = 0; i < readVicinity.length(); i++)
        {
            if (readVicinity[i]->contents.has_value()) {
                Organism& currOrganism = readVicinity[i]->contents.value();
                switch (currOrganism.getType()) {
                case OrganismType::Alge:
                    cells[n_alge++] = readVicinity[i];
                    break;
                case OrganismType::Bacteria:
                    cells[7 - n_bacteria] = readVicinity[i];
                    n_bacteria++;
                    break;
                }
            }
        }

        RandomGenerator generator = RandomGenerator();
        if (n_alge) {
            size_t n_cell = generator.generateRange(0, n_alge-1);
            cells[n_cell]->contents = std::nullopt;
            contents.value().increaseMelas();
        }
        else if (n_bacteria) {
            size_t n_cell = generator.generateRange(8-n_bacteria, 7);
            cells[n_cell]->contents = std::nullopt;
            contents.value().increaseMelas();
        }
    }

public:
    Cell() {}

    Cell(Organism organism) : contents(organism) {}

    static Cell random() {
        RandomGenerator generator = RandomGenerator();
        // Empty cell has equal probability to every other type of cell.
        bool is_empty = generator.generateWeightedBoolean(1, 5);

        if (is_empty)
            return Cell();

        Organism organism = Organism::random();
        return Cell(organism);
    }

    std::optional<Organism>& getContents() {
        return contents;
    }

    // TODO
    void step(Vicinity<Cell> readVicinity) {
        if (!contents.has_value())
            return;

        Organism& organism = contents.value();
        if (!organism.isAlive())
            return;

        if (!organism.isFed()) {
            switch (organism.getType())
            {
            case OrganismType::Alge:
                feedAlge(readVicinity);
                break;
            case OrganismType::Fungus:
                feedFungus(readVicinity);
                break;
            case OrganismType::Bacteria:
                feedBacteria(readVicinity);
                break;
            default:
                throw;
                break;
            }
        }

        Cell* emptyCells[8];
        size_t n_empty = 0;
        for (size_t i = 0; i < readVicinity.length(); i++)
        {
            if (!readVicinity[i]->contents.has_value()) {
                emptyCells[n_empty++] = readVicinity[i];
            }
        }
        RandomGenerator generator = RandomGenerator();

        // TODO: Implement reproduction system
        if (n_empty && organism.isFed()) {
            if (organism.canReproduce()) {
                emptyCells[generator.generateRange(0, n_empty - 1)]->contents = Organism(organism.getType(), generator.generateRange(Organism::getMinAge(organism.getType()), Organism::getMaxAge(organism.getType())));
                organism.reproduce();
            }
            else if (organism.getType() == OrganismType::Fungus || organism.getType() == OrganismType::Bacteria) {
                emptyCells[generator.generateRange(0, n_empty - 1)]->contents = contents.value();
                contents = std::nullopt;
            }
        }

        organism.age();
    }

    friend std::ostream& operator<<(std::ostream& os, const Cell& cell);
    friend std::istream& operator>>(std::istream& os, Cell& cell);
};

std::ostream& operator<<(std::ostream& os, const Cell& cell) {
    if (cell.contents.has_value()) {
        os << cell.contents.value();
    }
    else {
        os << CELL_EMPTY;
    }

    return os;
}

std::istream& operator>>(std::istream& stream, Cell& cell)
{
    char cellRepresentation = CELL_EMPTY;
    stream >> cellRepresentation;

    if (cellRepresentation == CELL_EMPTY) {
        cell.contents = std::nullopt;
    }
    else {
        // All Organisms are created with the default age.
        switch (cellRepresentation)
        {
            case ORGANISM_DEAD:
                cell.contents = Organism(OrganismType::Alge, 0);
                break;
            case ORGANISM_ALGE:
                cell.contents = Organism(OrganismType::Alge);
                break;
            case ORGANISM_FUNGUS:
                cell.contents = Organism(OrganismType::Fungus);
                break;
            case ORGANISM_BACTERIA:
                cell.contents = Organism(OrganismType::Bacteria);
                break;
        default:
            // unrechable
            throw;
        }
    }

    return stream;
}

struct OrganismsStatistics {
    size_t nAlge = 0;
    size_t nFungus = 0;
    size_t nBacteria = 0;
    size_t nDead = 0;
};

class Grid {
    Rows<Cell> m_readBuffer;

public:

    Grid(size_t colLen, size_t rowLen) : m_readBuffer(colLen, rowLen) {}

    void fillFile(std::ifstream& file) {
        for (size_t i = 0; i < m_readBuffer.columnLength(); i++) {
            for (size_t j = 0; j < m_readBuffer.rowLength(); j++) {
                file >> m_readBuffer[i][j];
            }
        }
    }

    void fillRandom() {
        for (size_t i = 0; i < m_readBuffer.columnLength(); i++)
            for (size_t j = 0; j < m_readBuffer.rowLength(); j++) {
                //m_readBuffer[i][j] = Cell();
                m_readBuffer[i][j] = Cell::random();
            }
    }

    void step() {
        for (size_t i = 0; i < m_readBuffer.columnLength(); i++) {
            for (size_t j = 0; j < m_readBuffer.rowLength(); j++) {
                Cell& currCell = m_readBuffer[i][j];
                auto vicinity = Vicinity<Cell>(m_readBuffer, i, j);
                currCell.step(vicinity);
            }
        }
    }

    OrganismsStatistics organismsStatistics() {
        OrganismsStatistics organisms_statistics = OrganismsStatistics();
        organisms_statistics.nAlge = 0;
        organisms_statistics.nBacteria = 0;
        organisms_statistics.nDead = 0;
        organisms_statistics.nFungus = 0;

        for (size_t i = 0; i < m_readBuffer.columnLength(); i++) {
            for (size_t j = 0; j < m_readBuffer.rowLength(); j++) {
                std::optional<Organism>& currCell = m_readBuffer[i][j].getContents();
                if (currCell.has_value()) {
                    Organism& organism = currCell.value();
                    if (!organism.isAlive()) {
                        organisms_statistics.nDead++;
                        continue;
                    }

                    switch (organism.getType())
                    {
                        case OrganismType::Alge:
                            organisms_statistics.nAlge++;
                            break;

                        case OrganismType::Fungus:
                            organisms_statistics.nFungus++;
                            break;

                        case OrganismType::Bacteria:
                            organisms_statistics.nBacteria++;
                            break;

                        default:
                            throw;
                            break;
                    }
                }
                
            }
        }

        return organisms_statistics;
    }

    friend std::ostream& operator<<(std::ostream& os, Grid& grid);
    friend std::istream& operator>>(std::istream& stream, Grid& grid);
};

std::ostream& operator<<(std::ostream& os, Grid& grid) {
    for (size_t i = 0; i < grid.m_readBuffer.columnLength(); i++) {
        for (size_t j = 0; j < grid.m_readBuffer.rowLength(); j++) {
            os << grid.m_readBuffer[i][j];
        }
        os << '\n';
    }

    return os;
}

std::istream& operator>>(std::istream& stream, Grid& grid)
{
    for (size_t i = 0; i < grid.m_readBuffer.columnLength(); i++) {
        for (size_t j = 0; j < grid.m_readBuffer.rowLength(); j++) {
            stream >> grid.m_readBuffer[i][j];
        }
    }

    return stream;
}
