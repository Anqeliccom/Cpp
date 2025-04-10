#ifndef WRITER_STRING_HPP
#define WRITER_STRING_HPP

#include "../Writer.hpp"

class WriterString : public Writer {
    std::string& output;
    bool open = true;

public:
    explicit WriterString(std::string& buffer) : output(buffer) {}

    bool isOpen() const override { return open; }

    bool eof() const override { return false; }

    void close() override { open = false; }

    void write_bytes(const char* buffer, size_t size) override {
        if (!open) throw std::runtime_error("Write failed");
        output.append(buffer, size);
    }
};

#endif // WRITER_STRING_HPP

