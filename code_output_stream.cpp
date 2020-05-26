#include "code_output_stream.h"

using std::byte;

void CodeOutputStream::operator<<(const Code &code) {
    if (bufferIsFree) {
        savedCode = code;
        bufferIsFree = false;
        return;
    } else {
        byte firstByte = byte(savedCode.bytes >> 4u);
        byte secondByte = byte(((savedCode.bytes & 0xFu) << 4u) + (code.bytes >> 8u));
        byte thirdByte = byte(code.bytes & 0xFFu);

        stream.write(reinterpret_cast<const char *>(&firstByte), 1);
        stream.write(reinterpret_cast<const char *>(&secondByte), 1);
        stream.write(reinterpret_cast<const char *>(&thirdByte), 1);
        bufferIsFree = true;
    }
}

void CodeOutputStream::flush() {
    if (bufferIsFree) return;
    *this << Code(0);
}

void CodeOutputStream::writeBigEndian(uint32_t number) {
    byte bytes[4];

    bytes[0] = byte(number >> 24u);
    bytes[1] = byte((number >> 16u) & 0xFFu);
    bytes[2] = byte((number >> 8u) & 0xFFu);
    bytes[3] = byte(number & 0xFFu);

    stream.write(reinterpret_cast<const char *>(&bytes), 4);
}
