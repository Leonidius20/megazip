#pragma once

#include <ostream>
#include "code.h"

class CodeOutputStream {
    std::ostream &stream;
    Code savedCode = Code(0);
    bool bufferIsFree = true;
public:
    explicit CodeOutputStream(std::ostream &stream) : stream(stream) {};

    void flush();

    void operator<<(const Code &code);

    void writeBigEndian(uint32_t number);
};
