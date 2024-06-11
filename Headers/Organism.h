#pragma once

// Character representation of Organism Types
#define ORGANISM_DEAD '+'
#define ORGANISM_ALGE '*'
#define ORGANISM_FUNGUS '#'
#define ORGANISM_BACTERIA '@'

// Alge predefined settings
#define ALGE_MIN_LIVE_SPAN 5
#define ALGE_MAX_LIVE_SPAN 10
#define ALGE_REPRODUCTION_COST 2
#define ALGE_MEAL_LIMIT 6

// Fungus predefined settings
#define FUNGUS_MIN_LIVE_SPAN 40
#define FUNGUS_MAX_LIVE_SPAN 60
#define FUNGUS_REPRODUCTION_COST 3
#define FUNGUS_MEAL_LIMIT 30

// Bacteria predefined settings
#define BACTERIA_MIN_LIVE_SPAN 25
#define BACTERIA_MAX_LIVE_SPAN 40
#define BACTERIA_REPRODUCTION_COST 3
#define BACTERIA_MEAL_LIMIT 10

enum class OrganismType
{
    Alge,
    Fungus,
    Bacteria
};

class Organism
{
    size_t m_age = 0;
    size_t m_nMeals = 0;
    bool m_isHungry = true;
    OrganismType m_organismType = OrganismType::Alge;

public:
    Organism(OrganismType organismType, size_t age)
    {
        m_organismType = organismType;
        m_age = age;
    }

    bool IsAlive() const
    {
        return m_age != 0;
    }

    bool IsFed() const
    {
        return !m_isHungry;
    }

    bool CanReproduce() const
    {
        return m_nMeals >= getReproductionCost(m_organismType);
    }

    size_t GetAge() const
    {
        return m_age;
    }

    OrganismType GetType() const
    {
        return m_organismType;
    }

    // Age organism by one step
    void Age()
    {
        if (IsAlive())
            m_age--;
    }

    void Feed()
    {
        m_nMeals++;

        if (m_nMeals > getMealLimit(m_organismType))
            m_isHungry = false;
    }

    void Reproduce()
    {
        m_nMeals -= getReproductionCost(m_organismType);
    }

private:
    static size_t getMinAge(OrganismType organismType)
    {
        switch (organismType)
        {
        case OrganismType::Alge:
            return ALGE_MIN_LIVE_SPAN;
            break;
        case OrganismType::Fungus:
            return FUNGUS_MIN_LIVE_SPAN;
            break;
        case OrganismType::Bacteria:
            return BACTERIA_MIN_LIVE_SPAN;
            break;
        default:
            throw;
            break;
        }
    }

    static size_t getMaxAge(OrganismType organismType)
    {
        switch (organismType)
        {
        case OrganismType::Alge:
            return ALGE_MAX_LIVE_SPAN;
            break;
        case OrganismType::Fungus:
            return FUNGUS_MAX_LIVE_SPAN;
            break;
        case OrganismType::Bacteria:
            return BACTERIA_MAX_LIVE_SPAN;
            break;
        default:
            throw;
            break;
        }
    }

    static size_t getMealLimit(OrganismType organismType)
    {
        switch (organismType)
        {
        case OrganismType::Alge:
            return ALGE_MEAL_LIMIT;
            break;
        case OrganismType::Fungus:
            return FUNGUS_MEAL_LIMIT;
            break;
        case OrganismType::Bacteria:
            return BACTERIA_MEAL_LIMIT;
            break;
        default:
            throw;
            break;
        }
    }

    static size_t getReproductionCost(OrganismType organismType)
    {
        switch (organismType)
        {
        case OrganismType::Alge:
            return ALGE_REPRODUCTION_COST;
        case OrganismType::Fungus:
            return FUNGUS_REPRODUCTION_COST;
        case OrganismType::Bacteria:
            return BACTERIA_REPRODUCTION_COST;
        default:
            throw;
            break;
        }
    }

public:
    static Organism Random(OrganismType organismType)
    {
        RandomGenerator *generator = RandomGenerator::GetGenerator();
        size_t age = generator->GenerateRange(Organism::getMinAge(organismType), Organism::getMaxAge(organismType));

        return Organism(organismType, age);
    }

    static Organism Random()
    {
        RandomGenerator *generator = RandomGenerator::GetGenerator();
        bool isDead = generator->GenerateBoolean();
        OrganismType organismType = (OrganismType)generator->GenerateRange(0, 2);
        size_t age = 0;

        if (!isDead)
        {
            age = generator->GenerateRange(Organism::getMinAge(organismType), Organism::getMaxAge(organismType));
        }

        return Organism(organismType, age);
    }

    friend std::ostream &operator<<(std::ostream &os, const Organism &organism);
};

std::ostream &operator<<(std::ostream &os, const Organism &organism)
{
    char representation = ' ';

    if (!organism.IsAlive())
    {
        representation = ORGANISM_DEAD;
    }
    else
    {
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
            // unreachable
            throw;
        }
    }

    os << representation;
    return os;
}