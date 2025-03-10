#ifndef MATRICES_HPP
#define MATRICES_HPP

#include <iostream>
#include <vector>

class Matrix {
private:
    size_t size;
    double** data;

public:
    explicit Matrix(size_t n);
    explicit Matrix(const std::vector<double>& vector);
    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);
    Matrix(Matrix&& other) noexcept;
    Matrix& operator=(Matrix&& other) noexcept;
    ~Matrix();

    explicit operator double() const;

    Matrix operator+(const Matrix& other);
    Matrix& operator+=(const Matrix& other);
    Matrix operator*(const Matrix& other);
    Matrix& operator*=(const Matrix& other);
    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;

    double* operator[](size_t index);

    void print() const;
    size_t getSize() const;
};

#endif // MATRICES_HPP
