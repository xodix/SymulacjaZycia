#pragma once
#include "Rows.h"
// Immidiet area around the cell.
template <typename T>
class Vicinity {
	// Maximum of 8, less if on the corner.
	// ! Might need to go onto the heap
	T* m_contents[8];
	size_t m_length = 0;

	/*
		TODO:
		This system is overly complicated! Yet I cannot find any other way of ensuring we do not touch data not owned by the grid.
	*/

	inline bool isTopRow(size_t i, size_t j) {
		return i == 0;
	}

	inline bool isBottomRow(Rows<T>& cells, size_t i, size_t j) {
		return i == cells.columnLength - 1;
	}

	inline bool isFirstColumn(size_t i, size_t j) {
		return j == 0;
	}

	inline bool isLastColumn(Rows<T>& cells, size_t i, size_t j) {
		return j == cells.rowLength() - 1;
	}

	void addRow(Rows<T>& cells, size_t row_index, size_t i, size_t j) {
		if (row_index != i)
			m_contents[m_length++] = cells[row_index][j];

		if (isFirstColumn(i, j)) {
			m_contents[m_length++] = cells[row_index][j+1];
		}
		else if (isLastColumn(i, j)) {
			m_contents[m_length++] = cells[row_index][j-1];
		}
		else {
			m_contents[m_length++] = cells[row_index][j-1];
			m_contents[m_length++] = cells[row_index][j+1];

		}
	}
public:
	Vicinity(Rows<T>& cells, size_t i, size_t j) {
		addRow(cells, i, i, j);
		if (isTopRow(i, j)) {
			addRow(cells, i+1, i, j);
		}
		else if (isBottomRow(cells, i, j)) {
			addRow(cells, i-1, i, j);
		}
		else {
			addRow(cells, i-1, i, j);
			addRow(cells, i+1, i, j);
		}
	}
};
