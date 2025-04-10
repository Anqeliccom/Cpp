#include "File/ReaderFile.hpp"
#include "File/WriterFile.hpp"
#include "String/ReaderString.hpp"
#include "String/WriterString.hpp"
#include "File/RW_File.hpp"
#include "String/RW_String.hpp"
#include <cassert>
#include <cstdio>

void testWriterAndReaderFile() {
    const char* filename = "test.bin";

    WriterFile writer(filename);
    writer.write(786);
    writer.write(7.56);
    writer.write(std::string("math"));
    writer.close();

    ReaderFile reader(filename);
    int i;
    double d;
    std::string s;
    reader.read(i);
    reader.read(d);
    reader.read(s);
    reader.close();

    assert(i == 786);
    assert(d == 7.56);
    assert(s == "math");

    std::remove(filename);
}

void testWriterAndReaderString() {
    std::string buffer;

    WriterString writer(buffer);
    writer.write(786);
    writer.write(7.56);
    writer.write(std::string("math"));
    writer.close();

    ReaderString reader(buffer);
    int i;
    double d;
    std::string s;
    reader.read(i);
    reader.read(d);
    reader.read(s);
    reader.close();

    assert(i == 786);
    assert(d == 7.56);
    assert(s == "math");
}

void testRW_File() {
    const char* filename = "test_rw.bin";

    ReaderWriterFile writer(filename);
    writer.write(23);
    writer.write(std::string("ray"));
    writer.close();

    ReaderWriterFile reader(filename);
    int i;
    std::string s;
    reader.read(i);
    reader.read(s);
    reader.close();

    assert(i == 23);
    assert(s == "ray");

    std::remove(filename);
}

void testRW_String() {
    std::string buffer;

    ReaderWriterString writer(buffer);
    writer.write(23);
    writer.write(std::string("ray"));
    writer.close();

    ReaderWriterString reader(buffer);
    int i;
    std::string s;
    reader.read(i);
    reader.read(s);
    reader.close();

    assert(i == 23);
    assert(s == "ray");
}

int main() {
    testWriterAndReaderFile();
    testWriterAndReaderString();
    testRW_File();
    testRW_String();
    return 0;
}
