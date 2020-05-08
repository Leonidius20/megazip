#include <iostream>
#include <vector>
#include "unpacker.h"
#include "packer.h"

using namespace std;

int main(int argc, char **argv) {
    if (argc < 3) {
        cout << "Too few arguments" << endl;
        return 1;
    }

    string first(argv[1]);

    if (first == "--decompress") {
        string fileName(argv[2]);
        unpack(fileName);
    } else {
        vector<string> files;

        string outputFile;

        for (int i = 1; i < argc; ++i) {
            string s(argv[i]);

            if (s == "--compress") {
                if (!outputFile.empty() || i + 1 == argc) {
                    cerr << "Ill-formed input." << endl;
                    return 1;
                }

                i++;
                outputFile = argv[i];
            } else {
                files.push_back(s);
            }
        }

        if (outputFile.empty()) {
            cerr << "Ill-formed input." << endl;
            return 1;
        }

        pack(files);
    }

    return 0;
}
