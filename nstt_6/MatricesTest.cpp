#include <cassert>

#include "Matrices.hpp"

void testMatrix() {
    //
    std::vector<double> diagonal = {10, 20, 30};
    Matrix m1(diagonal);
    assert(m1.getSize() == 3);
    m1.print();

    //
    Matrix m2(3);
    m2[0][0] = 40;
    m2[1][1] = 50;
    m2[2][2] = 60;

    Matrix m3 = m1 + m2;
    m3.print();
    assert(m3[0][0] == 50);

    //
    Matrix m4 = m1 * m2;
    m4.print();
    assert(m4[0][0] == 400);

    //
    double sum = static_cast<double>(m1);
    assert(sum == 60);

    //
    assert(m1 == m1);
    assert(m1 != m2);
}

int main() {
    testMatrix();
    std::cout << "Tests passed" << std::endl;
    return 0;
}

