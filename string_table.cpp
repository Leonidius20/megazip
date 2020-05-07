#include <string>
#include <climits>
#include "code.h"
#include "string_table.h"

using namespace std;

StringTable::StringTable() {
    for (unsigned char b = 0; b < UCHAR_MAX; ++b) {
        table[string(1, b)] = Code(byte(b));
    }

}

Code const &StringTable::addCode(const string &key) {
    return Code(); // TODO
}