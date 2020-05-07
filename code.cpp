#include <cstddef>
#include <algorithm>
#include "code.h"

using namespace std;

// unsigned short Code::NUMBER_OF_BITS = 12;
unsigned short Code::NUMBER_OF_BYTES = 2;

// maybe we could use vararg?
Code::Code(byte first, byte second) : bytes(new byte[NUMBER_OF_BYTES]) {
    bytes[0] = first;
    bytes[1] = second;
}

Code::Code(const Code &other) : bytes(new byte[NUMBER_OF_BYTES]) {
    for (int i = 0; i < NUMBER_OF_BYTES; ++i) {
        bytes[i] = other.bytes[i];
    }
}

bool Code::operator==(const Code &other) const {
    if (bytes[0] != other.bytes[0]) return false;
    return static_cast<unsigned char>(bytes[1]) >> 4 == static_cast<unsigned char>(other.bytes[1]) >> 4;
}
