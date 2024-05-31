#pragma once

#define DEFAULT_AGE 10

enum class OrganismType {
	Alge,
	Fungus,
	Bacteria
};

class Organism {
protected:
	size_t m_age = 0;
	OrganismType m_organismType;

public:
	Organism::Organism(OrganismType organismType, size_t age = DEFAULT_AGE) {
		m_organismType = organismType;
		m_age = age;
	}

	inline bool isAlive() {
		return m_age == 0;
	}

	const char representation() {
		if (!isAlive()) {
			return '+';
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

		return Organism((OrganismType)(choice % 3), (choice >= 3) ? choice : 0);
	}
};
