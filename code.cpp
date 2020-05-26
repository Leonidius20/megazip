#include <stdexcept>
#include "code.h"

using namespace std;

Code Code::END_OF_FILE = Code(0xFFF); // 12 ^ 2 - 1

Code &Code::operator++() {
    if (bytes == pow(2, 12) - 1) throw runtime_error("Cannot increment the code any further");
    bytes++;
    return *this;
}