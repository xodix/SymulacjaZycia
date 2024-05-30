#pragma once

#define DEFAULT_AGE 10

enum class OrganismType {
	Alge,
	Fungus,
	Bacteria
};

class Organism {
protected:
	bool m_alive = false;
	size_t m_age = 0;
	OrganismType m_organismType;

public:
	Organism() {};
	Organism::Organism(OrganismType organismType, size_t age = DEFAULT_AGE, bool alive = true) {
		m_organismType = organismType;
		m_age = age;
		m_alive = alive;
	}

	bool isAlive() {
		return m_alive;
	}

	const char representation() {
		if (!isAlive()) {
			return 'X';
		}

		switch (m_organismType)
		{
		case OrganismType::Alge:
			return '*';
		case OrganismType::Fungus:
			return '#';
		case OrganismType::Bacteria:
			return '@';
		default:
			// unrechable
			throw;
		}
	}

	static Organism random() {
		static std::random_device rd;
		std::uniform_int_distribution<unsigned int> dist(0, 5);
		unsigned int choice = dist(rd);

		Organism organism = Organism();
		organism.m_alive = (choice >= 3) ? false : true;
		organism.m_age = DEFAULT_AGE;
		organism.m_organismType = (OrganismType)(choice % 3);

		return organism;
	}
};
