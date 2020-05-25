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
        stream << firstTwoBytes << thirdByte;
        bufferIsFree = true;
    }
}

void CodeOutputStream::flush() {
    if (bufferIsFree) return;
    stream << savedCode.toShort();
    bufferIsFree = true;
}
