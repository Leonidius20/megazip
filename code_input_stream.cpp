#include "code_input_stream.h"
#include <stdexcept>

using namespace std;

#define COMPRESS_EOF 0xFFF // 2^12 - 1

CodeInputStream &operator>>(CodeInputStream &stream, unsigned short &code) {
    if (stream.eof) {
        throw exception();
    }

    if (stream.cachedCode != nullptr) {
        code = *stream.cachedCode;
        delete stream.cachedCode;
        stream.cachedCode = nullptr;
    } else {
        int size = 3;

        byte *bytes = new byte[size];
        stream.input->read(reinterpret_cast<char *>(bytes), size);

        code = (uint16_t(bytes[0]) << 4u) | (uint16_t(bytes[1]) >> 4u);
        stream.cachedCode = new unsigned short(
                ((uint16_t(bytes[1]) & 0xFu) << 8u) | uint16_t(bytes[2]));
    }

    stream.eof = (code == COMPRESS_EOF);
    return stream;
}
