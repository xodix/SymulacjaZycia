#pragma once

#define CELL_EMPTY '_'

// Single cell in a grid.
class Cell
{
    // Can contain Organism (dead or alive) or nullopt (empty) and is stored on the stack.
    std::optional<Organism> m_contents = std::nullopt;

    void feedAlge(Vicinity<Cell> &_vicinity)
    {
        m_contents.value().Feed();
    }

    void feedFungus(Vicinity<Cell> &vicinity)
    {
        Cell *dead[8]{};
        size_t nDead = 0;

        for (size_t i = 0; i < vicinity.Length(); i++)
        {
            if (vicinity[i]->m_contents.has_value())
            {
                if (!vicinity[i]->m_contents.value().IsAlive())
                {
                    dead[nDead++] = vicinity[i];
                }
            }
        }

        RandomGenerator *generator = RandomGenerator::GetGenerator();

        if (nDead)
        {
            size_t randomCell = generator->GenerateRange(0, nDead - 1);
            dead[randomCell]->m_contents = std::nullopt;
            m_contents.value().Feed();
        }
    }

    void feedBacteria(Vicinity<Cell> &vicinity)
    {
        Cell *cells[8]{};
        size_t nAlge = 0;
        size_t nBacteria = 0;

        for (size_t i = 0; i < vicinity.Length(); i++)
        {
            if (vicinity[i]->m_contents.has_value())
            {
                Organism &currOrganism = vicinity[i]->m_contents.value();
                switch (currOrganism.GetType())
                {
                case OrganismType::Alge:
                    cells[nAlge++] = vicinity[i];
                    break;
                case OrganismType::Bacteria:
                    cells[7 - nBacteria] = vicinity[i];
                    nBacteria++;
                    break;
                }
            }
        }

        RandomGenerator *generator = RandomGenerator::GetGenerator();
        if (nAlge)
        {
            size_t randomCell = generator->GenerateRange(0, nAlge - 1);
            cells[randomCell]->m_contents = std::nullopt;
            m_contents.value().Feed();
        }
        else if (nBacteria)
        {
            size_t randomCell = generator->GenerateRange(8 - nBacteria, 7);
            cells[randomCell]->m_contents = std::nullopt;
            m_contents.value().Feed();
        }
    }

public:
    Cell() {}

    Cell(Organism organism) : m_contents(organism) {}

    std::optional<Organism> &GetContents()
    {
        return m_contents;
    }

    void Step(Vicinity<Cell> vicinity)
    {
        if (!m_contents.has_value())
            return;

        Organism &organism = m_contents.value();
        if (!organism.IsAlive())
            return;

        if (!organism.IsFed())
        {
            switch (organism.GetType())
            {
            case OrganismType::Alge:
                feedAlge(vicinity);
                break;
            case OrganismType::Fungus:
                feedFungus(vicinity);
                break;
            case OrganismType::Bacteria:
                feedBacteria(vicinity);
                break;
            default:
                throw;
                break;
            }
        }

        Cell *emptyCells[8]{};
        size_t nEmpty = 0;
        for (size_t i = 0; i < vicinity.Length(); i++)
        {
            if (!vicinity[i]->m_contents.has_value())
            {
                emptyCells[nEmpty++] = vicinity[i];
            }
        }
        RandomGenerator *generator = RandomGenerator::GetGenerator();

        if (nEmpty && organism.IsFed())
        {
            size_t randomCell = generator->GenerateRange(0, nEmpty - 1);
            // Reproduce
            if (organism.CanReproduce())
            {
                emptyCells[randomCell]->m_contents = Organism::Random(organism.GetType());

                organism.Reproduce();
            }

            // Travel
            else if (organism.GetType() == OrganismType::Fungus || organism.GetType() == OrganismType::Bacteria)
            {
                emptyCells[randomCell]->m_contents = m_contents.value();
                m_contents = std::nullopt;
            }
        }

        organism.Age();
    }

    static Cell Random()
    {
        RandomGenerator *generator = RandomGenerator::GetGenerator();
        // Empty cell has equal probability to every other type of cell.
        bool is_empty = generator->GenerateWeightedBoolean(1, 5);

        if (is_empty)
            return Cell();

        Organism organism = Organism::Random();
        return Cell(organism);
    }

    friend std::ostream &operator<<(std::ostream &os, const Cell &cell);
    friend std::istream &operator>>(std::istream &os, Cell &cell);
};

std::ostream &operator<<(std::ostream &os, const Cell &cell)
{
    if (cell.m_contents.has_value())
    {
        os << cell.m_contents.value();
    }
    else
    {
        os << CELL_EMPTY;
    }

    return os;
}

std::istream &operator>>(std::istream &stream, Cell &cell)
{
    char cellRepresentation = CELL_EMPTY;
    stream >> cellRepresentation;

    if (cellRepresentation == CELL_EMPTY)
    {
        cell.m_contents = std::nullopt;
    }
    else
    {
        RandomGenerator *generator = RandomGenerator::GetGenerator();
        switch (cellRepresentation)
        {
        case ORGANISM_DEAD:
            cell.m_contents = Organism(OrganismType::Alge, 0);
            break;
        case ORGANISM_ALGE:
            cell.m_contents = Organism::Random(OrganismType::Alge);
            break;
        case ORGANISM_FUNGUS:
            cell.m_contents = Organism::Random(OrganismType::Fungus);
            break;
        case ORGANISM_BACTERIA:
            cell.m_contents = Organism::Random(OrganismType::Bacteria);
            break;
        default:
            // unreachable
            throw;
        }
    }

    return stream;
}

struct OrganismsStatistics
{
    size_t nAlge = 0;
    size_t nFungus = 0;
    size_t nBacteria = 0;
    size_t nDead = 0;
};

class Grid
{
    Rows<Cell> m_cells;

public:
    Grid(size_t colLen, size_t rowLen) : m_cells(colLen, rowLen) {}

    void FillFile(std::ifstream &file)
    {
        for (size_t i = 0; i < m_cells.ColumnLength(); i++)
        {
            for (size_t j = 0; j < m_cells.RowLength(); j++)
            {
                file >> m_cells[i][j];
            }
        }
    }

    void FillRandom()
    {
        for (size_t i = 0; i < m_cells.ColumnLength(); i++)
            for (size_t j = 0; j < m_cells.RowLength(); j++)
            {
                m_cells[i][j] = Cell::Random();
            }
    }

    void Step()
    {
        for (size_t i = 0; i < m_cells.ColumnLength(); i++)
        {
            for (size_t j = 0; j < m_cells.RowLength(); j++)
            {
                Cell &currCell = m_cells[i][j];
                auto vicinity = Vicinity<Cell>(m_cells, i, j);
                currCell.Step(vicinity);
            }
        }
    }

    OrganismsStatistics GetOrganismsStatistics()
    {
        OrganismsStatistics organismsStatistics = OrganismsStatistics();

        for (size_t i = 0; i < m_cells.ColumnLength(); i++)
        {
            for (size_t j = 0; j < m_cells.RowLength(); j++)
            {
                std::optional<Organism> &currCell = m_cells[i][j].GetContents();
                if (currCell.has_value())
                {
                    Organism &organism = currCell.value();
                    if (!organism.IsAlive())
                    {
                        organismsStatistics.nDead++;
                        continue;
                    }

                    switch (organism.GetType())
                    {
                    case OrganismType::Alge:
                        organismsStatistics.nAlge++;
                        break;

                    case OrganismType::Fungus:
                        organismsStatistics.nFungus++;
                        break;

                    case OrganismType::Bacteria:
                        organismsStatistics.nBacteria++;
                        break;

                    default:
                        throw;
                        break;
                    }
                }
            }
        }

        return organismsStatistics;
    }

    friend std::ostream &operator<<(std::ostream &os, Grid &grid);
    friend std::istream &operator>>(std::istream &stream, Grid &grid);
};

std::ostream &operator<<(std::ostream &os, Grid &grid)
{
    for (size_t i = 0; i < grid.m_cells.ColumnLength(); i++)
    {
        for (size_t j = 0; j < grid.m_cells.RowLength(); j++)
            os << grid.m_cells[i][j];

        os << '\n';
    }

    return os;
}

std::istream &operator>>(std::istream &stream, Grid &grid)
{
    for (size_t i = 0; i < grid.m_cells.ColumnLength(); i++)
    {
        for (size_t j = 0; j < grid.m_cells.RowLength(); j++)
        {
            stream >> grid.m_cells[i][j];
        }
    }

    return stream;
}
