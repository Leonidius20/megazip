#include <string>
#include <iostream>
#include <limits>
#include <stdexcept>
#include "code.h"
#include "string_table.h"

using namespace std;

const unsigned char MAX_UCHAR = numeric_limits<unsigned char>::max();

StringTable::StringTable() : lastCode(MAX_UCHAR) {
    for (unsigned char b = 0; b < MAX_UCHAR; ++b) {
        table[string(1, b)] = Code(b);
        cout << "byte" << b << "has code" << Code(b).toShort() << endl;
    }
    table[string(1, MAX_UCHAR)] = Code(MAX_UCHAR);
}

bool StringTable::addCode(const string &key) {
    if (lastCode.toShort() == 0xFFF) {
        return false; // table is full
    }
    table[key] = ++lastCode;
    return true;
}