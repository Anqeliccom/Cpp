#ifndef WRITER_HPP
#define WRITER_HPP

#include "IO.hpp"

class Writer : public virtual IO {
public:
    virtual ~Writer() = default;

    template<typename T>
    void write(const T& value) {
        char buffer[sizeof(T)];
        std::memcpy(buffer, &value, sizeof(T));
        write_bytes(buffer, sizeof(T));
    }

    void write(const std::string& str) {
        size_t len = str.size();
        write(len);
        write_bytes(str.data(), len);
    }

    virtual void write_bytes(const char* buffer, size_t size) = 0;
};

#endif // WRITER_HPP
