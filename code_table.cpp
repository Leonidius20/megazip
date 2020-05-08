#include "code_table.h"
#include <climits>
#include <stdexcept>

using namespace std;

CodeTable::CodeTable() {
    for (unsigned int c = 0; c <= UCHAR_MAX; ++c) {
        string value(1, char(c));
        putValue(value);
    }
}

void CodeTable::updateValue(const unsigned short &code, const string &value) {
    if (!table.contains(code)) {
        throw std::out_of_range("Cannot update value that's not in table.");
    }
    table[code] = value;
}

void CodeTable::putValue(const string &value) {
    unsigned short code = size();
    if (code <= MAX_CODE) {
        table[code] = value;
    }
}
