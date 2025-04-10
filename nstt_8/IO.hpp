#ifndef IO_HPP
#define IO_HPP

#include <cstring>
#include <string>
#include <stdexcept>

class IO {
public:
    virtual ~IO() = default;
    virtual bool isOpen() const = 0;
    virtual bool eof() const = 0;
    virtual void close() = 0;
};

#endif // IO_HPP