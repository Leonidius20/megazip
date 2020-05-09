#pragma once

#include <ostream>
#include "string_table.h"

class CodeOutputStream {
    std::ostream &stream;
public:
    explicit CodeOutputStream(std::ostream &stream) : stream(stream) {};

    // flush
    void operator<<(const Code &code);
};