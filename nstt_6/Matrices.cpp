#include "Matrices.hpp"
#include <stdexcept>
#include <iostream>

Matrix::Matrix(size_t n) : size(n), data(new double*[n]) {
    for (size_t i = 0; i < n; ++i) {
        data[i] = new double[n]();
    }
}

Matrix::Matrix(const std::vector<double>& vector)
        : size(vector.size()), data(new double*[size]) {
    for (size_t i = 0; i < size; ++i) {
        data[i] = new double[size]();
        data[i][i] = vector[i];
    }
}

Matrix::Matrix(const Matrix& other) : size(other.size), data(new double*[other.size]) {
    for (size_t i = 0; i < size; ++i) {
        data[i] = new double[size];
        for (size_t j = 0; j < size; ++j) {
            data[i][j] = other.data[i][j];
        }
    }
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        for (size_t i = 0; i < size; ++i) {
            delete[] data[i];
        }
        delete[] data;

        size = other.size;
        data = new double*[size];

        for (size_t i = 0; i < size; ++i) {
            data[i] = new double[size];
            for (size_t j = 0; j < size; ++j) {
                data[i][j] = other.data[i][j];
            }
        }
    }
    return *this;
}

Matrix::Matrix(Matrix&& other) noexcept : size(other.size), data(other.data) {
    other.size = 0;
    other.data = nullptr;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept {
    if (this != &other) {
        for (size_t i = 0; i < size; ++i) {
            delete[] data[i];
        }
        delete[] data;

        size = other.size;
        data = other.data;

        other.size = 0;
        other.data = nullptr;
    }
    return *this;
}

Matrix::~Matrix() {
    if (data) {
        for (size_t i = 0; i < size; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }
}

Matrix::operator double() const {
    double sum = 0;
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            sum += data[i][j];
        }
    }
    return sum;
}

Matrix Matrix::operator+(const Matrix& other) {
    if (size != other.size) {
        throw std::invalid_argument("Matrices must have the same size.");
    }

    Matrix result(size); /////////////////////////
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

Matrix& Matrix::operator+=(const Matrix& other) {
    *this = *this + other;
    return *this;
}

Matrix Matrix::operator*(const Matrix& other) {
    if (size != other.size) {
        throw std::invalid_argument("Matrices must have the same size.");
    }

    Matrix result(size); /////////////////////
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            result.data[i][j] = 0;
            for (size_t k = 0; k < size; ++k) {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}

Matrix& Matrix::operator*=(const Matrix& other) {
    *this = *this * other;
    return *this;
}

bool Matrix::operator==(const Matrix& other) const {
    if (size != other.size) return false;

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            if (data[i][j] != other.data[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& other) const {
    return !(*this == other);
}

Matrix::Row Matrix::operator[](size_t index) {
    if (index >= size) {
        throw std::out_of_range("Row index out of range");
    }
    return Row(data[index], size);
}

double& Matrix::Row::operator[](size_t index) {
    if (index >= row_size) {
        throw std::out_of_range("Column index out of range");
    }
    return row_data[index];
}

void Matrix::print() const {
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

size_t Matrix::getSize() const {
    return size;
}

