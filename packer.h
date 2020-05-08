#pragma once

#include <istream>
#include <ostream>
#include <vector>
#include <string>

void compress(std::istream &input, std::ostream &output);

void pack(const std::vector<std::string> &files);