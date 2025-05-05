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

int main() {
    struct Struct {
        char c;
        int i;
    };

    char* buffer = new char[sizeof(int) + sizeof(Struct)];
    allocate<sizeof(int) + sizeof(Struct)>(buffer, 23126, Struct{'S', 25});
    int* pi = (int*)buffer;
    Struct* ps = (Struct*)(buffer + sizeof(int));

    assert(*pi == 23126);
    assert(ps->c == 'S');
    assert(ps->i == 25);

    delete[] buffer;
    return 0;
}