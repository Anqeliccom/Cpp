#ifndef MATRICES_HPP
#define MATRICES_HPP

#include <iostream>
#include <vector>

class Matrix {
private:
    size_t size;
    double** data;

    class Row {
        size_t row_size;
        double* row_data;
    public:
        Row(double* data, size_t size) : row_data(data), row_size(size) {}
        double& operator[](size_t index);
    };

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

    Row operator[](size_t index);

    void print() const;
    size_t getSize() const;
};

#endif // MATRICES_HPP
