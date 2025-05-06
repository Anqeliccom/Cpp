#ifndef LIMITOFINSTANCE_HPP
#define LIMITOFINSTANCE_HPP

#include <stdexcept>

template <typename T>
struct Counter {
    static int objects_created;
    static int objects_alive;

    Counter() {
        ++objects_created;
        ++objects_alive;
    }

    Counter(const Counter&) {
        ++objects_created;
        ++objects_alive;
    }

protected:
    ~Counter() {
        --objects_alive;
    }
};

template <typename T>
int Counter<T>::objects_created = 0;

template <typename T>
int Counter<T>::objects_alive = 0;

template <typename Derived, int limit>
class LimitedInstance : Counter<Derived> {
public:
    LimitedInstance() {
        check_limit();
    }

    LimitedInstance(const LimitedInstance&) {
        check_limit();
    }

private:
    void check_limit() {
        if (Counter<Derived>::objects_alive > limit) {
            throw std::runtime_error("Limit of instances exceeded");
        }
    }
};

#endif // LIMITOFINSTANCE_HPP
