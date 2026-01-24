#include <utility>
#include <cassert>

template <typename Checker, typename... Args>
int getIndexOfFirstMatch(Checker check, Args&&... args) {
    int index = 0;
    int result = -1;

    ((result == -1 && check(std::forward<Args>(args)) ? result = index : ++index) || ...);

    return result;
}

int main() {
    auto isEven = [](int x) { return x % 2 == 0; };
    assert(getIndexOfFirstMatch(isEven, 2, 3, 5, 8, 10) == 0);
    assert(getIndexOfFirstMatch(isEven, 1, 3, 5, 7, 9) == -1);

    return 0;
}
