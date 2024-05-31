#include <iostream>
#include "../Headers/Rows.h"
#include "TestingUtilities.h"

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

int test_invalid_access() {
	// This should fail
	try {
		Rows<int> rows = Rows<int>(2,2);

		// 3 is out of range of the 2x2 matrix. So it should throw std::range_error here
		rows[0][3] = 0;

		return EXIT_FAILURE;
	} catch (const std::exception& e) {
		return EXIT_SUCCESS;
	}

}

int main(int argc, const char* argv[]) {
	test("initialize", test_initialize);
	test("out of range access", test_invalid_access);
	test("read & write", test_read_write);
}
