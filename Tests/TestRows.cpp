#include <iostream>
#include "../Headers/Rows.h"
#include "TestingUtilities.h"

int test_initialize_empty() {
	try {
		// m_contents = nullptr colLen = rowLen = 0
		Rows<int> rows = Rows<int>();

		// This has to throw an exception.
		rows[0][0] = 10;
		return EXIT_FAILURE;
	}
	catch (const std::exception& e) {
		return EXIT_SUCCESS;
	}
}

int test_initialize() {
	try {
		// m_contents = nullptr colLen = rowLen = 0
		Rows<int> rows = Rows<int>(1,2);
		
		if (rows.columnLength() != 1)
			return EXIT_FAILURE;
		if (rows.rowLength() != 2)
			return EXIT_FAILURE;

		return EXIT_SUCCESS;
	}
	catch (const std::exception& e) {
		return EXIT_FAILURE;
	}

}

int test_read_write() {
	try {
		// m_contents = nullptr colLen = rowLen = 0
		Rows<int> rows = Rows<int>(2,2);

		// This has to throw an exception.
		rows[0][0] = 1;
		rows[0][1] = 2;
		rows[1][0] = 3;
		rows[1][1] = 4;
		if (rows[0][0] != 1)
			return EXIT_FAILURE;
		if (rows[0][1] != 2)
			return EXIT_FAILURE;
		if (rows[1][0] != 3)
			return EXIT_FAILURE;
		if (rows[1][1] != 4)
			return EXIT_FAILURE;

		return EXIT_SUCCESS;
	}
	catch (const std::exception& e) {
		return EXIT_FAILURE;
	}
}

int main(int argc, const char* argv[]) {
	test("empty_initialize", test_initialize_empty);
	test("initialize", test_initialize);
	test("read_write", test_read_write);
}
