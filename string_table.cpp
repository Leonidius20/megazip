#include <string>
#include <iostream>
#include <climits>
#include <stdexcept>
#include "code.h"
#include "string_table.h"

using namespace std;

StringTable::StringTable() : lastCode(UCHAR_MAX) {
    for (unsigned char b = 0; b < UCHAR_MAX; ++b) {
        table[string(1, b)] = Code(b);
    }
    table[string(1, UCHAR_MAX)] = Code(UCHAR_MAX);
}

bool StringTable::addCode(const string &key) {
    if (lastCode.toShort() == Code::END_OF_FILE.toShort() - 1) {
        return false; // table is full
    }
    table[key] = ++lastCode;
    return true;
}