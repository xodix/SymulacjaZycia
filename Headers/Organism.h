#pragma once

#define DEFAULT_AGE 10

enum class OrganismType {
	Alge,
	Fungus,
	Bacteria
};

class Organism {
	size_t m_age = 0;
	OrganismType m_organismType = OrganismType::Alge;

public:
	Organism::Organism(OrganismType organismType, size_t age = DEFAULT_AGE) {
		m_organismType = organismType;
		m_age = age;
	}

	inline bool isAlive() const {
		return m_age != 0;
	}

	// Age organism by one step
	void age() {
		if (isAlive())
			m_age--;
	}

	static Organism random() {
		static std::random_device rd;
		std::uniform_int_distribution<unsigned int> dist(0, 5);
		unsigned int choice = dist(rd);

		return Organism((OrganismType)(choice % 3), (choice >= 3) ? choice : 0);
	}

	friend std::ostream& operator<<(std::ostream& os, const Organism& organism);
};

std::ostream& operator<<(std::ostream& os, const Organism& organism)
{
	char representation = ' ';

	if (!organism.isAlive())
		representation = '+';

	switch (organism.m_organismType)
	{
	case OrganismType::Alge:
		representation = '*';
	case OrganismType::Fungus:
		representation =  '#';
	case OrganismType::Bacteria:
		representation = '@';
	default:
		// unrechable
		throw;
	}

	os << representation;
	return os;
}
