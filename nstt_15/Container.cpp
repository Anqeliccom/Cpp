#include <memory>
#include <cassert>

template<typename T>
constexpr size_t align_up(size_t offset) {
    return (offset + alignof(T) - 1) & ~(alignof(T) - 1);
}

template<typename... Types>
constexpr size_t compute_total_size() {
    size_t offset = 0;
    ((offset = align_up<Types>(offset), offset += sizeof(Types)), ...);
    return offset;
}

template<size_t SIZE, typename... Types>
void allocate(void* memory, Types... args) requires ((std::is_copy_constructible<Types>::value && ...) && (SIZE >= (compute_total_size<Types...>()))) {
    char* base = static_cast<char*>(memory);
    size_t offset = 0;

    auto alloc = [&](const auto& arg) {
        using Type = std::remove_reference_t<decltype(arg)>;
        offset = align_up<Type>(offset);
        new (base + offset) Type(arg);
        offset += sizeof(Type);
    };

    (alloc(args), ...);
}

template<typename... Types>
class Container {
    char data[compute_total_size<Types...>()];
    size_t offsets[sizeof...(Types)];

public:
    Container(Types... args) {
        size_t offset = 0;
        size_t i = 0;
        ((offset = align_up<Types>(offset), offsets[i++] = offset, offset += sizeof(Types)), ...);
        allocate<compute_total_size<Types...>()>(data, args...);
    }

    template<typename T>
    T getElement(size_t idx) {
        return *(T*)(data + offsets[idx]);
    }
};

struct Point { int x, y; };

int main() {
    Container<int, char, Point> c(12, 'c', Point{2, 3});
    assert(c.getElement<int>(0) == 12);
    assert(c.getElement<char>(1) == 'c');
    assert(c.getElement<Point>(2).x == 2);
    return 0;
}
