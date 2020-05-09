#include <istream>
#include <ostream>
#include <vector>
#include <string>
#include "string_table.h"
#include "packer.h"
#include "code_output_stream.h"

using namespace std;

void compress(istream &input, CodeOutputStream &output) {
    StringTable table;
    string currentPrefix;

    char c;
    string currentString;
    while (input >> c) {
        currentString = currentPrefix + c; // move prob not needed here
        if (table.contains(currentString)) {
            currentPrefix = move(currentString);
        } else {
            table.addCode(currentString); // might fail but we don't care
            output << table.getCode(currentPrefix);
            currentPrefix = c;
        }
    }
}

void pack(const vector<string> &files) {
    for (const string &file : files) {
        // TODO
    }
}