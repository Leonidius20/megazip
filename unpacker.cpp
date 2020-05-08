#include "unpacker.h"

#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>
#include "code_table.h"
#include "code_input_stream.h"

using namespace std;

unsigned int readInt(ifstream &input);

void appendToLastEntry(char c, CodeTable &table);

void unpack(const string &file) {
    ifstream input(file, ios::in | ios::binary);

    while (input.peek() != EOF) {
        unsigned int fileNameLength = readInt(input);

        byte *fileNameBytes = new byte[fileNameLength];
        input.read(reinterpret_cast<char *>(fileNameBytes), fileNameLength);
        char *fileName(reinterpret_cast<char *>(fileNameBytes));

        cout << "Decompressing file " << fileName << "... ";

        if (filesystem::exists(fileName)) {
            cerr << endl
                 << "File is not empty. Recreating it... ";
            filesystem::remove(fileName);
        }

        CodeInputStream codeStream(&input);
        ofstream output(fileName);

        decompress(codeStream, output);

        cout << "Done.";

        delete[] fileNameBytes;
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

    unsigned short code;
    bool firstRead = true;
    while (input >> code) {
        string value = table.getValue(code);

        if (!firstRead) {
            appendToLastEntry(value[0], table);
            value = table.getValue(code); // value might've been updated.
        }
        firstRead = false;

        output << value;
        table.putValue(value);
    }
}

void appendToLastEntry(const char c, CodeTable &table) {
    unsigned short lastCodeInDictionary = table.getLastCode();
    string lastValueFromDictionary = table.getValue(lastCodeInDictionary);

    lastValueFromDictionary += c;
    table.updateValue(lastCodeInDictionary, lastValueFromDictionary);
}
