#pragma once
#include <stdexcept>
#include <algorithm>

// A view over contents of Rows data structure. It is only a view and thus it does not own any data.
template <typename T>
class Row
{
	T *m_contents;
	size_t m_length;

public:
	Row(T *ptr, size_t length) : m_contents(ptr), m_length(length) {}

	T &operator[](size_t index) noexcept(false)
	{
		if (index >= m_length)
			throw std::range_error("Item index out of range!");

		return m_contents[index];
	}
};

// Abstraction that exposes 1D array as a 2D array.
template <typename T>
class Rows
{
	// One continuous array of data for better cache locality.
	T *m_array = nullptr;

	// Length of a single column. [[1,2], [3,4], [5,6]] would have colLen of 3.
	size_t m_colLen = 0;

	// Length of a single row. [[1,2], [3,4], [5,6]] would have rowLen of 2.
	size_t m_rowLen = 0;

public:
	Rows(size_t colLen, size_t rowLen)
	{
		if (colLen == 0 || rowLen == 0)
			throw std::length_error("Cannot initialize Rows<T> with the col or row length of 0.");
		m_colLen = colLen;
		m_rowLen = rowLen;
		m_array = new T[colLen * rowLen];
	}

	inline size_t ColumnLength() const
	{
		return m_colLen;
	}

	inline size_t RowLength() const
	{
		return m_rowLen;
	}

	Row<T> operator[](size_t index) noexcept(false)
	{
		if (index >= m_colLen)
			throw std::range_error("Column index out of range!");

		return Row<T>(&m_array[index * m_rowLen], m_rowLen);
	}

	~Rows()
	{
		delete[] m_array;
	}
};
