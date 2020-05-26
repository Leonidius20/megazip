#ifndef MEGAZIP_CODE_INPUT_STREAM_H
#define MEGAZIP_CODE_INPUT_STREAM_H

#include <fstream>
#include "code.h"

class CodeInputStream {

    std::ifstream *input;

    Code *cachedCode = nullptr;
    bool eof = false;
public:

    explicit CodeInputStream(std::ifstream *input) : input(input) {}

    friend CodeInputStream &operator>>(CodeInputStream &stream, Code &code);

    explicit operator bool() { return !eof; }
};


#endif //MEGAZIP_CODE_INPUT_STREAM_H
