#pragma once

// Exits with EXIT_FAILURE when test_fuction returns EXIT_FAILURE.
void test(const char* test_msg, int (*test_fuction)()) {
	std::cout << "Testing: " << test_msg << ' ';
	int result = test_fuction();
	if (result == EXIT_FAILURE) {
		std::cout << "FAILED" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::cout << "SUCCEEDED" << std::endl;
}

