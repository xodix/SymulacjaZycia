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
#define FUNGUS_MAX_LIVE_SPAN  60
#define FUNGUS_REPRODUCTION_COST 3
#define FUNGUS_MEAL_LIMIT 30

// Bacteria predefined settings
#define BACTERIA_MIN_LIVE_SPAN 25
#define BACTERIA_MAX_LIVE_SPAN  40
#define BACTERIA_REPRODUCTION_COST 3
#define BACTERIA_MEAL_LIMIT 10

enum class OrganismType {
    Alge,
    Fungus,
    Bacteria
};

class Organism {
    size_t m_age = 0;
    size_t m_nMeals = 0;
    bool m_isHungry = true;
    OrganismType m_organismType = OrganismType::Alge;

public:
    Organism(OrganismType organismType, size_t age) {
        m_organismType = organismType;
        m_age = age;
    }

    bool isAlive() const {
        return m_age != 0;
    }

    // Age organism by one step
    void age() {
        if (isAlive())
            m_age--;
    }

    void increaseMelas() {
        m_nMeals++;

        if (m_nMeals > getMealLimit()) {
            m_isHungry = false;
        }
    }

    bool isFed() const {
        return !m_isHungry;
    }

    // TODO: Should be static.
    size_t getMealLimit() const {
        switch (m_organismType)
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

    size_t getAge() const {
        return m_age;
    }

    OrganismType getType() const {
        return m_organismType;
    }

    bool canReproduce() {
        switch (m_organismType)
        {
        case OrganismType::Alge:
            return m_nMeals >= ALGE_REPRODUCTION_COST;
        case OrganismType::Fungus:
            return m_nMeals >= FUNGUS_REPRODUCTION_COST;
        case OrganismType::Bacteria:
            return m_nMeals >= BACTERIA_REPRODUCTION_COST;
        default:
            throw;
            break;
        }
    }

    void reproduce() {
        switch (m_organismType)
        {
        case OrganismType::Alge:
            m_nMeals -= ALGE_REPRODUCTION_COST;
            break;
        case OrganismType::Fungus:
            m_nMeals -= FUNGUS_REPRODUCTION_COST;
            break;
        case OrganismType::Bacteria:
            m_nMeals -= BACTERIA_REPRODUCTION_COST;
            break;
        default:
            throw;
            break;
        }
    }

    static size_t getMinAge(OrganismType organismType) {
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

    static size_t getMaxAge(OrganismType organismType) {
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

    static Organism random() {
        RandomGenerator* generator = RandomGenerator::GetGenerator();
        bool isDead = generator->GenerateBoolean();
        OrganismType organismType = (OrganismType)generator->GenerateRange(0, 2);
        size_t age = 0;

        if (!isDead) {
           age = generator->GenerateRange(Organism::getMinAge(organismType), Organism::getMaxAge(organismType));
        }

        return Organism(organismType, age);
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