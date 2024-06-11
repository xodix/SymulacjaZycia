#pragma once
#include <random>

// Singleton for pseudorandom number generation.
class RandomGenerator
{
	std::random_device *m_rd = nullptr;
	static RandomGenerator *s_instance;

	// Create the instance of std::random_device that will last till program completion.
	RandomGenerator()
	{
		m_rd = new std::random_device();
	}

public:
	// Get the instance of the singleton.
	static RandomGenerator *GetGenerator()
	{
		if (RandomGenerator::s_instance == nullptr)
		{
			RandomGenerator::s_instance = new RandomGenerator();
			return RandomGenerator::s_instance;
		}
		else
		{
			return RandomGenerator::s_instance;
		}
	}

	// Generate a random integer in <from, to> range.
	size_t GenerateRange(size_t from, size_t to) const
	{
		if (from == to)
			return from;

		std::uniform_int_distribution<int> dist(from, to);

		return dist(*m_rd);
	}

	// Generate a random boolean.
	bool GenerateBoolean() const
	{
		std::uniform_int_distribution<short> dist(0, 1);

		return dist(*m_rd) == 0;
	}

	// Generate a random boolean that has a different chance of beeing true than false.
	bool GenerateWeightedBoolean(size_t trueWeight, size_t falseWeight) const
	{
		if (trueWeight == falseWeight)
			return GenerateBoolean();

		std::uniform_int_distribution<int> dist(1, trueWeight + falseWeight);
		size_t weightedResult = (size_t)dist(*m_rd);
		return weightedResult <= trueWeight;
	}
};

RandomGenerator *RandomGenerator::s_instance = nullptr;
