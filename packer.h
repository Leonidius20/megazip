#pragma once

#include <istream>
#include <ostream>
#include <vector>
#include <string>
#include "code_output_stream.h"

void compress(std::istream &input, CodeOutputStream &output);

void pack(const std::vector<std::string> &files, const std::string &outputFile);