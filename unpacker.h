#pragma once

#include "code_input_stream.h"
#include <fstream>
#include <string>

void decompress(CodeInputStream &input, std::ofstream &output);

void unpack(const std::string &file);
