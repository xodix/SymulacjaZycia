#pragma once

#define CELL_EMPTY '_'

// Single cell in a grid.
class Cell {
    // Can contain Organism (dead or alive) or nullopt (empty) and is stored on the stack.
    std::optional<Organism> contents = std::nullopt;

    void feedAlge(Vicinity<Cell>& readVicinity, Organism& alge) {
        alge.increaseMelas();
    }

    void feedFungus(Vicinity<Cell>& readVicinity, Organism& alge) {

    }

    void feedBacteria(Vicinity<Cell>& readVicinity, Organism& alge) {
    }

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
        unsigned int type_of_cell = dist(rd);

        // Empty cell has equal probability to every other type of cell.
        if (type_of_cell == 0)
            return Cell();

        Organism organism = Organism::random();
        return Cell(organism);
    }

    std::optional<Organism>& getContents() {
        return contents;
    }

    // TODO
    void step(Vicinity<Cell> readVicinity, Vicinity<Cell> writeVicinity) {
        // Dead cells take no steps
        if (contents.has_value()) {
            Organism& organism = contents.value();
            if (!organism.isAlive()) {
                return;
            }

            switch (organism.getOrganismType())
            {
            case OrganismType::Alge:
                feedAlge(readVicinity, organism);
                break;
            case OrganismType::Fungus:
                organism.isFed
                feedFungus(readVicinity, organism);
                break;
            case OrganismType::Bacteria:
                feedBacteria(readVicinity, organism);
                break;
            default:
                throw;
                break;
            }
        }
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
    Rows<Cell> m_writeBuffer;

public:

    Grid(size_t colLen, size_t rowLen) : m_readBuffer(colLen, rowLen), m_writeBuffer(colLen, rowLen) {}

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
                m_readBuffer[i][j] = Cell();
                m_readBuffer[i][j] = Cell::random();
            }
    }

    void step() {
        for (size_t i = 0; i < m_readBuffer.columnLength(); i++) {
            for (size_t j = 0; j < m_readBuffer.rowLength(); j++) {
                Cell currCell = m_readBuffer[i][j];
                auto readVicinity = Vicinity<Cell>(m_readBuffer, i, j);
                auto writeVicinity = Vicinity<Cell>(m_writeBuffer, i, j);
                currCell.step(readVicinity, writeVicinity);
            }
        }
    }

    OrganismsStatistics organismsStatistics() {
        OrganismsStatistics organisms_statistics = OrganismsStatistics();
        for (size_t i = 0; i < m_readBuffer.columnLength(); i++) {
            for (size_t j = 0; j < m_readBuffer.rowLength(); j++) {
                std::optional<Organism>& currCell = m_readBuffer[i][j].getContents();
                if (currCell.has_value()) {
                    Organism& organism = currCell.value();
                    if (!organism.isAlive()) {
                        organisms_statistics.nDead++;
                        continue;
                    }

                    switch (organism.getOrganismType())
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
