#include "code_table.h"

using namespace std;

CodeTable::CodeTable() {
    for (unsigned char c = 0; c < MAX_UCHAR; ++c) {
        putValue(string(1, c));
    }
    putValue(string(1, MAX_UCHAR));
}

void CodeTable::putValue(const string &value) {
    Code newCode = ++getLastCode();
    if (newCode.toShort() < Code::END_OF_FILE.toShort()) {
        table[newCode] = value;
    }
}
