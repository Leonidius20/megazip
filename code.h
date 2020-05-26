#pragma once

#include <cstddef>
#include <algorithm>
#include <stdexcept>
#include <cmath>

class Code {
    unsigned short bytes = 0;
public:
    friend class CodeOutputStream;

    static Code END_OF_FILE;

    Code() = default;

    explicit Code(short bytes) {
        if (bytes > pow(2, 12) - 1) throw std::invalid_argument("Code value is out of bounds");
        this->bytes = bytes;
    };

    Code &operator++();

    bool operator==(const Code &other) const { return bytes == other.bytes; };

    [[nodiscard]] unsigned short toShort() const { return bytes; };
};