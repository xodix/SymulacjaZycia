#pragma once
#include <stdexcept>
#include <algorithm>
/// A view over contents of Rows data structure. It is only a view and thus it does not own any data.
template <typename T>
class Row {
	T* contents;
	size_t m_length;

public:
	Row(T* ptr, size_t length) {
		contents = ptr;
		m_length = length;
	}

	T& operator[](size_t index) {
		if (index >= m_length)
			throw std::range_error("Item index out of range!");

		return contents[index];
	}
};

/// Abstraction that exposes 1D array as a 2D array.
template <typename T>
class Rows {
	// One continous array of data for better caching.
	T* m_rows = nullptr;

	// Length of a single column. [[1,2], [3,4], [5,6]] would have colLen of 3.
	size_t m_colLen = 0;

	// Length of a single row. [[1,2], [3,4], [5,6]] would have rowLen of 2.
	size_t m_rowLen = 0;

public:
	Rows() {};

	Rows(size_t colLen, size_t rowLen) {
		m_colLen = colLen;
		m_rowLen = rowLen;
		m_rows = new T[colLen * rowLen];
	}

	void construct(size_t colLen, size_t rowLen) {
		m_colLen = colLen;
		m_rowLen = rowLen;
		m_rows = new T[colLen * rowLen];
	}

	size_t columnLength() const {
		return m_colLen;
	}

	size_t rowLength() const {
		return m_rowLen;
	}

	Row<T> operator[](size_t index) {
		if (index >= m_colLen)
			throw std::range_error("Column index out of range!");

		return Row<T>(&m_rows[index * m_rowLen], m_rowLen);
	}

	~Rows() {
		delete[] m_rows;
	}
};
