#pragma once
#include "Rows.h"

// Immediate area around the cell.
template <typename T>
class Vicinity
{
	// Maximum of 8 T*, less if on corners.
	T *m_contents[8];
	size_t m_length = 0;

	inline bool isTopRow(size_t i, size_t _j) const
	{
		return i == 0;
	}

	inline bool isBottomRow(Rows<T> &cells, size_t i, size_t _j) const
	{
		return i == cells.ColumnLength() - 1;
	}

	inline bool isFirstColumn(size_t _i, size_t j) const
	{
		return j == 0;
	}

	inline bool isLastColumn(Rows<T> &cells, size_t _i, size_t j) const
	{
		return j == cells.RowLength() - 1;
	}

	// Add a selected row without causing std::range_exception
	void addRow(Rows<T> &cells, size_t row_index, size_t i, size_t j) noexcept
	{
		if (row_index != i)
		{
			m_contents[m_length++] = &cells[row_index][j];
		}

		if (isFirstColumn(i, j))
		{
			m_contents[m_length++] = &cells[row_index][j + 1];
		}
		else if (isLastColumn(cells, i, j))
		{
			m_contents[m_length++] = &cells[row_index][j - 1];
		}
		else
		{
			m_contents[m_length++] = &cells[row_index][j - 1];
			m_contents[m_length++] = &cells[row_index][j + 1];
		}
	}

public:
	Vicinity(Rows<T> &cells, size_t i, size_t j) noexcept
	{
		addRow(cells, i, i, j);

		if (isTopRow(i, j))
		{
			addRow(cells, i + 1, i, j);
		}
		else if (isBottomRow(cells, i, j))
		{
			addRow(cells, i - 1, i, j);
		}
		else
		{
			addRow(cells, i - 1, i, j);
			addRow(cells, i + 1, i, j);
		}
	}

	size_t Length() const
	{
		return m_length;
	}

	T *operator[](size_t index) const
	{
		if (index > m_length)
			throw std::range_error("Index out of bounds");

		return m_contents[index];
	}
};
