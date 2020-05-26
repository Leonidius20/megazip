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

void CodeTable::putValue(const string &value) {
    Code newCode = ++getLastCode();
    if (newCode.toShort() < Code::END_OF_FILE.toShort()) {
        table[newCode] = value;
    }
}
