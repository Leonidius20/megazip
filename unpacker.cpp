#include "unpacker.h"

#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>
#include "code_table.h"
#include "code_input_stream.h"
#include "code.h"

using namespace std;

unsigned int readInt(ifstream &input);

void unpack(const string &file) {
    ifstream input(file, ios::in | ios::binary);

    while (input.peek() != EOF) {
        unsigned int fileNameLength = readInt(input);

        char *fileName = new char[fileNameLength + 1]; // +1 for '\0'
        input.read(fileName, fileNameLength);
        fileName[fileNameLength] = '\0';

        cout << "Decompressing file " << fileName << "... ";

        if (filesystem::exists(fileName)) {
            cerr << endl
                 << "File is not empty. Recreating it... ";
            filesystem::remove(fileName);
        }

        CodeInputStream codeStream(&input);
        ofstream output(fileName, ios::out | ios::binary);

        decompress(codeStream, output);

        output.close();

        cout << "Done." << endl;

        delete[] fileName;
    }

    input.close();
}

unsigned int readInt(ifstream &input) {
    size_t size = sizeof(int);
    byte *bytes = new byte[size];
    input.read(reinterpret_cast<char *>(bytes), size);

    unsigned int value = 0;

    for (int i = 0; i < size; ++i) {
        value = (value << 8u) + static_cast<unsigned char>(bytes[i]);
    }

    delete[] bytes;
    return value;
}

void decompress(CodeInputStream &input, ofstream &output) {
    CodeTable table;

    Code oldCode, code;
    string oldValue, value;

    input >> code;
    output << table.getValue(code);
    oldCode = code;

    while (input >> code) {
        if (table.contains(code)) {
            value = table.getValue(code);
            output.write(value.c_str(), value.length());
            oldValue = table.getValue(oldCode);
            table.putValue(oldValue + value[0]);
            oldCode = code;
        } else {
            oldValue = table.getValue(oldCode);
            value = oldValue + oldValue[0];
            output.write(value.c_str(), value.length());
            table.putValue(value);
            oldCode = code;
        }

    }
}
