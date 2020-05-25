#pragma once

#include <cstddef>
#include <algorithm>
#include <cmath>

class Code {
    unsigned short bytes = 0;
public:
    explicit Code(short bytes) : bytes((bytes >> 4u) << 4u) {};

    [[nodiscard]] unsigned short toShort() const { return bytes; };
};

    //static unsigned short NUMBER_OF_BYTES;
    // static unsigned short NUMBER_OF_BITS;
    /*[[nodiscard]] static unsigned short getNumberOfBytes() {
        return std::ceil(NUMBER_OF_BITS / 8.0);
    }*/
/*public:


    // friend class Input/OutputCodeStream

    explicit Code(std::byte first = std::byte(0), std::byte second = std::byte(0));

    Code(Code &&other) noexcept { std::swap(bytes, other.bytes); };

    Code(const Code &other);

    Code &operator=(Code other) {
        swap(bytes, other.bytes);
        return *this;
    };

    bool operator==(const Code &other) const;

    ~Code() { delete[] bytes; };
};