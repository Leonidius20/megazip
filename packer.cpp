#include <istream>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "string_table.h"
#include "packer.h"
#include "code_output_stream.h"

using namespace std;

void compress(istream &input, CodeOutputStream &output) {
    StringTable table;
    string currentPrefix;

    unsigned char c;
    string currentString;
    while (input >> c) {
        currentString = currentPrefix + string(1, c); // move prob not needed here
        if (table.contains(currentString)) {
            currentPrefix = move(currentString);
        } else {
            table.addCode(currentString); // might fail but we don't care
            output << table.getCode(currentPrefix);
            currentPrefix = c;
        }
    }
}

void pack(const vector<string> &files, const string &outputFile) {
    ofstream fileStream(outputFile, ios::binary);
    if (!fileStream.is_open()) throw runtime_error("Could not open the output file");
    CodeOutputStream codeStream(fileStream);

    for (const string &file : files) {
        cout << "Processing file " << file << "... ";
        fileStream << file.length() * sizeof(char) << file;
        ifstream inputStream(file, ios::binary);
        if (!inputStream.is_open()) {
            throw runtime_error("Could not open the file " + file);
        }
        compress(inputStream, codeStream);
        inputStream.close();
        codeStream << Code::END_OF_FILE;
        codeStream.flush(); // should it be here?
        cout << "Done." << endl;
    }

    fileStream.close();
}