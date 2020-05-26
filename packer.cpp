#include <istream>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "string_table.h"
#include "code_output_stream.h"
#include "packer.h"

using namespace std;

void compress(istream &input, CodeOutputStream &output) {
    StringTable table;
    string currentPrefix;

    char c;
    string currentString;
    while (input.read(&c, 1)) {
        currentString = currentPrefix + string(1, c);
        if (table.contains(currentString)) {
            currentPrefix = move(currentString);
        } else {
            table.addCode(currentString); // might fail but we don't care
            output << table.getCode(currentPrefix);
            currentPrefix = c;
        }
    }
    output << table.getCode(currentPrefix);
}

void pack(const vector<string> &files, const string &outputFile) {
    ofstream fileStream(outputFile, ios::out | ios::trunc | ios::binary);
    if (!fileStream.is_open()) throw runtime_error("Could not open the output file");
    CodeOutputStream codeStream(fileStream);

    for (const string &file : files) {
        cout << "Processing file " << file << "... ";

        ifstream inputStream(file, ios::in | ios::binary);
        if (!inputStream.is_open()) {
            throw runtime_error("Could not open the file " + file);
        }

        codeStream.writeBigEndian(file.length());
        fileStream.write(file.c_str(), file.length());

        compress(inputStream, codeStream);
        inputStream.close();
        codeStream << Code::END_OF_FILE;
        codeStream.flush();
        cout << "Done." << endl;
    }

    fileStream.close();

    cout << "Result written to " << outputFile << "." << endl;
}