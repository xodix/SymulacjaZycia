#pragma once

#define DEFAULT_AGE 10
#define ORGANISM_DEAD '+'
#define ORGANISM_ALGE '*'
#define ORGANISM_FUNGUS '#'
#define ORGANISM_BACTERIA '@'

enum class OrganismType {
    Alge,
    Fungus,
    Bacteria
};

class Organism {
    size_t m_age = DEFAULT_AGE;
    size_t n_meals = 0;
    OrganismType m_organismType = OrganismType::Alge;

public:
    Organism::Organism(OrganismType organismType, size_t age = DEFAULT_AGE) {
        m_organismType = organismType;
        m_age = age;
    }

    inline bool isAlive() const {
        return m_age != 0;
    }

    // TODO: age beeing a verb and a noun may be confusing.
    // Age organism by one step
    void age() {
        if (isAlive())
            m_age--;
    }

    void increaseMelas() {
        n_meals++;
    }

    bool isFed() {
        switch (m_organismType)
        {
        case OrganismType::Alge:
            return n_meals > 10;
            break;
        case OrganismType::Fungus:
            return n_meals > 10;
            break;
        case OrganismType::Bacteria:
            return n_meals > 10;
            break;
        default:
            throw;
            break;
        }
    }

    size_t getAge() {
        return m_age;
    }

    OrganismType getOrganismType() {
        return m_organismType;
    }

    static Organism random() {
        static std::random_device rd;
        std::uniform_int_distribution<unsigned int> dist(0, 5);
        unsigned int choice = dist(rd);

        return Organism((OrganismType)(choice % 3), (choice >= 3) ? choice * 2 : 0);
    }

    friend std::ostream& operator<<(std::ostream& os, const Organism& organism);
};

std::ostream& operator<<(std::ostream& os, const Organism& organism)
{
    char representation = ' ';

    if (!organism.isAlive()) {
        representation = ORGANISM_DEAD;
    }
    else {
        switch (organism.m_organismType)
        {
        case OrganismType::Alge:
            representation = ORGANISM_ALGE;
            break;
        case OrganismType::Fungus:
            representation = ORGANISM_FUNGUS;
            break;
        case OrganismType::Bacteria:
            representation = ORGANISM_BACTERIA;
            break;
        default:
            // unrechable
            throw;
        }
    }

    os << representation;
    return os;
}