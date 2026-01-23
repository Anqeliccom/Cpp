#include <iostream>

#include "isPrime.hpp"

int main() {
    std::cout << getNthPrime<1>::value << "\n";  // 2
    std::cout <<  getNthPrime<5>::value << "\n"; // 11
    std::cout << getNthPrime<51>::value << "\n"; // 233
    return 0;
}
