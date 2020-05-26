#include "code_input_stream.h"
#include <stdexcept>

using namespace std;

CodeInputStream &operator>>(CodeInputStream &stream, Code &code) {
    if (stream.eof) {
        throw runtime_error("EOF");
    }

    if (stream.cachedCode != nullptr) {
        code = *stream.cachedCode;
        delete stream.cachedCode;
        stream.cachedCode = nullptr;
    } else {
        int size = 3;

        byte *bytes = new byte[size];
        stream.input->read(reinterpret_cast<char *>(bytes), size);

        code = Code((uint16_t(bytes[0]) << 4u) | (uint16_t(bytes[1]) >> 4u));
        stream.cachedCode = new Code(
                ((uint16_t(bytes[1]) & 0xFu) << 8u) | uint16_t(bytes[2]));
    }

    stream.eof = (code == Code::END_OF_FILE);
    return stream;
}
