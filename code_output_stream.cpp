#include "code_output_stream.h"

using std::byte;

void CodeOutputStream::operator<<(const Code &code) {
    if (bufferIsFree) {
        savedCode = code;
        bufferIsFree = false;
        return;
    } else {
        short firstTwoBytes = savedCode.toShort() + (code.toShort() >> 12u);
        unsigned char thirdByte = (code.toShort() & 0b0000111111111111u) >> 4u;
        stream.write(reinterpret_cast<const char *>(&firstTwoBytes), 2);
        stream.write(reinterpret_cast<const char *>(&thirdByte), 1);
        bufferIsFree = true;
    }
}

void CodeOutputStream::flush() {
    if (bufferIsFree) return;
    stream.write(reinterpret_cast<const char *>(&savedCode), 2);
    bufferIsFree = true;
}

void CodeOutputStream::writeLittleEndian(uint32_t number) {
    byte bytes[4];

    bytes[0] = byte(number >> 24u);
    bytes[1] = byte((number >> 16u) & 0xFFu);
    bytes[2] = byte((number >> 8u) & 0xFFu);
    bytes[3] = byte(number & 0xFFu);

    stream.write(reinterpret_cast<const char *>(&bytes), 4);
}
