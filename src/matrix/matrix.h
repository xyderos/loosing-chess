#pragma once
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <fstream>

template <class T> class matrix {
    public:
	explicit matrix(const size_t n)
	{
		this->m_rows = n;
		this->m_cols = n;
		n > 0 ? this->m_vec = new T[n * n] { nullptr } :
			this->m_vec = new T[n * n];
	}

	matrix()
	{
		this->m_rows = 0;
		this->m_cols = 0;
		this->m_vec = new T[0];
	}

	matrix(const size_t n, const size_t m)
	    : m_rows(n)
	    , m_cols(m)
	    , m_capacity(n * m)
	    , m_vec(new T[m_capacity])
	{

		for (size_t i = 0; i < m_capacity; i++) {
			m_vec[i] = T();
		}
	}

	matrix(const matrix &other)
	    : m_rows(other.m_rows)
	    , m_cols(other.m_cols)
	    , m_capacity(m_rows * m_cols)
	    , m_vec(new T[m_capacity])
	{
		for (size_t i = 0; i < m_capacity; i++) {
			m_vec[i] = other[i];
		}
	}

	matrix(matrix &&other) noexcept
	    : m_rows(other.m_rows)
	    , m_cols(other.m_cols)
	    , m_capacity(m_rows * m_cols)
	    , m_vec(other.m_vec)
	{
		other.m_vec = nullptr;
		other.m_capacity = 0;
	}

	matrix(std::initializer_list<T> list)
	{
		if (floor(sqrt(list.size())) != sqrt(list.size())) {
			throw std::out_of_range("sqrt");
		}

		m_rows = sqrt(list.size());
		m_cols = sqrt(list.size());
		m_capacity = list.size();
		m_vec = new T[m_capacity];
		int i = 0;
		for (auto it = list.begin(); it < list.end(); ++it) {
			m_vec[i] = *it;
			++i;
		}
	}

	auto get(const size_t x, const size_t y) -> T
	{
		return m_vec[y * m_cols + x];
	}

	void set(const size_t x, const size_t y, T val)
	{
		m_vec[x * m_cols + y] = val;
	}

	~matrix()
	{
		if (this->m_vec) {
			delete[] this->m_vec;
		}
	}

	auto operator[](const size_t rhs) const -> T & { return m_vec[rhs]; }

	auto operator[](const size_t rhs) -> T & { return m_vec[rhs]; }

	auto operator=(const matrix<T> &other) -> matrix<T> &
	{
		if (this == &other) {
			return *this;
		}

		if (m_capacity != other.m_capacity) {
			delete[] m_vec;
			m_vec = nullptr;
			m_capacity = 0;
			m_vec = new T[other.m_capacity];

			m_capacity = other.m_capacity;
			m_rows = other.m_rows;
			m_cols = other.m_cols;
		}

		std::copy(other.m_vec, other.m_vec + other.m_capacity, m_vec);
		return *this;
	}

	auto operator=(matrix<T> &&other) noexcept -> matrix<T> &
	{
		if (this == &other) {
			return *this;
		}

		m_vec = other.m_vec;
		other.m_vec = nullptr;
		m_capacity = other.m_capacity;
		other.m_capacity = 0;
		m_rows = other.m_rows;
		other.m_rows = 0;
		m_cols = other.m_cols;
		other.m_cols = 0;
		return *this;
	}

	auto operator*(const T &rhs) const -> matrix<T> &
	{
		auto *mult = new matrix(m_rows, m_cols);
		for (size_t i = 0; i < m_capacity; i++) {
			mult->m_vec[i] = rhs * m_vec[i];
		}

		return *mult;
	}

	auto operator*(const matrix &rhs) const -> matrix<T> &
	{
		size_t cols_rhs = rhs.get_number_of_cols();
		size_t rows_rhs = rhs.get_number_of_rows();

		if (m_cols != rows_rhs) {
			return nullptr;
		}

		auto *mult = new matrix(m_rows, cols_rhs);

		for (size_t i = 0; i < m_rows; i++) {
			for (size_t j = 0; j < cols_rhs; j++) {
				int sum = 0;
				for (size_t k = 0; k < m_cols; k++) {
					sum = sum +
					    m_vec[i * m_cols + k] *
						rhs[k * cols_rhs + j];
				}
				mult->m_vec[i * cols_rhs + j] = sum;
			}
		}
		return *mult;
	}

	auto operator+(const matrix &rhs) const -> matrix<T> &
	{
		size_t cols_rhs = rhs.get_number_of_cols();
		size_t rows_rhs = rhs.get_number_of_rows();

		if ((m_rows != rows_rhs) || (m_cols != cols_rhs)) {
			return nullptr;
		}

		auto *add = new matrix(m_capacity);

		for (size_t i = 0; i < m_capacity; i++) {
			add->m_vec[i] = m_vec[i] + rhs[i];
		}
		return *add;
	}

	auto operator-(const matrix &rhs) const -> matrix<T> &
	{
		size_t cols_rhs = rhs.get_number_of_cols();
		size_t rows_rhs = rhs.get_number_of_rows();

		if ((m_rows != rows_rhs) || (m_cols != cols_rhs)) {
			return nullptr;
		}

		auto *diff = new matrix(m_capacity);

		for (size_t i = 0; i < m_capacity; i++) {
			diff->m_vec[i] = m_vec[i] - rhs[i];
		}
		return *diff;
	}

	void operator*=(const T &rhs)
	{
		for (size_t i = 0; i < m_capacity; i++) {
			m_vec[i] = rhs * m_vec[i];
		}
	}

	void operator*=(const matrix &rhs)
	{
		size_t cols_rhs = rhs.get_number_of_cols();
		size_t rows_rhs = rhs.get_number_of_rows();

		if (m_cols != rows_rhs) {
			return;
		}

		matrix<T> mult(*this);

		for (size_t i = 0; i < m_rows; i++) {
			for (size_t j = 0; j < cols_rhs; j++) {
				int sum = 0;
				for (size_t k = 0; k < m_cols; k++) {
					sum = sum +
					    mult.m_vec[i * m_cols + k] *
						rhs[k * cols_rhs + j];
				}
				m_vec[i * cols_rhs + j] = sum;
			}
		}
	}

	void operator+=(const matrix &rhs)
	{
		size_t cols_rhs = rhs.get_number_of_cols();
		size_t rows_rhs = rhs.get_number_of_rows();

		if ((m_rows != rows_rhs) || (m_cols != cols_rhs)) {
			return;
		}

		for (size_t i = 0; i < m_capacity; i++) {
			m_vec[i] = m_vec[i] - rhs[i];
		}
	}

	void operator-=(const matrix &rhs)
	{
		size_t cols_rhs = rhs.get_number_of_cols();
		size_t rows_rhs = rhs.get_number_of_rows();

		if ((m_rows != rows_rhs) || (m_cols != cols_rhs)) {
			return;
		}

		for (size_t i = 0; i < m_capacity; i++) {
			m_vec[i] = m_vec[i] - rhs[i];
		}
	}

	[[nodiscard]] auto get_number_of_rows() const -> size_t
	{
		return m_rows;
	}

	[[nodiscard]] auto get_number_of_cols() const -> size_t
	{
		return m_cols;
	}

	void reset()
	{
		for (size_t i = 0; i < m_capacity; i++) {
			m_vec[i] = T();
		}
	}

	auto identity(unsigned int x) -> matrix<T>
	{
		matrix<T> m(x);
		size_t j = 0;
		for (size_t i = 0; i < x * x; i++) {
			if (j == i) {
				m[i] = 1;
				j = j + x + 1;
			} else {
				m[i] = 0;
			}
		}
		return m;
	}

	void insert_row(size_t row)
	{
		size_t newCap = m_capacity + m_cols;
		T *newMatrix = new T[newCap];

		auto k = row * m_cols;
		if (row == 0) {
			for (size_t i = 0; i < m_cols; i++) {
				newMatrix[i] = 0;
			}
			for (size_t i = m_cols; i < newCap; i++) {
				newMatrix[i] = m_vec[i - m_cols];
			}
		} else {
			for (size_t i = 0; i < k; i++) {
				newMatrix[i] = m_vec[i];
			}
			for (size_t i = k; i < k + m_cols; i++) {
				newMatrix[i] = 0;
			}
			for (size_t i = k + m_cols; i < newCap; i++) {
				newMatrix[i] = m_vec[i - m_cols];
			}
		}
		delete[] m_vec;
		m_vec = nullptr;

		m_vec = new T[newCap];
		m_capacity = newCap;
		m_rows += 1;
		std::copy(newMatrix, newMatrix + newCap, m_vec);
		delete[] newMatrix;
		newMatrix = nullptr;
	}

	void append_row(size_t row)
	{
		if ((row < 0) || (row > m_rows)) {
			return;
		}

		size_t newCap = m_capacity + m_cols;

		T *newMatrix = new T[newCap];

		auto k = row * m_cols + m_cols;

		for (size_t i = 0; i < k; i++) {
			newMatrix[i] = m_vec[i];
		}

		for (size_t i = k; i < k + m_cols; i++) {
			newMatrix[i] = 0;
		}
		for (size_t i = k + m_cols; i < newCap; i++) {
			newMatrix[i] = m_vec[i - m_cols];
		}

		delete[] m_vec;
		m_vec = nullptr;

		m_vec = new T[newCap];
		m_capacity = newCap;
		m_rows += 1;
		std::copy(newMatrix, newMatrix + newCap, m_vec);
		delete[] newMatrix;
		newMatrix = nullptr;
	}

	void remove_row(size_t row)
	{
		if ((row < 0) || (row > m_rows)) {
			return;
		}

		size_t newCap = m_capacity - m_cols;

		T *newMatrix = new T[newCap];

		size_t start = row * m_cols;

		size_t finish = start + m_cols;

		for (size_t i = 0; i < m_capacity; i++) {
			if (i < start) {
				newMatrix[i] = m_vec[i];

			} else if (i >= start && i < finish) {
				continue;
			} else {
				newMatrix[i - m_cols] = m_vec[i];
			}
		}

		delete[] m_vec;
		m_vec = nullptr;

		m_vec = new T[newCap];
		m_capacity = newCap;
		m_rows -= 1;
		std::copy(newMatrix, newMatrix + newCap, m_vec);
		delete[] newMatrix;
		newMatrix = nullptr;
	}

	void insert_col(size_t col)
	{
		if ((col < 0) || (col >= m_cols)) {
			return;
		}

		size_t newCap = m_capacity + m_rows;
		T *newMatrix = new T[newCap];

		for (size_t i = 0; i < m_capacity; i++) {
			newMatrix[i] = m_vec[i];
		}
		for (size_t i = m_capacity; i < newCap; i++) {
			newMatrix[i] = 0;
		}
		auto n = m_capacity;
		for (size_t i = 0; i < newCap; i++) {
			if (i == col) {
				for (size_t j = n; j > i; j--) {
					newMatrix[j] = newMatrix[j - 1];
				}
				newMatrix[i] = 0;
				col += m_cols + 1;
				n++;
			}
		}

		delete[] m_vec;
		m_vec = nullptr;

		m_vec = new T[newCap];
		m_capacity = newCap;
		m_cols += 1;
		std::copy(newMatrix, newMatrix + newCap, m_vec);
		delete[] newMatrix;
		newMatrix = nullptr;
	}

	void append_col(size_t col)
	{
		if ((col < 0) || (col >= m_cols)) {
			return;
		}

		size_t newCap = m_capacity + m_rows;
		T *newMatrix = new T[newCap];

		for (size_t i = 0; i < m_capacity; i++) {
			newMatrix[i] = m_vec[i];
		}
		for (size_t i = m_capacity; i < newCap; i++) {
			newMatrix[i] = 0;
		}
		auto n = m_capacity;
		for (size_t i = 0; i < newCap; i++) {
			if (i == col + 1) {
				for (size_t j = n; j > i; j--) {
					newMatrix[j] = newMatrix[j - 1];
				}
				newMatrix[i] = 0;
				col += m_cols + 1;
				n++;
			}
		}

		delete[] m_vec;
		m_vec = nullptr;

		m_vec = new T[newCap];
		m_capacity = newCap;
		m_cols += 1;
		std::copy(newMatrix, newMatrix + newCap, m_vec);
		delete[] newMatrix;
		newMatrix = nullptr;
	}

	void remove_col(size_t col)
	{
		if ((col < 0) || (col >= m_cols)) {
			return;
		}

		size_t newCap = m_capacity - m_rows;
		T *newMatrix = new T[newCap];

		for (size_t i = 0; i < m_capacity; i++) {
			if (i == col) {
				for (size_t j = i; j < m_capacity; j++) {
					m_vec[j] = m_vec[j + 1];
				}
				col += m_cols - 1;
			}
		}

		for (size_t i = 0; i < newCap; i++) {
			newMatrix[i] = m_vec[i];
		}

		delete[] m_vec;
		m_vec = nullptr;

		m_vec = new T[newCap];
		m_capacity = newCap;
		m_cols -= 1;
		std::copy(newMatrix, newMatrix + newCap, m_vec);
		delete[] newMatrix;
		newMatrix = nullptr;
	}

	using it = T *;

	auto begin() -> it { return &m_vec[0]; }
	auto end() -> it { return &m_vec[m_capacity]; }

	friend auto operator<<(std::ostream &out, const matrix &m)
	    -> std::ostream &
	{
		for (size_t i = 1; i <= m.m_capacity; i++) {
			out << m.m_vec[i - 1];
			if (i % m.get_number_of_cols() == 0) {
				out << std::endl;
			}
		}
		return out;
	}

	friend auto operator>>(std::istream &in, matrix &m) -> std::istream &
	{
		for (size_t i = 0; i < m.m_capacity; i++) {
			if (!(in >> m.m_vec[i])) {
				return in;
			}
		}
		return in;
	}

    private:
	size_t m_rows {};
	size_t m_cols {};
	size_t m_capacity {};
	T *m_vec;
};
