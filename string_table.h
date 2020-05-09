#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <cstddef>
#include <memory>

using Code = unsigned short;

class StringTable {
    std::unordered_map<std::string, Code> table;
    Code lastCode;
public:
    StringTable();

    [[nodiscard]] Code const &getCode(const std::string &key) const { return table.at(key); };

    [[nodiscard]] bool contains(const std::string &key) const { return table.contains(key); }

    bool addCode(const std::string &key);
};