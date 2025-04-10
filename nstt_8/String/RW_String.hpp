#ifndef READER_WRITER_STRING_HPP
#define READER_WRITER_STRING_HPP

#include "../ReaderWriter.hpp"

class ReaderWriterString : public ReaderWriter {
    std::string& data;
    size_t pos = 0;
    bool open = true;

public:
    explicit ReaderWriterString(std::string& buffer) : data(buffer) {}

    bool isOpen() const override { return open; }

    bool eof() const override { return pos >= data.size(); }

    void close() override { open = false; }

    void read_bytes(char* buffer, size_t size) override {
        if (!open) throw std::runtime_error("Read failed");
        if (pos + size > data.size()) throw std::runtime_error("End of data");
        std::memcpy(buffer, data.data() + pos, size);
        pos += size;
    }

    void write_bytes(const char* buffer, size_t size) override {
        if (!open) throw std::runtime_error("Write failed");
        data.append(buffer, size);
    }
};

#endif // READER_WRITER_STRING_HPP
