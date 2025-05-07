#ifndef READER_WRITER_HPP
#define READER_WRITER_HPP

#include "Reader.hpp"
#include "Writer.hpp"

class ReaderWriter : public Reader, public Writer {
public:
    virtual ~ReaderWriter() = default;
};

#endif // READER_WRITER_HPP