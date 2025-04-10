#ifndef WRITER_FILE_HPP
#define WRITER_FILE_HPP

#include "../Writer.hpp"

class WriterFile : public Writer {
    FILE* file;

public:
    explicit WriterFile(const char* filename) {
        file = std::fopen(filename, "wb");
        if (!file) throw std::runtime_error("Failed to open file");
    }

    ~WriterFile() override { if (file) std::fclose(file); }

    bool isOpen() const override { return file != nullptr; }

    bool eof() const override { return std::feof(file); }

    void close() override {
        if (file) {
            std::fclose(file);
            file = nullptr;
        }
    }

    void write_bytes(const char* buffer, size_t size) override {
        if (!file) throw std::runtime_error("Write failed");
        std::fwrite(buffer, 1, size, file);
    }
};

#endif // WRITER_FILE_HPP

