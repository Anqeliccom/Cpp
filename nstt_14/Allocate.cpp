#include <memory>
#include <cassert>
#include <iostream>

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
void allocate(void* memory, Types&&... args) requires ((std::is_copy_constructible<Types>::value && ...) && (SIZE >= (compute_total_size<Types...>()))) {
    char* base = static_cast<char*>(memory);
    size_t offset = 0;

    auto alloc = [&](auto&& arg) {
        using Type = std::remove_reference_t<decltype(arg)>;
        offset = align_up<Type>(offset);
        new (base + offset) Type(std::forward<decltype(arg)>(arg));
        offset += sizeof(Type);
    };

    (alloc(std::forward<Types>(args)), ...);
}

int main() {
    struct Struct {
        char c;
        int i;
        Struct(const Struct& other){
            this->c = other.c;
            this->i = other.i;
            std::cout << "copy" << std::endl;
        }
        Struct(char hi, int i){
            this->c = hi;
            this->i = i;
        }
        Struct(Struct&& other){
            this->c = other.c;
            this->i = other.i;
            std::cout << "move" << std::endl;
        }
    };
    Struct str{'S', 25};
    char* buffer = new char[sizeof(int) + sizeof(Struct)];
    allocate<sizeof(int) + sizeof(Struct)>(buffer, 23126, str);
    int* pi = (int*)buffer;
    Struct* ps = (Struct*)(buffer + sizeof(int));

    assert(*pi == 23126);
    assert(ps->c == 'S');
    assert(ps->i == 25);

    delete[] buffer;
    return 0;
}
