#ifndef READER_WRITER_FILE_HPP
#define READER_WRITER_FILE_HPP

#include "../ReaderWriter.hpp"

class ReaderWriterFile : public ReaderWriter {
    FILE* file;

public:
    explicit ReaderWriterFile(const std::string& path) {
        file = std::fopen(path.c_str(), "r+b");
        if (!file) {
            file = std::fopen(path.c_str(), "w+b");
            if (!file) {
                throw std::runtime_error("Failed to open/create file");
            }
        }
    }

    ~ReaderWriterFile() override { if (file) std::fclose(file); }

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

    void write_bytes(const char* buffer, size_t size) override {
        if (!file) throw std::runtime_error("Write failed");
        std::fwrite(buffer, 1, size, file);
    }
};

#endif // READER_WRITER_FILE_HPP
