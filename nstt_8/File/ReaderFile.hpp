#ifndef READER_FILE_HPP
#define READER_FILE_HPP

#include "../Reader.hpp"

class ReaderFile : public Reader {
    FILE* file;

public:
    explicit ReaderFile(const std::string& path) {
        file = std::fopen(path.c_str(), "rb");
        if (!file) throw std::runtime_error("Failed to open file");
    }

    ~ReaderFile() override { if (file) std::fclose(file); }

    bool isOpen() const override { return file != nullptr; }

    bool eof() const override { return std::feof(file); }

    void close() override {
        if (file) {
            std::fclose(file);
            file = nullptr;
        }
    }

    void read_bytes(char* buffer, size_t size) override {
        if (!file) throw std::runtime_error("Read failed");
        std::fread(buffer, 1, size, file);
    }
};

#endif // READER_FILE_HPP
