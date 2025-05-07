#ifndef READER_HPP
#define READER_HPP

#include "IO.hpp"

class Reader : public virtual IO {
public:
    virtual ~Reader() = default;

    template<typename T>
    void read(T& value) {
        char buffer[sizeof(T)];
        read_bytes(buffer, sizeof(T));
        std::memcpy(&value, buffer, sizeof(T));
    }

    void read(std::string& str) {
        size_t len;
        read(len);
        char* buffer = new char[len];
        read_bytes(buffer, len);
        str.assign(buffer, len);
        delete[] buffer;
    }

    virtual void read_bytes(char* buffer, size_t size) = 0;
};

#endif // READER_HPP

