#pragma once

#include <istream>
#include <ostream>
#include <string>

void decompress(std::istream &input, std::ostream &output);

void unpack(const std::string &file);
