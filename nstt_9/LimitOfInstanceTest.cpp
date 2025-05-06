#include <iostream>

#include "LimitOfInstance.hpp"

class Foo : public LimitedInstance<Foo, 3> {
public:
    Foo() { std::cout << "Create foo" << std::endl; }
};

int main() {
    try {
        Foo a;
        Foo b;
        Foo c;
        Foo d;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}