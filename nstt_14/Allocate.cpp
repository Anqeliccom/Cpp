#include <memory>
#include <cassert>

template<size_t SIZE, typename... Types>
void allocate(void* memory, Types... args) requires ((std::is_copy_constructible<Types>::value && ...) && (SIZE >= (sizeof(Types) + ...))) {
    char* ptr = static_cast<char*>(memory);

    auto alloc = [&](const auto& arg) {
        using Type = std::remove_reference_t<decltype(arg)>;
        new (ptr) Type(arg);
        ptr += sizeof(Type);
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