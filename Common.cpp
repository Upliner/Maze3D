#include "Common.h"
#include <stdexcept>

MyFile::MyFile(char const *filename) : filename(filename) {
    if (!(f = fopen(filename,"rb")))
        throw std::runtime_error(std::string("Can't open file ") + std::string(filename));
}
void MyFile::read(void *buf, size_t cnt) {
    if (fread(buf, 1, cnt, f) != cnt)
        throw std::runtime_error(std::string("Error reading file ") + std::string(filename));
}
void MyFile::seek(size_t pos) {
    if (fseek(f, pos, SEEK_SET) != 0)
        throw std::runtime_error(std::string("Seek failed in ") + std::string(filename));
}
MyFile::~MyFile() {
    fclose(f);
}