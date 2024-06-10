#pragma once

// Singleton for pseudorandom number generation.
class RandomGenerator{
	std::random_device* rd;

public:

	RandomGenerator() {
		// Initializing static variable only once.
		if (RandomGenerator::rd == nullptr) {
			RandomGenerator::rd = new std::random_device();
		}
	}

	int generateRange(int from, int to) {
		if (from == to)
			return from;

		std::uniform_int_distribution<int> dist(from, to);

		return dist(*rd);
	}

	bool generateBoolean() {
		std::uniform_int_distribution<short> dist(0, 1);

		return dist(*rd) == 0;
	}

	bool generateWeightedBoolean(size_t trueWeight, size_t falseWeight) {
		if (trueWeight == falseWeight)
			return generateBoolean();

		std::uniform_int_distribution<int> dist(1, trueWeight + falseWeight);
		size_t weightedResult = (size_t)dist(*rd);
		return weightedResult <= trueWeight;
	}
};

