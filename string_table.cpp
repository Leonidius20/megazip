#include <string>
#include <climits>
#include <stdexcept>
#include "code.h"
#include "string_table.h"

using namespace std;

StringTable::StringTable() : lastCode(UCHAR_MAX) {
    for (unsigned char b = 0; b <= UCHAR_MAX; ++b) {
        table[string(1, b)] = b;
    }
}

bool StringTable::addCode(const string &key) {
    if (lastCode == 0xFFF) {
        return false; // table is full
    }
    table[key] = ++lastCode;
    return true;
}