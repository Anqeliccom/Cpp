#ifndef READER_STRING_HPP
#define READER_STRING_HPP

#include "../Reader.hpp"

class ReaderString : public Reader {
    std::string data;
    size_t pos = 0;
    bool open = true;

public:
    explicit ReaderString(const std::string& input) : data(input) {}

    bool isOpen() const override { return open; }

    bool eof() const override { return pos >= data.size(); }

    void close() override { open = false; }

    void read_bytes(char* buffer, size_t size) override {
        if (!open) throw std::runtime_error("Read failed");
        if (pos + size > data.size()) throw std::runtime_error("End of data");
        std::memcpy(buffer, data.data() + pos, size);
        pos += size;
    }
};

#endif // READER_STRING_HPP

